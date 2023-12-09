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
  maps.push(list.sort((a, b) => a[1] - b[1]));
  line++;
}

let ans = Number.MAX_SAFE_INTEGER;
for (let i = 0; i < seeds.length; i += 2) {
  const ranges = [[seeds[i], seeds[i + 1]]];
  for (const map of maps) {
    const next: number[][] = [];
    // console.log('Map', map);
    for (const _range of ranges) {
      const range = [..._range];
      for (const trans of map) {
        if (range[0] < trans[1] && range[0] + range[1] > trans[1]) {
          const len = trans[1] - range[0];
          next.push([range[0], len]);
          range[1] -= len;
          range[1] += len;
        }
        if (range[0] >= trans[1] && range[0] < trans[1] + trans[2]) {
          const st = range[0];
          const len = Math.min(range[1], trans[2] - (range[0] - trans[1]));
          if (len > 0) {
            next.push([trans[0] + (st - trans[1]), len]);
            range[1] -= len;
            range[0] += len;
          }
        }
      }
      if (range[1] > 0) {
        next.push([range[0], range[1]]);
      }
    }
    // console.log(ranges, next);
    ranges.splice(0, ranges.length, ...next);
  }
  ans = Math.min(ans, ...ranges.map(r => r[0]));
}
console.log(ans);
