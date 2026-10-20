#!/usr/bin/env python3
"""Manual isolated build. No upload, automation, cleanup or gameplay."""
from pathlib import Path
import argparse, datetime, hashlib, json, os, re, shutil, subprocess, sys
from verify_source import verify
ROOT=Path(__file__).resolve().parents[1]
def main():
 p=argparse.ArgumentParser();p.add_argument('--toolchain',type=Path,required=True);p.add_argument('--make',default='make');p.add_argument('--host-prefix',type=Path);p.add_argument('--run-id',default='build-37c-01');p.add_argument('--jobs',type=int,choices=range(1,5),default=2);a=p.parse_args()
 if not re.fullmatch(r'[A-Za-z0-9_-]+',a.run_id):raise SystemExit('Unsafe run id')
 result=verify(True)
 if result['failures']:print(json.dumps(result,indent=2));return 2
 out=ROOT/'_local/runs'/a.run_id;out.mkdir(parents=True,exist_ok=False);source=out/'engine'
 rows=json.loads((ROOT/'provenance/engine-inputs.json').read_text())['records']
 for r in rows:
  if not (r['exported'] or r['path'].endswith('.gba')):continue
  dest=source/r['path'];dest.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(ROOT/'engine'/r['path'],dest);dest.chmod(0o755 if r['mode']=='100755' else 0o644)
 make=shutil.which(a.make) if '/' not in a.make else str(Path(a.make).resolve())
 if not make:raise SystemExit('GNU Make is missing')
 bins=[str(a.toolchain.resolve()/'bin')]
 if a.host_prefix:bins.append(str(a.host_prefix.resolve()/'bin'))
 bins.extend([str(Path(make).parent),str(Path(sys.executable).resolve().parent),'/usr/bin','/bin','/usr/sbin','/sbin'])
 env={k:os.environ[k] for k in ['HOME','TMPDIR','SYSTEMROOT'] if k in os.environ};env.update(PATH=os.pathsep.join(dict.fromkeys(bins)),LANG='C',LC_ALL='C',TZ='UTC')
 if a.host_prefix:env.update(PKG_CONFIG_PATH=os.pathsep.join(str(a.host_prefix.resolve()/s) for s in ['lib/pkgconfig','share/pkgconfig']),PKG_CONFIG_ALLOW_SYSTEM_LIBS='1',PKG_CONFIG_ALLOW_SYSTEM_CFLAGS='1')
 cmd=[make,'firered','-j'+str(a.jobs),'TOOLCHAIN='+str(a.toolchain.resolve()),'O_LEVEL=s','RELEASE=0','LTO=0']
 report={'schema':'37c-manual-cloud-build-1','startedUTC':datetime.datetime.now(datetime.timezone.utc).isoformat(),'command':cmd,'scope':'Fresh source copy; generated outputs ignored; compilation is not gameplay','environment':{k:env[k] for k in ['PATH','LANG','LC_ALL','TZ']},'sourceVerification':result}
 with (out/'stdout.log').open('wb') as stdout,(out/'stderr.log').open('wb') as stderr:
  run=subprocess.run(cmd,cwd=source,env=env,stdout=stdout,stderr=stderr)
 report['exitCode']=run.returncode;report['artifacts']=[]
 for name in ['pokefirered.gba','pokefirered.elf','pokefirered.map']:
  file=source/name
  if file.is_file():b=file.read_bytes();report['artifacts'].append({'name':name,'bytes':len(b),'sha256':hashlib.sha256(b).hexdigest()})
 if (source/'pokefirered.map').exists():
  s=(source/'pokefirered.map').read_text();reg=re.search(r'^ROM\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)',s,re.M);end=re.search(r'^\s*0x([0-9a-f]+)\s+__rom_end\b',s,re.M)
  if reg and end:used=int(end[1],16)-int(reg[1],16);report['ROM']={'used':used,'capacity':int(reg[2],16),'free':int(reg[2],16)-used}
 report['endedUTC']=datetime.datetime.now(datetime.timezone.utc).isoformat();(out/'manifest.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps({'exitCode':run.returncode,'report':str(out/'manifest.json'),'ROM':report.get('ROM'),'artifacts':report['artifacts']},indent=2));return run.returncode
if __name__=='__main__':raise SystemExit(main())
