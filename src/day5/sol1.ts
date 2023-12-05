import fs from 'fs';

const content = fs.readFileSync('assets/day5/in.txt', 'utf-8').split('\n');

const seeds = content[0]
  .replace('seeds: ', '')
  .split(' ')
  .map(t => t.trim())
  .filter(Boolean)
  .map(t => +t);

const maps: [number, number, number][][] = [];
for (let i = 0, line = 2; i < 7; i++) {
  if (!content[line].endsWith('map:')) throw new Error();
  line++;
  const list: [number, number, number][] = [];
  while (line < content.length && content[line] !== '') {
    const [a, b, c] = content[line].split(' ');
    list.push([+a, +b, +c]);
    line++;
  }
  maps.push(list);
  line++;
}

let ans = Number.MAX_SAFE_INTEGER;
for (const seed of seeds) {
  let cur = seed;
  for (const map of maps) {
    for (const [dst, sst, len] of map) {
      if (cur >= sst && cur < sst + len) {
        cur = dst + (cur - sst);
        break;
      }
    }
  }
  ans = Math.min(ans, cur);
}
console.log(ans);
