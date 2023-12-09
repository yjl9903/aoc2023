set windows-shell := ["powershell.exe", "-c"]

day1:
  g++ src/day1/sol1.cpp -o day1.exe
  Get-Content assets/day1/in.txt | ./day1.exe
  rm ./*.exe
  tsx src/day1/sol2.ts

day2:
  tsx src/day2/sol1.ts
  tsx src/day2/sol2.ts

day3:
  g++ src/day3/sol1.cpp -o day3.exe
  Get-Content assets/day3/in.txt | ./day3.exe
  g++ src/day3/sol2.cpp -o day3.exe
  Get-Content assets/day3/in.txt | ./day3.exe
  rm ./*.exe

day4:
  tsx src/day4/sol1.ts
  tsx src/day4/sol2.ts

day5:
  tsx src/day5/sol1.ts
  tsx src/day5/sol2.ts

day6:
  g++ src/day6/sol1.cpp -o day6.exe
  Get-Content assets/day6/in.txt  | ./day6.exe
  Get-Content assets/day6/in2.txt | ./day6.exe
  rm ./*.exe

day7:
  g++ src/day7/sol1.cpp -o day7.out --std=c++20
  ./day7.out < assets/day7/in.txt
  g++ src/day7/sol2.cpp -o day7.out --std=c++17
  ./day7.out < assets/day7/in.txt
  rm ./*.out

day8:
  g++ src/day8/sol1.cpp -o day8.out --std=c++17
  ./day8.out < assets/day8/in.txt
  g++ src/day8/sol2.cpp -o day8.out --std=c++17
  ./day8.out < assets/day8/in.txt
  rm ./*.out

day9:
  g++ src/day9/sol1.cpp -o day9.out --std=c++17
  ./day9.out < assets/day9/in.txt
  g++ src/day9/sol2.cpp -o day9.out --std=c++17
  ./day9.out < assets/day9/in.txt
  rm ./*.out

clean:
  rm ./*.exe  
  rm ./*.out
