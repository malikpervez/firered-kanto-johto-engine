#!/usr/bin/env python3
"""Compile the existing three layout probes, comparing 397 actual ARM facts."""
from pathlib import Path
import argparse, datetime, json, os, re, shutil, struct, subprocess
ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--toolchain',type=Path);p.add_argument('--engine-root',type=Path,default=ROOT/'engine');p.add_argument('--run-id',default='arm-layout-01');a=p.parse_args()
 engine=a.engine_root.resolve()
 if not engine.is_relative_to(ROOT):raise SystemExit('Use a source/build tree inside this repository.')
 if not (engine/'include/constants/map_groups.h').is_file():raise SystemExit('Generated map headers are absent. Run the fresh build first, then pass --engine-root _local/runs/<build-run>/engine. No fake header is supplied.')
 if not re.fullmatch(r'[a-zA-Z0-9_-]+',a.run_id):raise SystemExit('Unsafe run id')
 out=ROOT/'_local/checks'/a.run_id;out.mkdir(parents=True,exist_ok=False)
 def tool(name):
  p=a.toolchain/'bin'/('arm-none-eabi-'+name) if a.toolchain else shutil.which('arm-none-eabi-'+name)
  if not p:raise SystemExit('ARM tool missing: '+name)
  return str(p)
 expected=json.loads((ROOT/'tests/expected-arm-layout.json').read_text());runs=[];actual={};fail=[]
 flags=['-mthumb','-mthumb-interwork','-mabi=apcs-gnu','-mtune=arm7tdmi','-march=armv4t','-std=gnu17','-DMODERN=1','-DTESTING=0','-DFIRERED','-Os','-iquote','include']
 def run(name,cmd):
  r=subprocess.run(cmd,cwd=engine,capture_output=True);(out/(name+'.stdout')).write_bytes(r.stdout);(out/(name+'.stderr')).write_bytes(r.stderr);runs.append({'command':cmd,'cwd':str(engine),'exit':r.returncode})
  if r.returncode:raise RuntimeError('Probe failed: '+name+'; see '+str(out))
  return r.stdout
 try:
  version=run('compiler-version',[tool('gcc'),'--version']).decode()
  for name,values in expected.items():
   probe=ROOT/'tests/probes'/(name+'.c')
   if name=='registered':
    obj=out/(name+'.o');raw=out/(name+'.bin');run(name,[tool('gcc'),*flags,'-c',str(probe),'-o',str(obj)]);run(name+'-extract',[tool('objcopy'),'-O','binary','--only-section=.registered',str(obj),str(raw)])
    b=raw.read_bytes()
    if len(b)!=4*len(values):raise RuntimeError('Registered array length mismatch')
    measured=dict(zip(values,struct.unpack('<'+'I'*len(values),b)))
   else:
    asm=out/(name+'.s');run(name,[tool('gcc'),*flags,'-S',str(probe),'-o',str(asm)]);s=asm.read_text();measured={}
    for key in values:
     m=re.search(r'^'+re.escape(key)+r':\s*\n\s*\.(word|space|zero)\s+([^\n@]+)',s,re.M)
     if not m:raise RuntimeError('Cannot extract actual ARM field: '+key)
     measured[key]=0 if m[1] in ['space','zero'] else int(m[2].strip(),0)&0xffffffff
   actual[name]=measured
   fail.extend({'probe':name,'field':k,'expected':v,'actual':measured.get(k)} for k,v in values.items() if measured.get(k)!=v)
  report={'status':'PASS' if not fail else 'FAIL','facts':sum(map(len,actual.values())),'failures':fail,'compiler':version,'runs':runs,'actual':actual,'scope':'Actual ARM structure/offset facts only. No save conversion or game runtime.'}
 except Exception as e:
  report={'status':'ERROR','error':str(e),'runs':runs,'actual':actual}
 (out/'results.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps({k:v for k,v in report.items() if k not in ['runs','actual','compiler']},indent=2));return 0 if report['status']=='PASS' else 1
if __name__=='__main__':raise SystemExit(main())
