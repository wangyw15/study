#include <iostream>
#include <ostream>
#include "Time.h"

Time::Time()
{
    h = m = s = 0;
}

Time::Time(unsigned long hour, unsigned long minute)
{
    if (hour >= 24)
    {
        throw hour;
    }
    h = hour;
    if (minute >= 60)
    {
        throw minute;
    }
    m = minute;
    s = 0;
}

Time::Time(unsigned long hour, unsigned long minute, unsigned long second)
{
    if (hour >= 24)
    {
        throw hour;
    }
    h = hour;
    if (minute >= 60)
    {
        throw minute;
    }
    m = minute;
    if (second >= 60)
    {
        throw minute;
    }
    s = second;
}

void Time::SetTime(unsigned long hour, unsigned long minute, unsigned long second)
{
    if (hour >= 24)
    {
        throw hour;
    }
    h = hour;
    if (minute >= 60)
    {
        throw minute;
    }
    m = minute;
    if (second >= 60)
    {
        throw minute;
    }
    s = second;
}

unsigned long Time::GetHour() const
{
    return h;
}

unsigned long Time::GetMinute() const
{
    return m;
}

unsigned long Time::GetSecond() const
{
    return s;
}

std::ostream & operator<<(std::ostream &os, const Time &t)
{
    os << std::setfill('0') << std::setw(2) << t.h
       << ":" << std::setw(2) << t.m
       << ":" << std::setw(2) << t.s
       << std::setfill(' ');
    return os;
}

std::istream & operator>>(std::istream &is, Time &t)
{
    std::cin >> t.h;
    std::cin.ignore(1, ':');
    std::cin >> t.m;
    std::cin.ignore(1, ':');
    std::cin >> t.s;
    return is;
}