#!/usr/bin/env python3
"""Adapt actual trainerproc output to the compact FireRed Johto ROM pool.

Only array designators change. Original HnS .party input, generator and output
remain unchanged; the separately named FireRed header contains the same teams.
"""

import argparse
from pathlib import Path
import re


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--input', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--constants', type=Path, required=True)
    parser.add_argument('--party', type=Path, required=True)
    args = parser.parse_args()
    source = args.input.read_text(encoding='utf-8')
    constants = args.constants.read_text(encoding='utf-8')
    party = args.party.read_text(encoding='utf-8')
    names = re.findall(r'^===\s+(TRAINER_[A-Z0-9_]+)\s+===\s*$', party, re.MULTILINE)
    aliases = set(re.findall(r'^#define\s+(TRAINER_JOHTO_[A-Z0-9_]+)\s+\(', constants, re.MULTILINE))
    expected = set(names)
    seen = set()
    pattern = re.compile(r'(\[DIFFICULTY_[A-Z0-9_]+\])\[(TRAINER_[A-Z0-9_]+)\](\s*=)')

    def adapt(match):
        original = match.group(2)
        alias = 'TRAINER_JOHTO_' + original.removeprefix('TRAINER_')
        if original not in expected or alias not in aliases:
            raise ValueError('No approved catalog mapping for ' + original)
        seen.add(original)
        return match.group(1) + '[(' + alias + ' - JOHTO_TRAINER_ID_BASE)]' + match.group(3)

    adapted, count = pattern.subn(adapt, source)
    if len(names) != len(expected) or seen != expected or count != len(names):
        raise ValueError('Generated HnS designators do not exactly match the real source catalog')
    # This reversible check rules out accidental changes to names, teams, stats,
    # AI, moves or every other byte from the actual trainerproc output.
    restored = re.sub(r'\[\((TRAINER_JOHTO_[A-Z0-9_]+) - JOHTO_TRAINER_ID_BASE\)\]',
                      lambda m: '[TRAINER_' + m.group(1).removeprefix('TRAINER_JOHTO_') + ']', adapted)
    if restored != source:
        raise ValueError('Johto pool adaptation changed a non-designator byte')
    args.output.write_text(adapted, encoding='utf-8')


if __name__ == '__main__':
    main()
