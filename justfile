set windows-shell := ["powershell.exe", "-c"]

day01:
  g++ src/day01/sol1.cpp -o day01.exe
  Get-Content assets/day01/in.txt | ./day01.exe
  rm ./*.exe
  tsx src/day01/sol2.ts

day02:
  tsx src/day02/sol1.ts
  tsx src/day02/sol2.ts

day03:
  g++ src/day03/sol1.cpp -o day03.exe
  Get-Content assets/day03/in.txt | ./day03.exe
  g++ src/day03/sol2.cpp -o day03.exe
  Get-Content assets/day03/in.txt | ./day03.exe
  rm ./*.exe

day04:
  tsx src/day04/sol1.ts
  tsx src/day04/sol2.ts

day05:
  tsx src/day05/sol1.ts
  tsx src/day05/sol2.ts

day06:
  g++ src/day06/sol1.cpp -o day06.exe
  Get-Content assets/day06/in.txt  | ./day06.exe
  Get-Content assets/day06/in2.txt | ./day06.exe
  rm ./*.exe

day07:
  g++ src/day07/sol1.cpp -o day07.out --std=c++20
  ./day07.out < assets/day07/in.txt
  g++ src/day07/sol2.cpp -o day07.out --std=c++17
  ./day07.out < assets/day07/in.txt
  rm ./*.out

day08:
  g++ src/day08/sol1.cpp -o day08.out --std=c++17
  ./day08.out < assets/day08/in.txt
  g++ src/day08/sol2.cpp -o day08.out --std=c++17
  ./day08.out < assets/day08/in.txt
  rm ./*.out

day09:
  g++ src/day09/sol1.cpp -o day09.out --std=c++17
  ./day09.out < assets/day09/in.txt
  g++ src/day09/sol2.cpp -o day09.out --std=c++17
  ./day09.out < assets/day09/in.txt
  rm ./*.out

day10:
  g++ src/day10/sol1.cpp -o day10.exe
  Get-Content assets/day10/in.txt | ./day10.exe
  g++ src/day10/sol2.cpp -o day10-2.exe
  Get-Content assets/day10/in.txt | ./day10.exe > test.out
  Get-Content assets/day10/in.txt | ./day10.exe | ./day10-2.exe
  rm ./*.exe

day11:
  g++ src/day11/sol1.cpp -o day11.exe
  Get-Content assets/day11/in.txt | ./day11.exe 2
  Get-Content assets/day11/in.txt | ./day11.exe 1000000
  rm ./*.exe

day12:
  # g++ src/day12/sol1.cpp -o day12.out --std=c++17
  # ./day12.out < assets/day12/in.txt
  g++ src/day12/sol2.cpp -o day12.out --std=c++17
  ./day12.out < assets/day12/in.txt
  rm ./*.out

day13:
  g++ src/day13/sol1.cpp -o day13.exe
  Get-Content assets/day13/in.txt | ./day13.exe
  g++ src/day13/sol2.cpp -o day13.exe
  Get-Content assets/day13/in.txt | ./day13.exe
  rm ./*.exe

day14:
  g++ src/day14/sol1.cpp -o day14.exe
  Get-Content assets/day14/in.txt | ./day14.exe
  g++ src/day14/sol2.cpp -o day14.exe
  Get-Content assets/day14/in.txt | ./day14.exe
  rm ./*.exe

day15:
  g++ src/day15/sol1.cpp -o day15.exe
  Get-Content assets/day15/in.txt | ./day15.exe
  g++ src/day15/sol2.cpp -o day15.exe
  Get-Content assets/day15/in.txt | ./day15.exe
  rm ./*.exe

day16:
  g++ src/day16/sol1.cpp -o day16.exe
  Get-Content assets/day16/in.txt | ./day16.exe
  g++ src/day16/sol2.cpp -o day16.exe
  Get-Content assets/day16/in.txt | ./day16.exe
  rm ./*.exe

day17:
  g++ src/day17/sol1.cpp -o day17.out --std=c++17
  ./day17.out < assets/day17/in.txt
  g++ src/day17/sol2.cpp -o day17.out --std=c++17
  ./day17.out < assets/day17/in.txt
  rm ./*.out

day18:
  g++ src/day18/sol1.cpp -o day18.exe
  Get-Content assets/day18/in.txt | ./day18.exe
  g++ src/day18/sol2.cpp -o day18.exe
  Get-Content assets/day18/in.txt | ./day18.exe
  rm ./*.exe

day19:
  tsx src/day19/sol1.ts
  tsx src/day19/sol2.ts

day20:
  tsx src/day20/sol1.ts
  tsx src/day20/sol2.ts

day21:
  g++ src/day21/sol2.cpp -o day21.exe
  Get-Content assets/day21/in.txt | ./day21.exe
  rm ./*.exe

clean:
  rm ./*.exe  
  rm ./*.out
