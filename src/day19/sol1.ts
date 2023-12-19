import fs from 'fs';

const content = fs.readFileSync('./assets/day19/in.txt', 'utf-8').split('\n');

const rules: Map<string, Rule> = new Map();

interface Rule {
  branches: Array<
    | { key: string; op: '<' | '>'; value: number; target: string }
    | { target: string }
  >;
}

type Env = Record<string, number>;

let ans = 0;
for (const line of content) {
  if (line.length === 0) continue;
  if (line[0] === '{') {
    const env = Object.fromEntries(
      line
        .slice(1, line.length - 1)
        .split(',')
        .map(t => {
          const [key, value] = t.split('=');
          return [key, +value] as const;
        })
    );
    ans += solve(env);
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
            key: match[1],
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

console.log(ans);

function solve(env: Env) {
  let state = 'in';
  while (state !== 'R' && state !== 'A') {
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
  const sum = Object.values(env).reduce((p, c) => p + c, 0);
  return state === 'A' ? sum : 0;
}
