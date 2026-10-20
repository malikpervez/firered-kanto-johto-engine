import fs from 'node:fs';
import path from 'node:path';
import crypto from 'node:crypto';
import {fileURLToPath, pathToFileURL} from 'node:url';

// Offline presentation derivative. Never changes the source reviews or evidence.
const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, '../..');
const out = path.join(root, '_local/owner-review');
const modules = process.env.REVIEW_HUB_MODULES || '[LOCAL_MACHINE_PATH]';
const {Marked, Renderer} = await import(pathToFileURL(path.join(modules, 'marked/lib/marked.esm.js')));
const inventoryPath = path.join(root, '_local/review-hub-inputs/document-groups.json');
const inventory = JSON.parse(fs.readFileSync(inventoryPath));
const currentPath = path.join(root, '_local/review-hub-inputs/current-review.json');
const current = fs.existsSync(currentPath) ? JSON.parse(fs.readFileSync(currentPath)) : null;
const curated = new Map(inventory.documents.map(d => [path.resolve(root,d.path),d]));
// Optional preview reviews supplement the room without replacing its current feature.
const supplementalPath=path.join(root,'_local/review-hub-inputs/supplemental-reviews.json');
const supplemental=fs.existsSync(supplementalPath)?JSON.parse(fs.readFileSync(supplementalPath)):{reviews:[]};
if(!Array.isArray(supplemental.reviews))throw Error('Supplemental reviews must be an array');
const supplementalReviews=supplemental.reviews.map(r=>{
  const p=path.resolve(root,r.path||'');
  if(!p.startsWith(root+path.sep)||!fs.existsSync(p)||!p.endsWith('.md'))throw Error('Invalid supplemental review path');
  return {...r,path:p};
});
const supplementalByPath=new Map(supplementalReviews.map(r=>[r.path,r]));
const sha = s => crypto.createHash('sha256').update(s).digest('hex');
const esc = s => String(s ?? '').replaceAll('&','&amp;').replaceAll('<','&lt;').replaceAll('>','&gt;').replaceAll('"','&quot;').replaceAll("'",'&#39;');
const slug = s => String(s).toLowerCase().replace(/<[^>]*>/g,'').replace(/[^\p{L}\p{N}_-]+/gu,'-').replace(/^-|-$/g,'');
const relative = p => path.relative(root,p).split(path.sep).join('/');
const fileHref = p => pathToFileURL(p).href;
const assetHref = p => path.relative(out,p).split(path.sep).map(encodeURIComponent).join('/');
const sources = [];
function walk(dir) {
  for(const e of fs.readdirSync(dir,{withFileTypes:true})) {
    const p=path.join(dir,e.name);
    if(e.isDirectory() && p!==path.join(root,'_local/evidence/campaign-review-refresh-01/before') && !p.split(path.sep).join('/').includes('/scratch/recon/')) walk(p);
    else if(e.isFile() && /\.md$/i.test(e.name)) sources.push(p);
  }
}
for(const e of fs.readdirSync(root,{withFileTypes:true})) if(e.isFile() && /\.md$/i.test(e.name)) sources.push(path.join(root,e.name));
walk(path.join(root,'docs')); walk(path.join(root,'_local/evidence'));
const rainbowPath = path.join(root,'_local/evidence/rainbow-story-01/story-review-01/story-review.html');
sources.push(rainbowPath);
const ids = new Map([...new Set(sources)].map(p=>[p,'d-'+sha(relative(p)).slice(0,12)]));
const imageMap = new Map(), missing = new Set(), blocked = new Set();
const sourcePins=[];
const friendsPath=path.join(root,'_local/evidence/friends-story-01/owner-review-36m/REVIEW.md');
const rocketPath=path.join(root,'_local/evidence/story-presentation-04/owner-review-33b-03/REVIEW.md');
const characterPath=path.join(root,'_local/evidence/story-additions-02/story-review-31e/owner-review-02/story-review.md');
const specialOrder=new Map([[friendsPath,0],[rainbowPath,1],[rocketPath,2],[characterPath,3]]);
const latestPath=current?.reviewPath?path.resolve(root,current.reviewPath):null;
if(latestPath)specialOrder.set(latestPath,-1);
supplementalReviews.filter(r=>r.featured).forEach((r,i)=>specialOrder.set(r.path,4+i));
const friends=JSON.parse(fs.readFileSync(path.join(root,'_local/review-hub-inputs/friends-structure.json')));
const knownCaptures=new Map();
function findCaptures(v) {
  if(Array.isArray(v)) {v.forEach(findCaptures);return;}
  if(!v || typeof v!=='object') return;
  const p=v.path || v.screenshot || v.file || v.image;
  if(typeof p==='string' && /\.(png|gif)$/i.test(p) && (v.build || v.rom_sha256 || v.ROM_sha256 || v.kind)) knownCaptures.set(path.resolve(root,p),v);
  Object.values(v).forEach(findCaptures);
}
findCaptures(friends);
const extraCapturePath=current?.captureIndexPath?path.resolve(root,current.captureIndexPath):null;
const currentCaptureIndex=extraCapturePath&&fs.existsSync(extraCapturePath)?JSON.parse(fs.readFileSync(extraCapturePath)):null;
const historicalCapturePaths=(current?.historicalCaptureIndexPaths||[]).map(p=>path.resolve(root,p));
for(const p of historicalCapturePaths)findCaptures(JSON.parse(fs.readFileSync(p)));
if(currentCaptureIndex)findCaptures(currentCaptureIndex);
const supplementalCapturePaths=[...new Set(supplementalReviews.map(r=>r.captureIndexPath).filter(Boolean).map(p=>path.resolve(root,p)))];
for(const p of supplementalCapturePaths){
  if(!p.startsWith(root+path.sep))throw Error('Supplemental captures must stay local');
  findCaptures(JSON.parse(fs.readFileSync(p)));
}
function resolveRef(href,source) {
  let h=String(href||'').trim();
  if(/^(https?:|mailto:)/i.test(h)) return {external:true,href:h};
  if(h.startsWith('data:image/')) return {data:true,href:h};
  if(/^(javascript:|vbscript:|data:)/i.test(h)) {blocked.add(h.slice(0,120));return {blocked:true,href:'#'};}
  if(h.startsWith('#')) return {anchor:decodeURIComponent(h.slice(1)),target:source};
  let anchor=''; const hash=h.indexOf('#');if(hash>=0){anchor=decodeURIComponent(h.slice(hash+1));h=h.slice(0,hash);}
  let p;
  try {p=h.startsWith('file:')?fileURLToPath(h):decodeURIComponent(h);}catch{p=h;}
  const line=p.match(/:(\d+)$/);if(line) p=p.slice(0,-line[0].length);
  p=path.isAbsolute(p)?path.normalize(p):path.resolve(path.dirname(source),p);
  return {target:p,anchor,line:line?.[1],href:fileHref(p)+(line?'#L'+line[1]:anchor?'#'+encodeURIComponent(anchor):'')};
}
function link(href,text,source) {
  const r=resolveRef(href,source);
  if(r.blocked) return `<span>${text}</span>`;
  const id=ids.get(r.target);
  if(id) return `<a href="#read=${id}${r.anchor?'&part='+encodeURIComponent(r.anchor):''}" data-doc="${id}" data-anchor="${esc(r.anchor||'')}">${text}</a>`;
  return `<a href="${esc(r.href)}" ${r.external?'target="_blank" rel="noreferrer"':'target="_blank" rel="noopener"'} title="${esc(r.target||r.href)}${r.line?':'+r.line:''}">${text}${r.line?`<span class="line-ref">:${r.line}</span>`:''}</a>`;
}
function registerImage(href,caption,source,chapterId) {
  const r=resolveRef(href,source); const docId=ids.get(source);
  if(r.external || r.blocked) return {html:`<div class="image-missing">External image retained as a link. ${link(href,esc(caption||'Original image'),source)}</div>`};
  if(!r.data && (!r.target.startsWith(root+path.sep) || !fs.existsSync(r.target))) {
    missing.add(r.target||href);return {html:`<div class="image-missing">Image unavailable · ${esc(caption)} ${link(href,'Original reference',source)}</div>`};
  }
  const key=r.data?'data-'+sha(r.href):r.target;
  let item=imageMap.get(key);
  if(!item) {
    let width=0,height=0;
    if(!r.data && /\.png$/i.test(r.target)) {const f=fs.openSync(r.target,'r');const b=Buffer.alloc(24);fs.readSync(f,b,0,24,0);fs.closeSync(f);if(b[0]===137&&b[1]===80){width=b.readUInt32BE(16);height=b.readUInt32BE(20);}}
    const known=knownCaptures.get(r.target);
    const staticPreview=/static|not gameplay|composite|mockup|contact sheet|comparison|preview/i.test(caption);
    const supplementalType={native_capture:'Native capture',native_recording:'Native recording',native_contact_sheet:'Native contact sheet',asset_preview:'Static preview',engineering_preview:'Engineering preview'}[known?.presentation_kind];
    item={id:'i-'+sha(key).slice(0,14),src:r.data?r.href:assetHref(r.target),path:r.target||null,caption,docId,chapterId,width,height,type:supplementalType||(known?.kind==='native_gameplay'?'Native capture':staticPreview?'Static preview':known?'Native capture':'Source image'),build_id:known?.build_id||'',rom_sha256:known?.rom_sha256||'',staged:known?.staged??null,script_label:known?.script_label||'',references:[]};
    imageMap.set(key,item);
  }
  if(!item.references.some(x=>x.docId===docId&&x.chapterId===chapterId)) item.references.push({docId,chapterId,caption});
  return {item,html:`<figure class="evidence-image"><button class="image-open" data-image="${item.id}" aria-label="Enlarge image: ${esc(caption)}"><img loading="lazy" decoding="async" src="${esc(item.src)}" alt="${esc(caption)}" ${item.width?`width="${item.width}" height="${item.height}"`:''} class="${item.width===240&&item.height===160?'pixel-capture':''}"><span class="image-zoom" aria-hidden="true">↗</span></button><figcaption>${esc(caption||'Image from the original review')} <span class="media-kind">${esc(item.type)}</span>${item.build_id?` <span class="media-kind">${esc(item.build_id)}${item.staged?' · staged':''}</span>`:''}${item.script_label?`<span class="capture-script">${esc(item.script_label)}</span>`:''}</figcaption></figure>`};
}
function groupFor(p) {
  if(supplementalByPath.get(p)?.category==='characters')return 'characters';
  const rel=relative(p).toLowerCase();
  if(/decisions\/|defects\/|risks\.md|feedback|critical-review|review-findings/.test(rel)) return 'decisions';
  if(/friends-from|friends-arc|friends-new-event|rainbow-story|shadow-lugia-story|event-handoff/.test(rel) && rel.startsWith('docs/'))return 'design';
  if(/owner-review|story-review|story-implementation|character-presentation-implementation|friends-story-presentation/.test(rel))return 'stories';
  if(/map|ambient|art-review|asset-review|character|presentation/.test(rel))return 'visuals';
  if(/build|test|native|save|rom-|source|environment|toolchain|optimization|capacity/.test(rel))return 'engineering';
  if(rel.startsWith('docs/')||!rel.includes('/'))return 'project';
  return 'archive';
}
function renderMarkdown(raw,source,chapterId) {
  const headings=[],anchors=[];const counts=new Map();const renderer=new Renderer();
  renderer.heading=function(t){const text=this.parser.parseInline(t.tokens),base=slug(t.text)||'section',n=counts.get(base)||0;counts.set(base,n+1);const id=base+(n?'-'+n:'');headings.push({id,text:t.text,depth:t.depth});anchors.push(id);const aliases=[...new Set([base.replace(/-+/g,'-'),t.text.toLowerCase().replace(/[^\p{L}\p{N}_\s-]/gu,'').replace(/\s/g,'-')])].map(a=>a+(n?'-'+n:'')).filter(a=>a&&a!==id&&!anchors.includes(a));anchors.push(...aliases);return aliases.map(a=>`<span class="source-anchor" id="${esc(a)}"></span>`).join('')+`<h${t.depth} id="${esc(id)}">${text}</h${t.depth}>\n`;};
  renderer.link=function(t){return link(t.href,this.parser.parseInline(t.tokens),source);};
  renderer.image=function(t){return registerImage(t.href,t.text||t.title||'',source,chapterId).html;};
  renderer.html=function(t){
    const a=t.text.match(/^\s*<a\s+(?:id|name)=["']([\w-]+)["']\s*>\s*<\/a>\s*$/);
    if(a){anchors.push(a[1]);return `<a class="source-anchor" id="${esc(a[1])}"></a>`;}
    if(/^\s*<br\s*\/?\s*>\s*$/i.test(t.text))return '<br>';
    if(/^\s*<!--/.test(t.text))return '';
    return esc(t.text);
  };
  renderer.code=function(t){const lang=(t.lang||'').split(/\s/)[0];const code=`<pre class="${lang==='text'?'dialogue-screen':'source-code'}"><code>${esc(t.text)}</code></pre>`;return lang==='text'||!lang?code:`<details class="code-fold"><summary><span>Script / ${esc(lang)}</span><span>View source</span></summary>${code}</details>`;};
  const parser=new Marked({gfm:true,renderer});
  // Empty source anchors are block tokens, so Marked cannot split their opening
  // and closing tags. This admits only audited IDs, never arbitrary raw HTML.
  parser.use({extensions:[{name:'sourceAnchor',level:'block',start(src){return src.match(/^<a\s+(?:id|name)=["'][\w-]+["']\s*>\s*<\/a>\s*$/m)?.index;},tokenizer(src){const m=src.match(/^<a\s+(?:id|name)=["']([\w-]+)["']\s*>[ \t]*<\/a>[ \t]*(?:\n|$)/);if(m)return {type:'sourceAnchor',raw:m[0],id:m[1]};},renderer(t){anchors.push(t.id);return `<span class="source-anchor" id="${esc(t.id)}"></span>\n`;}}]});
  let html=parser.parse(raw);
  // A block image cannot remain nested in the paragraph emitted by GFM.
  html=html.replace(/<p>(\s*<figure[\s\S]*?<\/figure>\s*)<\/p>/g,'$1');
  return {html,headings,anchors};
}
function splitMarkdown(raw,p) {
  const lines=raw.split('\n');let depth=p===friendsPath?3:2;
  const points=[];let fenced=false;
  lines.forEach((line,i)=>{if(/^\s*```|^\s*~~~/.test(line)){fenced=!fenced;return;}if(fenced)return;const m=line.match(/^(#{1,6})\s+(.+)$/);if(m&&m[1].length===depth)points.push({line:i,title:m[2]});});
  if(points.length<2 || raw.length<20000)return [{id:'overview',title:'Full document',raw}];
  const starts=[{line:0,title:'Overview'},...points.filter(x=>x.line>0)];
  const seen=new Map();return starts.map((s,i)=>{let start=s.line;if(start>0 && /^<a id=/.test(lines[start-1]))start--;let end=starts[i+1]?.line??lines.length;if(end>0&&/^<a id=/.test(lines[end-1]))end--;const base=slug(s.title)||'overview',n=seen.get(base)||0;seen.set(base,n+1);return{id:base+(n?'-'+n:''),title:s.title,raw:lines.slice(start,end).join('\n')};});
}
const docs=[];
for(const p of [...new Set(sources)].sort((a,b)=>(specialOrder.get(a)??50)-(specialOrder.get(b)??50)||a.localeCompare(b))) {
  const raw=fs.readFileSync(p,'utf8'),meta=curated.get(p)||{};const rel=relative(p);
  sourcePins.push({path:rel,sha256:sha(raw),bytes:Buffer.byteLength(raw)});
  const title=meta.title||raw.match(/^#\s+(.+)$/m)?.[1]||path.basename(p);
  const doc={id:ids.get(p),path:p,relative:rel,sourceHref:fileHref(p),title,category:groupFor(p),scope:meta.status||(/\/owner-review-36m\//.test(rel)?'current':rel.startsWith('_local/')?'historical':'reference'),build:meta.buildScope||'',previewBuild:supplementalByPath.get(p)?.build||'',featured:specialOrder.has(p),chapters:[],sha256:sha(raw),bytes:Buffer.byteLength(raw),notes:meta.notes||''};
  if(p===latestPath){doc.scope='current-feature';doc.build=current.build+' · targeted feature review';}
  if(p===rainbowPath) {
    const r=JSON.parse(fs.readFileSync(path.join(root,'_local/review-hub-inputs/rainbow-structure.json')));
    let html=r.html_fragment;html=html.replace(/<a\b([^>]*?)href="([^"]+)"([^>]*)>([\s\S]*?)<\/a>/g,(_,a,h,b,t)=>link(h.replaceAll('&amp;','&'),t,p));
    // Keep every original article intact; new CSS controls its presentation.
    html=html.replace(/<img\b([^>]*?)src="([^"]+)"([^>]*)>/g,(_,a,h,b)=>{const alt=(a+b).match(/alt="([^"]*)"/)?.[1]||'Original Rainbow review image';return registerImage(h,alt,p,'rainbow-full').html;});
    const anchors=[...html.matchAll(/\bid="([^"]+)"/g)].map(m=>m[1]);
    doc.chapters=[{id:'rainbow-full',title:'All legendary events',html,headings:r.events.map(x=>({id:x.fragment_anchor,text:x.event_id+' · '+x.title,depth:2})),anchors,plain:html.replace(/<[^>]*>/g,' ')}];doc.scope='feature-reference';doc.build='Original candidate30f / earlier image labels retained';
  } else {
    doc.chapters=splitMarkdown(raw,p).map(c=>{const rendered=renderMarkdown(c.raw,p,c.id);return {id:c.id,title:c.title,...rendered,plain:c.raw};});
  }
  doc.search=(doc.title+' '+rel+' '+doc.chapters.map(c=>c.plain).join('\n')).toLowerCase();
  doc.excerpt=raw.replace(/!\[[^\]]*\]\([^)]*\)/g,'').replace(/\[([^\]]+)\]\([^)]*\)/g,'$1').replace(/[#*_`>|]/g,'').replace(/\s+/g,' ').slice(0,240);
  docs.push(doc);
}
const images=[...imageMap.values()];const featured={pikachu:latestPath?ids.get(latestPath):null,friends:ids.get(friendsPath),rainbow:ids.get(rainbowPath),rocket:ids.get(rocketPath),characters:ids.get(characterPath)};
// A focused, read-only mood review derived from the exact current source record.
// Never invent an image, promote a missing capture, or copy dialogue by hand.
let pikachuMoods=[],pikachuSummary=null;
if(currentCaptureIndex?.outcomes?.length && currentCaptureIndex.outcomes.every(o=>o.event_id?.startsWith('PC02-'))) {
  if(currentCaptureIndex.rom_sha256!==current.ROM)throw Error('Pikachu capture index ROM does not match current feature');
  const review=docs.find(d=>d.id===featured.pikachu);
  pikachuMoods=currentCaptureIndex.outcomes.map(o=>{
    const source=path.resolve(root,o.source_file);
    if(!source.startsWith(root+path.sep))throw Error('Pikachu source escapes workspace');
    const lines=fs.readFileSync(source,'utf8').split('\n');
    const sourceLine=lines.findIndex(l=>l===o.script_label+':'||l===o.script_label+'::')+1;
    const textLine=lines.findIndex(l=>l===o.text_label+':'||l===o.text_label+'::')+1;
    if(!sourceLine||!textLine)throw Error('Missing Pikachu source label: '+o.event_id);
    let text='';
    for(let i=textLine;i<lines.length&&(!lines[i]||/^\s/.test(lines[i]));i++) {
      const m=lines[i].match(/^\s*\.string\s+("(?:[^"\\]|\\.)*")/);
      if(m)text+=JSON.parse(m[1]);
    }
    if(!text.endsWith('$')||JSON.stringify([text.slice(0,-1)])!==JSON.stringify(o.dialogue_pages))throw Error('Pikachu source dialogue mismatch: '+o.event_id);
    const anchor=slug(o.event_id+' — '+o.name);
    if(!review.chapters.some(c=>c.anchors.includes(anchor)))throw Error('Missing mood review anchor: '+anchor);
    const captures=currentCaptureIndex.captures.filter(c=>c.event_id===o.event_id).map(c=>{
      const p=path.resolve(root,c.path),item=imageMap.get(p);
      if(!item||c.kind!=='native_gameplay'||c.rom_sha256!==current.ROM||c.script_label!==o.script_label||sha(fs.readFileSync(p))!==c.sha256)throw Error('Invalid native mood capture: '+p);
      return {...c,imageId:item.id};
    });
    // Show the actual dialogue first; keep animation and field-return stills
    // as separately captioned evidence, never a substitute for that textbox.
    captures.sort((a,b)=>{
      const score=c=>c.locked&&/_text_/.test(path.basename(c.path))?0:c.locked&&!/_motion_/.test(path.basename(c.path))?1:2;
      return score(a)-score(b);
    });
    const category=o.reaction_value<2?'warming':o.reaction_value<4?'friendly':o.reaction_value<6?'devoted':'situations';
    return {...o,triggerOriginal:o.trigger,trigger:o.trigger.replace(/([a-z;])(?=\d)/gi,'$1 '),sourceLine,textLine,sourceHref:fileHref(source)+'#L'+sourceLine,textSourceHref:fileHref(source)+'#L'+textLine,reviewHref:'#read='+review.id+'&part='+encodeURIComponent(anchor),category,captures,nativeStatus:captures.length?'CAPTURED':'NOT RUN'};
  });
  pikachuSummary={build:current.build,ROM:current.ROM,implemented:pikachuMoods.length,captured:pikachuMoods.filter(o=>o.captures.length).length,pending:pikachuMoods.filter(o=>!o.captures.length).length,reviewHref:'#read='+review.id,indexHref:fileHref(extraCapturePath)};
}
const heroPath=current?.heroPath?path.resolve(root,current.heroPath):path.join(root,'_local/evidence/friends-story-01/native-execution-36m-01/runtime-kit/screenshots/36m_M_Lugia_filter_clear_adults_f65729.png');
let hero=images.find(i=>i.path===heroPath);if(!hero)hero=registerImage(heroPath,'New Bark campsite · actual 36M capture',friendsPath,'fg21').item;
const data={version:1,generatedDate:new Intl.DateTimeFormat('en-US',{month:'long',day:'numeric',year:'numeric',timeZone:'America/New_York'}).format(new Date()),workspace:root,build:current?.build||'36M',ROM:current?.ROM||'8cda75eb36d9fb578b4771f678557fe838fa7ca132cf3c56800fd98f6db5650d',headroom:current?.headroom??857244,latest:latestPath?{docId:ids.get(latestPath),title:current.title,description:current.description}:null,docs,images,featured,hero:hero.id,pikachuMoods,pikachuSummary,friendsOutline:[...friends.events,...friends.battles].map(e=>({id:e.id,title:e.title,kind:e.kind,anchor:e.section?.recommended_slug||e.id.toLowerCase(),line:e.section?.line})),categories:[['stories','Story reviews'],['design','Story scripts & plans'],['visuals','Art & maps'],['decisions','Feedback & decisions'],['engineering','Builds & tests'],['project','Project documents'],['archive','Evidence archive']]};
// A separate campaign index reconciles the latest preview with the original
// feature evidence. It never relabels the 36P moods or historical screenshots.
const journeyPath=path.join(root,'_local/review-hub-inputs/campaign-journey.json');
if(fs.existsSync(journeyPath)){
  const journey=JSON.parse(fs.readFileSync(journeyPath));
  if(journey.schema!=='campaign-journey-1')throw Error('Unsupported campaign guide schema');
  const bindRef=r=>{
    const p=path.resolve(root,r.path),d=docs.find(d=>d.path===p);
    if(!d)throw Error('Campaign reference missing: '+r.path);
    let part=r.part||'';
    if(r.event&&!part){
      part=d.chapters.flatMap(c=>c.headings).find(h=>new RegExp('^'+r.event+'(?:\\s|[—–:])').test(h.text))?.id||'';
      if(!part&&d.chapters.some(c=>c.anchors.includes(r.event)))part=r.event;
      if(!part)throw Error('Campaign event anchor missing: '+r.event+' in '+r.path);
    }
    if(part&&!d.chapters.some(c=>c.id===part||c.anchors.includes(part)))throw Error('Campaign section missing: '+part);
    return {...r,docId:d.id,href:'#read='+d.id+(part?'&part='+encodeURIComponent(part):'')};
  };
  const eventIds=new Set();
  journey.events=journey.events.map(e=>{
    if(eventIds.has(e.id))throw Error('Duplicate campaign event: '+e.id);eventIds.add(e.id);
    const p=path.resolve(root,e.source.path);
    if(!p.startsWith(root+path.sep))throw Error('Campaign source outside workspace');
    const line=fs.readFileSync(p,'utf8').split('\n')[e.source.line-1];
    if(line!==e.source.label+':'&&line!==e.source.label+'::')throw Error('Campaign label drift: '+e.id);
    const review=bindRef(e.review),d=docs.find(d=>d.id===review.docId);
    const part=decodeURIComponent(review.href.split('&part=')[1]||'');
    const chapter=d.chapters.find(c=>c.id===part||c.anchors.includes(part));
    // Only source-bound native images may illustrate the route. Broader
    // historic pages remain available through their full original review.
    const image=images.find(i=>i.build_id&&i.type==='Native capture'&&(e.capturePath?i.path===e.capturePath:i.script_label===e.source.label)&&i.references.some(r=>r.docId===d.id));
    return {...e,review,sourceHref:fileHref(p)+'#L'+e.source.line,imageId:image?.id||null};
  });
  journey.chapters=journey.chapters.map(c=>{
    if(c.events.some(id=>!eventIds.has(id)))throw Error('Unknown campaign chapter event');
    return {...c,refs:c.refs.map(bindRef)};
  });
  journey.pending=journey.pending.map(e=>({...e,review:bindRef(e.review)}));
  journey.updates=journey.updates.map(u=>({...u,review:bindRef(u.review)}));
  journey.candidate.review=bindRef(journey.candidate.review);
  journey.candidate.manifestHref=fileHref(path.resolve(root,journey.candidate.manifestPath));
  const manifest=JSON.parse(fs.readFileSync(path.resolve(root,journey.candidate.manifestPath)));
  if(manifest.source_commit!=='167aa6d537b109bb229c231ddce4616974c4da71')throw Error('Campaign source pin mismatch');
  if(manifest.artifacts.find(a=>a.kind==='ROM')?.sha256!==journey.candidate.ROM)throw Error('Campaign ROM mismatch');
  const romMap=manifest.artifacts.find(a=>a.kind==='MAP');
  const mapText=fs.readFileSync(romMap.path,'utf8');
  const romRegion=mapText.match(/^rom\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)/mi);
  const romEnd=mapText.match(/^\s*0x([0-9a-f]+)\s+__rom_end\b/mi);
  if(journey.candidate.used+journey.candidate.headroom!==journey.candidate.capacity)throw Error('Campaign ROM arithmetic mismatch');
  if(!romRegion||!romEnd||parseInt(romEnd[1],16)-parseInt(romRegion[1],16)!==journey.candidate.used||parseInt(romRegion[2],16)!==journey.candidate.capacity)throw Error('Campaign linked ROM budget mismatch');
  journey.guide=bindRef({path:journey.guidePath});
  data.journey=journey;
  const guide=docs.find(d=>d.id===journey.guide.docId);guide.category='stories';guide.scope='current-guide';guide.build='37C source / original evidence labels';
}
data.previewReviews=supplementalReviews.filter(r=>r.featured).map(r=>({docId:ids.get(r.path),build:r.build,title:r.cardTitle||docs.find(d=>d.id===ids.get(r.path))?.title,description:r.description||'',letter:r.letter||'T'}));
if(supplementalReviews.some(r=>r.category==='characters'))data.categories.push(['characters','Characters & player art']);
fs.mkdirSync(out,{recursive:true});
const css=fs.readFileSync(path.join(here,'hub.css'),'utf8'),js=fs.readFileSync(path.join(here,'hub.js'),'utf8'),shell=fs.readFileSync(path.join(here,'shell.html'),'utf8');
const payload=JSON.stringify(data).replaceAll('<','\\u003c').replaceAll('\u2028','\\u2028').replaceAll('\u2029','\\u2029');
const output=shell.replace('/*__CSS__*/',()=>css).replace('/*__JS__*/',()=>js).replace('__DATA__',()=>payload).replace('__BUILD_LABEL__',()=>esc(data.journey?data.journey.candidate.build+' preview':data.build));
fs.writeFileSync(path.join(out,'index.html'),output);
const generatorPins=['build.mjs','shell.html','hub.css','hub.js','README.md'].map(p=>path.join(here,p)).concat([inventoryPath,path.join(root,'_local/review-hub-inputs/friends-structure.json'),path.join(root,'_local/review-hub-inputs/rainbow-structure.json')]).map(p=>({path:relative(p),sha256:sha(fs.readFileSync(p))}));
for(const p of [current?currentPath:null,extraCapturePath,...historicalCapturePaths])if(p)generatorPins.push({path:relative(p),sha256:sha(fs.readFileSync(p))});
for(const p of [fs.existsSync(supplementalPath)?supplementalPath:null,...supplementalCapturePaths])if(p)generatorPins.push({path:relative(p),sha256:sha(fs.readFileSync(p))});
if(fs.existsSync(journeyPath))generatorPins.push({path:relative(journeyPath),sha256:sha(fs.readFileSync(journeyPath))});
const validation={schema:'offline-review-hub-build-1',createdUTC:new Date().toISOString(),documents:docs.length,images:images.length,chapters:docs.reduce((a,d)=>a+d.chapters.length,0),sourcePins,generatorPins,excludedContent:['Ignored reconstructed upstream scratch/recon documentation; not owner-authored review material'],missingLocalImages:[...missing],blockedActiveLinks:[...blocked],features:{offline:true,noExternalRuntimeDependencies:true,gameplayOrGameSourceChanged:false,notes:'Browser-local; exported only by owner action'},browserVisualReview:{status:'NOT RUN',reason:'Browser automation policy rejected local-file navigation. No alternate browser/server workaround attempted; owner can open the file directly.'},output:{path:relative(path.join(out,'index.html')),bytes:Buffer.byteLength(output),sha256:sha(output)},renderer:{name:'marked',version:JSON.parse(fs.readFileSync(path.join(modules,'marked/package.json'))).version,node:process.version}};
fs.writeFileSync(path.join(out,'manifest.json'),JSON.stringify(validation,null,2)+'\n');
fs.writeFileSync(path.join(out,'README.txt'),'Open index.html in a browser. Everything is local and offline; no server is needed.\nOriginal documents and evidence are preserved. Historical results keep their build scope.\nFeedback notes are stored in this browser; use Export notes to keep a JSON copy.\nTo regenerate: run scripts/review_hub/build.mjs with the bundled Node runtime.\n');
console.log(JSON.stringify({documents:docs.length,chapters:validation.chapters,images:images.length,missingImages:missing.size,output:path.join(out,'index.html'),bytes:validation.output.bytes}));
