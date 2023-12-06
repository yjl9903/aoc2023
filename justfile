set shell := ["powershell.exe", "-c"]

day1:
  g++ src/day1/sol1.cpp -o day1.exe
  Get-Content assets/day1/in.txt | ./day1.exe
  rm *.exe
  tsx src/day1/sol2.ts

day2:
  tsx src/day2/sol1.ts
  tsx src/day2/sol2.ts

day3:
  g++ src/day3/sol1.cpp -o day3.exe
  Get-Content assets/day3/in.txt | ./day3.exe
  g++ src/day3/sol2.cpp -o day3.exe
  Get-Content assets/day3/in.txt | ./day3.exe
  rm *.exe

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
  rm *.exe

clean:
  rm *.exe  
