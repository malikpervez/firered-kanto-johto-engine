#!/usr/bin/env python3
"""Check exact 37C raw source; source integrity is not gameplay evidence."""
from pathlib import Path
import argparse, concurrent.futures, hashlib, json
ROOT=Path(__file__).resolve().parents[1]
def verify(require_embedded=False):
 data=json.loads((ROOT/'provenance/engine-inputs.json').read_text());fail=[];count=0;missing=[]
 def check(r):
  p=ROOT/'engine'/r['path']
  needed=r['exported'] or require_embedded and r['path'].endswith('.gba')
  if not needed:return None
  if not p.is_file():return {'path':r['path'],'error':'missing'}
  b=p.read_bytes()
  if len(b)!=r['bytes'] or hashlib.sha256(b).hexdigest()!=r['sha256']:return {'path':r['path'],'error':'hash/length mismatch'}
  return True
 with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
  for r in pool.map(check,data['records']):
   if r is True:count+=1
   elif r:fail.append(r)
 return {'status':'PASS' if not fail else 'FAIL','checked':count,'failures':fail,'sourceFingerprint':data['originalSourceFingerprint'],'scope':'Raw source checks only; no build or gameplay execution'}
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--require-embedded',action='store_true');a=p.parse_args();r=verify(a.require_embedded);print(json.dumps(r,indent=2));raise SystemExit(bool(r['failures']))
