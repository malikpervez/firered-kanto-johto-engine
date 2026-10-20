#!/usr/bin/env python3
"""Restore only three pinned upstream multiboot inputs into ignored paths."""
from pathlib import Path
import argparse, hashlib, json, subprocess

ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--cache',type=Path);p.add_argument('--fetch',action='store_true');a=p.parse_args()
 record=json.loads((ROOT/'provenance/upstream-embedded-inputs.json').read_text())
 cache=(a.cache or ROOT/'_local/upstream-input-cache').resolve()
 if not cache.exists():
  if not a.fetch:raise SystemExit('Provide a pinned upstream Git checkout with --cache or explicitly allow its read-only clone with --fetch.')
  cache.parent.mkdir(parents=True,exist_ok=True)
  subprocess.run(['git','clone','--filter=blob:none','--no-checkout',record['sourceURL'],str(cache)],check=True)
 subprocess.run(['git','-C',str(cache),'cat-file','-e',record['commit']+'^{commit}'],check=True)
 restored=[]
 for r in record['inputs']:
  dest=ROOT/'engine'/r['path']
  if dest.exists():
   b=dest.read_bytes()
  else:
   b=subprocess.check_output(['git','-C',str(cache),'show',record['commit']+':'+r['path']])
  if len(b)!=r['bytes'] or hashlib.sha256(b).hexdigest()!=r['sha256']:raise SystemExit('Input hash mismatch: '+r['path'])
  if not dest.exists():dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(b)
  restored.append(r['path'])
 print(json.dumps({'status':'PASS — exact pinned source inputs restored locally, never committed','inputs':restored}))
if __name__=='__main__':main()
