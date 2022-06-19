@echo off
del /Q *.o > nul
cls

date < cr.txt
time < cr.txt
date < cr.txt > results_release.txt
time < cr.txt >> results_release.txt

echo about 2 minutes, please wait ...
Sorts >> results_release.txt
time < cr.txt
time < cr.txt >> results_release.txt

echo.
echo another 2 minutes, please wait again ...
Sorts >> results_release.txt
time < cr.txt
time < cr.txt >> results_release.txt
pause
