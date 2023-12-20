import fs from 'fs';

const content = fs.readFileSync('./assets/day20/in.txt', 'utf-8').split('\n');

interface Flip {
  type: 'flip';
  outputs: string[];
  state: boolean;
}

interface Conj {
  type: 'conj';
  inputs: Map<string, boolean>;
  outputs: string[];
}

interface Broadcaster {
  type: 'broadcaster';
  outputs: string[];
}

const modules: Map<string, Flip | Conj | Broadcaster> = new Map();

for (const line of content) {
  if (line.startsWith('broadcaster')) {
    const outputs = line.slice('broadcaster -> '.length).split(', ');
    modules.set('broadcaster', { type: 'broadcaster', outputs });
  } else if (line.startsWith('%')) {
    const [from, to] = line.split(' -> ');
    const name = from.slice(1);
    const outputs = to.split(', ');
    modules.set(name, { type: 'flip', outputs, state: false });
  } else if (line.startsWith('&')) {
    const [from, to] = line.split(' -> ');
    const name = from.slice(1);
    const outputs = to.split(', ');
    modules.set(name, { type: 'conj', inputs: new Map(), outputs });
  }
}

for (const [name, mod] of modules.entries()) {
  for (const out of mod.outputs) {
    const target = modules.get(out)!;
    if (target && target.type === 'conj') {
      target.inputs.set(name, false);
    }
  }
}

let turn = 0;
const loop = {
  st: undefined,
  tn: undefined,
  hh: undefined,
  dt: undefined,
};
function execute() {
  interface Message {
    target: string;
    from: string;
    signal: boolean;
  }

  turn++;
  const q: Message[] = [{ target: 'broadcaster', from: '', signal: false }];
  for (let i = 0; i < q.length; i++) {
    const msg = q[i];
    const mod = modules.get(q[i].target);
    if (!mod) continue;
    if (mod.type === 'broadcaster') {
      for (const out of mod.outputs) {
        q.push({ target: out, from: q[i].target, signal: msg.signal });
      }
    } else if (mod.type === 'flip') {
      if (msg.signal === false) {
        mod.state = !mod.state;
        for (const out of mod.outputs) {
          q.push({ target: out, from: q[i].target, signal: mod.state });
        }
      }
    } else if (mod.type === 'conj') {
      mod.inputs.set(msg.from, msg.signal);
      if (msg.target === 'lv' && msg.signal) {
        if (msg.from in loop) {
          if (loop[msg.from] === undefined) {
            loop[msg.from] = turn;
          }
        }
      }
      const signal = ![...mod.inputs.values()].reduce((p, v) => p && v, true);
      for (const out of mod.outputs) {
        q.push({ target: out, from: q[i].target, signal });
      }
    }
  }
}

function resetState() {
  for (const [name, mod] of modules) {
    if (mod.type === 'flip') {
      mod.state = false;
    } else if (mod.type === 'conj') {
      for (const key of mod.inputs.keys()) {
        mod.inputs.set(key, false);
      }
    }
  }
}

for (let i = 1; ; i++) {
  execute();
  if (loop.st && loop.tn && loop.hh && loop.dt) {
    break;
  }
  // const mod = modules.get('lv')! as Conj;
  // for (const [key, value] of mod.inputs) {
  //   if (value === true) {
  //     console.log(i, key);
  //   }
  // }
}
console.log(Object.values(loop).reduce((p, a) => lcm(p, a!), 1));

function gcd(a: number, b: number) {
  return !b ? a : gcd(b, a % b);
}
function lcm(a: number, b: number) {
  return (a * b) / gcd(a, b);
}
