@echo off
del /Q *.o > nul
cls

date < cr.txt
time < cr.txt
date < cr.txt > results_debug.txt
time < cr.txt >> results_debug.txt

echo about 4 minutes, please wait ...
Sorts >> results_debug.txt
time < cr.txt
time < cr.txt >> results_debug.txt

echo.
echo another 4 minutes, please wait again ...
Sorts >> results_debug.txt
time < cr.txt
time < cr.txt >> results_debug.txt
pause
