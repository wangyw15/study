#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

bool isLeapYear(long year)
{
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
    return false;
}

long calculateDays(long year, long month, long day)
{
    if(month == 2 && day == 29)
    {
        return 31 + 29;
    }
    else
    {
        long totalDays = day;
        if(month > 2 && isLeapYear(year))
        {
            totalDays++;
        }
        for(long i = 1; i < month; i++)
        {
            /*switch(i)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    totalDays += 31;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    totalDays += 30;
                    break;
                case 2:
                    totalDays += 28;
                    break;
            }*/
            if((i <= 7 && i % 2 == 1) || (i >= 8 && i % 2 == 0))
            {
                totalDays += 31;
            }
            else if(i == 2)
            {
                totalDays += 28;
            }
            else
            {
                totalDays += 30;
            }
        }
        return totalDays;
    }
}

int main()
{
    long index = 1, year, month, day;
    while (cin >> year >> month >> day)
    {
        printf("Case %d: %.2d/%.2d/%.2d, %d\n", index++, month, day, year, calculateDays(year, month, day));
    }
    return 0;
}