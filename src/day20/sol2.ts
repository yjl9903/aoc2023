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

// const count = { low: 0, high: 0 };
function execute() {
  interface Message {
    target: string;
    from: string;
    signal: boolean;
  }

  let ok = 0;
  const q: Message[] = [{ target: 'broadcaster', from: '', signal: false }];
  for (let i = 0; i < q.length; i++) {
    const msg = q[i];
    if (msg.target === 'rx' && !msg.signal) {
      ok++;
    }
    // if (msg.signal) {
    //   count.high++;
    // } else {
    //   count.low++;
    // }
    // console.log(msg);
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
      mod.inputs.set(q[i].from, msg.signal);
      const signal = ![...mod.inputs.values()].reduce((p, v) => p && v, true);
      for (const out of mod.outputs) {
        q.push({ target: out, from: q[i].target, signal });
      }
    }
  }
  if (ok) {
    console.log(ok);
  }
  return ok === 1;
}

function getState() {
  const flip: Record<string, boolean> = {};
  const conj: Record<string, Map<string, boolean>> = {};
  for (const [name, mod] of modules) {
    if (mod.type === 'flip') {
      flip[name] = mod.state;
    } else if (mod.type === 'conj') {
      conj[name] = mod.inputs;
    }
  }
  return { flip, conj };
}

let count = 0;
while (true) {
  count++;
  // console.log(getState());
  if (execute()) {
    break;
  }
  // console.log(getState());
}
console.log(count);
