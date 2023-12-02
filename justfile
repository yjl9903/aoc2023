set shell := ["powershell.exe", "-c"]

day1:
  g++ day1.cpp -o day1.exe
  Get-Content assets/day1/in.txt | ./day1.exe

day2:
  tsx day2.ts

clean:
  rm *.exe  
