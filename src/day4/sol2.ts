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

const match = content.map(([win, my]) => {
  const set = new Set(win);
  let sum = 0;
  for (const c of my) {
    if (set.has(c)) {
      sum++;
    }
  }
  return sum;
});

const copy = content.map(() => 1);
for (let i = 0; i < match.length; i++) {
  for (let j = i + 1; j <= i + match[i] && j < copy.length; j++) {
    copy[j] += copy[i];
  }
}
console.log(copy.reduce((a, b) => a + b, 0));
