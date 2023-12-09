import fs from 'fs';

const content = fs.readFileSync('assets/day1/in.txt', 'utf-8').split('\n');

const table = {
  one: 1,
  two: 2,
  three: 3,
  four: 4,
  five: 5,
  six: 6,
  seven: 7,
  eight: 8,
  nine: 9,
  1: 1,
  2: 2,
  3: 3,
  4: 4,
  5: 5,
  6: 6,
  7: 7,
  8: 8,
  9: 9,
};

const answer = content
  .map(line => {
    let mnIdx = Number.MAX_SAFE_INTEGER,
      mnValue = -1;
    let mxIdx = Number.MIN_SAFE_INTEGER,
      mxValue = -1;
    for (const [key, value] of Object.entries(table)) {
      const id = line.indexOf(key);
      if (id !== -1 && id < mnIdx) {
        mnIdx = id;
        mnValue = value;
      }
      const rid = line.lastIndexOf(key);
      if (rid !== -1 && rid > mxIdx) {
        mxIdx = rid;
        mxValue = value;
      }
    }
    if (mnValue === -1 || mxValue === -1) throw new Error();
    // console.log(line, mnValue * 10 + mxValue);
    return mnValue * 10 + mxValue;
  })
  .reduce((a, b) => a + b, 0);

console.log(answer);
