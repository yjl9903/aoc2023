import fs from 'fs';

const content = fs
  .readFileSync('assets/day4/in.txt', 'utf-8')
  .split('\n')
  .map(l => l.split(':')[1].trim())
  .map(l =>
    l.split('|').map(l =>
      l
        .split(' ')
        .filter(Boolean)
        .map(t => +t)
    )
  );

const answer = content
  .map(([win, my]) => {
    const set = new Set(win);
    let sum = 0;
    for (const c of my) {
      if (set.has(c)) {
        if (sum === 0) sum = 1;
        else sum *= 2;
      }
    }
    return sum;
  })
  .reduce((a, b) => a + b, 0);

console.log(answer);
