#include <iostream>
#include <ostream>
#include <string>
#include <ios>
#include "headers/SeqStack.hpp"

using namespace std;

struct Car
{
    string Plate;
    int Year;
    int Month;
    int Day;
    int Hour;
    int Minute;
    int Second;

    bool operator<(const Car &other)
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
        else if (Second != other.Second)
        {
            return Second < other.Second;
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
        out << "Plate: " << car.Plate << "; Enter time: "
            << car.Year << "/" << car.Month << "/" << car.Day << " "
            << car.Hour << ":" << car.Minute << ":" << car.Second;
        return out;
    }

    friend istream &operator>>(istream& in, Car &car)
    {
        in >> car.Plate
            >> car.Year >> car.Month >> car.Day
            >> car.Hour >> car.Minute >> car.Second;
        return in;
    }
};

int main()
{
    // (1)
    /*Car tempCar;
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
    cout << endl;*/

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