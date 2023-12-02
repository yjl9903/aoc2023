import fs from 'fs';

const content = fs.readFileSync('assets/day2/in.txt', 'utf-8').split('\n');

const RED = 12;
const GREEN = 13;
const BLUE = 14;

const answer = content
  .map(line => {
    const id = getId();
    const games = getGames();
    const inValid = games.some(
      g => g.blue > BLUE || g.red > RED || g.green > GREEN
    );

    return inValid ? 0 : id;

    function getId() {
      const match = /Game (\d+):/.exec(line)!;
      return +match[1];
    }

    function getGames() {
      const games = line
        .replace(/Game \d+: /, '')
        .split(';')
        .map(d => d.trim());
      return games.map(game => {
        const piece = game.split(',').map(d => d.trim());
        let red = 0;
        let green = 0;
        let blue = 0;

        for (const t of piece) {
          const num = /^(\d+)/.exec(t)![1];
          if (t.includes('blue')) {
            blue += +num;
          } else if (t.includes('green')) {
            green += +num;
          } else if (t.includes('red')) {
            red += +num;
          }
        }

        return {
          red,
          green,
          blue,
        };
      });
    }
  })
  .reduce((a, b) => a + b, 0);

console.log(answer);
