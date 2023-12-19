import fs from 'fs';

const content = fs.readFileSync('./assets/day19/in.txt', 'utf-8').split('\n');

const rules: Map<string, Rule> = new Map();

interface Rule {
  branches: Array<
    | {
        key: 'x' | 'm' | 'a' | 's';
        op: '<' | '>';
        value: number;
        target: string;
      }
    | { target: string }
  >;
}

type Env = Record<'x' | 'm' | 'a' | 's', number>;

for (const line of content) {
  if (line.length === 0) continue;
  if (line[0] === '{') {
  } else {
    const idx = line.indexOf('{');
    const name = line.slice(0, idx);
    const parts = line
      .slice(idx + 1, line.length - 1)
      .split(',')
      .map(part => {
        if (part.includes(':')) {
          const [cond, target] = part.split(':');
          const match = /(\w+)(<|>)(\d+)/.exec(cond)!;
          return {
            key: match[1] as 'x' | 'm' | 'a' | 's',
            op: match[2] as '<' | '>',
            value: +match[3],
            target,
          };
        } else {
          return { target: part };
        }
      });
    rules.set(name, { branches: parts });
    // console.log(parts);
  }
}

function solve(env: Env) {
  const visited = new Set<string>();
  let state = 'in';
  while (state !== 'R' && state !== 'A') {
    if (visited.has(state)) break;
    visited.add(state);
    const rule = rules.get(state);
    if (!rule) {
      throw new Error(`Can not find rule ${state}`);
    }
    for (const branch of rule.branches) {
      if ('key' in branch) {
        const value = env[branch.key];
        if (branch.op === '<' && value < branch.value) {
          state = branch.target;
          break;
        } else if (branch.op === '>' && value > branch.value) {
          state = branch.target;
          break;
        }
      } else {
        state = branch.target;
        break;
      }
    }
  }
  return state === 'A';
}

const axes = {
  x: new Set([1, 4001]),
  m: new Set([1, 4001]),
  a: new Set([1, 4001]),
  s: new Set([1, 4001]),
};
for (const rule of rules.values()) {
  for (const branch of rule.branches) {
    if ('key' in branch) {
      const point = branch.op === '<' ? branch.value : branch.value + 1;
      axes[branch.key].add(point);
    }
  }
}
const pos = {
  x: [...axes.x].sort((a, b) => a - b),
  m: [...axes.m].sort((a, b) => a - b),
  a: [...axes.a].sort((a, b) => a - b),
  s: [...axes.s].sort((a, b) => a - b),
};
let ans = 0;
for (let i = 0; i + 1 < pos.x.length; i++) {
  for (let j = 0; j + 1 < pos.m.length; j++) {
    for (let p = 0; p + 1 < pos.a.length; p++) {
      for (let q = 0; q + 1 < pos.s.length; q++) {
        const flag = solve({
          x: pos.x[i],
          m: pos.m[j],
          a: pos.a[p],
          s: pos.s[q],
        });
        if (flag) {
          ans +=
            (pos.x[i + 1] - pos.x[i]) *
            (pos.m[j + 1] - pos.m[j]) *
            (pos.a[p + 1] - pos.a[p]) *
            (pos.s[q + 1] - pos.s[q]);
        }
      }
    }
  }
}
console.log(ans);
// 131899818301477
