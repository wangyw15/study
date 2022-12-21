#ifndef TIME
#define TIME

#include <ostream>
#include <iomanip>

class Time
{
public:
    Time();
    Time(unsigned long hour, unsigned long minute);
    Time(unsigned long hour, unsigned long minute, unsigned long second);
    void SetTime(unsigned long hour, unsigned long minute, unsigned long second);
    unsigned long GetHour() const;
    unsigned long GetMinute() const;
    unsigned long GetSecond() const;
private:
    long h, m, s;
    friend std::ostream & operator<<(std::ostream & os, const Time & t);
    friend std::istream & operator>>(std::istream & is, Time & t);
};

#endif