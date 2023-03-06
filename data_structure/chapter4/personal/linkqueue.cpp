#include <iostream>
#include <string>
#include "headers/LinkQueue.hpp"

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

struct Airline
{
    string FlightNumber;
    DateTime DepartureTime;
    string DepartureAirport;
    DateTime ArrivalTime;
    string ArrivalAirport;
    int Seat;
    int RemainingSeat;
    int TicketPrice;

    friend istream &operator>>(istream& in, Airline &airline)
    {
        in >> airline.FlightNumber
            >> airline.DepartureTime >> airline.DepartureAirport
            >> airline.ArrivalTime >> airline.ArrivalAirport
            >> airline.Seat >> airline.RemainingSeat >> airline.TicketPrice;
        return in;
    }

    friend ostream &operator<<(ostream& out, Airline &airline)
    {
        out << "flight number: " << airline.FlightNumber << "" << endl
            << "departure from " << airline.DepartureAirport << " at " << airline.DepartureTime << endl
            << "arrive at " << airline.ArrivalAirport << " at " << airline.ArrivalTime << endl
            << "seat: " << airline.RemainingSeat << "/" << airline.Seat << endl
            << "sell at " << airline.TicketPrice << endl;
        return out;
    }
};

int main()
{
    // (1)
    Airline tempAirline;
    LinkQueue<Airline> airlines;
    cout << "the amount of data: ";
    int count = 0;
    cin >> count;
    cout << "data:" << endl;
    for (auto i = 0; i < count; i++)
    {
        cin >> tempAirline;
        airlines.EnQueue(tempAirline);
    }
    cout << endl;
    airlines.Traverse([] (Airline item) { cout << item << endl; });
    cout << endl;

    // (2)
    LinkQueue<int> queue;
    for (auto i = 0; i < 100; i++)
    {
        queue.EnQueue(i);
    }
    cout << "length: " << queue.Length() << endl << queue << endl << endl;

    cout << "dequeued 0-49, enqueued 200-249" << endl;
    for (auto i = 0; i < 50; i++)
    {
        queue.DeQueue();
    }
    for (auto i = 0; i < 50; i++)
    {
        queue.EnQueue(i + 200);
    }

    cout << "traverse:" << endl;
    queue.Traverse([](int item) { cout << item << " "; });
    cout << endl << endl;

    queue.Clear();
    cout<< "cleared: " << queue
        << "; length: " << queue.Length()
        << "; is " << (queue.IsEmpty() ? "" : "not") << "empty" << endl << endl;

    for (auto i = 100; i < 150; i++)
    {
        queue.EnQueue(i);
    }
    cout << "length: " << queue.Length() << "; head: " << queue.Head() << endl << endl;
    cout << "dequeue: " << endl;
    for (auto i = 100; i < 150; i++)
    {
        cout << queue.DeQueue() << " ";
    }
    cout << endl << endl << "length: " << queue.Length() << endl;
    return 0;
}