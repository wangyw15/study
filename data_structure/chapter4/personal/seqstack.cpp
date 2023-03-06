#include <iostream>
#include <ostream>
#include <string>
#include <ios>
#include "headers/SeqStack.hpp"

using namespace std;

struct DateTime
{
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;

    bool operator<(const DateTime &other)
    {
        if (Year != other.Year)
        {
            return Year < other.Year;
        }
        else if (Month != other.Month)
        {
            return Month < other.Month;
        }
        else if (Day != other.Day)
        {
            return Day < other.Day;
        }
        else if (Hour != other.Hour)
        {
            return Hour < other.Hour;
        }
        else if (Minute != other.Minute)
        {
            return Minute < other.Minute;
        }
        else
        {
            return Second < other.Second;
        }
    }

    bool operator>(const DateTime &other)
    {
        return !(*this < other);
    }

    bool operator==(const DateTime &other)
    {
        return Year == other.Year && Month == other.Month && Day == other.Day &&
            Hour == other.Hour && Minute == other.Minute && Second == other.Second;
    }

    bool operator!=(const DateTime &other)
    {
        return !(*this == other);
    }

    bool operator<=(const DateTime &other)
    {
        return (*this == other) || (*this < other);
    }

    bool operator>=(const DateTime &other)
    {
        return (*this == other) || (*this > other);
    }

    friend ostream &operator<<(ostream& out, DateTime &dt)
    {
        out << dt.Year << "/" << dt.Month << "/" << dt.Day << " "
            << dt.Hour << ":" << dt.Minute << ":" << dt.Second;
        return out;
    }

    friend istream &operator>>(istream& in, DateTime &dt)
    {
        in >> dt.Year >> dt.Month >> dt.Day
            >> dt.Hour >> dt.Minute >> dt.Second;
        return in;
    }
};

struct Car
{
    string Plate;
    DateTime EnterTime;

    bool operator<(const Car &other)
    {
        if (EnterTime != other.EnterTime)
        {
            return EnterTime < other.EnterTime;
        }
        else
        {
            return Plate < other.Plate;
        }
    }
    
    bool operator>(const Car &other)
    {
        return !(*this < other);
    }

    friend ostream &operator<<(ostream& out, Car &car)
    {
        out << "Plate: " << car.Plate << "; Enter time: " << car.EnterTime;
        return out;
    }

    friend istream &operator>>(istream& in, Car &car)
    {
        in >> car.Plate >> car.EnterTime;
        return in;
    }
};

int main()
{
    // (1)
    Car tempCar;
    SeqStack<Car> cars;
    cout << "the amount of data: ";
    int count = 0;
    cin >> count;
    cout << "data:" << endl;
    for (auto i = 0; i < count; i++)
    {
        cin >> tempCar;
        cars.Push(tempCar);
    }
    cars.Traverse([] (Car item) { cout << item << endl; });
    cout << endl;

    // (2)
    SeqStack<int> stack;
    for (auto i = 0; i < 200; i++)
    {
        stack.Push(i);
    }
    cout << "length: " << stack.Length() << endl << endl << "traverse:" << endl;
    stack.Traverse([](int item) { cout << item << " "; });
    cout << endl << endl;

    stack.Clear();
    cout<< "cleared: " << stack
        << "; length: " << stack.Length()
        << "; is " << (stack.IsEmpty() ? "" : "not") << "empty" << endl << endl;

    for (auto i = 100; i < 150; i++)
    {
        stack.Push(i);
    }
    cout << "length: " << stack.Length() << "; top: " << stack.Top() << endl << endl;
    cout << "pop: " << endl;
    for (auto i = 100; i < 150; i++)
    {
        cout << stack.Pop() << " ";
    }
    cout << endl << endl << "length: " << stack.Length() << endl;
    return 0;
}