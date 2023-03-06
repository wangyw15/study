#ifndef COMMON
#include "../Common.h"
#endif

using namespace std;

EmployeeEventList::EmployeeEventList()
{
    _head = newNode();
    _tail = newNode();
    _head->next = _tail;
    _head->prev = nullptr;
    _tail->prev = _head;
    _tail->next = nullptr;
    _size = 0;
    fstream fs;
    fs.open(string(DATA_PATH) + string(EVENTS_FILE_NAME), ios::in);
    string line;
    while (getline(fs, line))
    {
        stringstream ss(line);
        auto event = newNode();
        ss >> event->ID >> event->Event;
        append(event);
    }
    fs.close();
}

EmployeeEventNode* EmployeeEventList::newNode()
{
    return new EmployeeEventNode;
}

EmployeeEventNode* EmployeeEventList::begin()
{
    return _head->next;
}

EmployeeEventNode* EmployeeEventList::end()
{
    return _tail;
}

EmployeeEventNode& EmployeeEventList::operator[](long n)
{
    auto ret = begin();
    for(long i = 0; i < n; i++)
    {
        ret = ret->next;
    }
    return *ret;
}

void EmployeeEventList::append(EmployeeEventNode *event)
{
    event->next = end();
    event->prev = end()->prev;
    end()->prev->next = event;
    end()->prev = event;
    _size++;
}

void EmployeeEventList::remove(long position)
{
    long index = 0;
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (index++ == position)
        {
            i->prev->next = i->next;
            i->next->prev = i->prev;
            delete i;
            _size--;
            break;
        }
    }
}

void EmployeeEventList::removeByID(long id)
{
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (i->ID == id)
        {
            i->prev->next = i->next;
            i->next->prev = i->prev;
            delete i;
            _size--;
        }
    }
}

void EmployeeEventList::modify(long position, EmployeeEventNode *newEvent)
{
    long index = 0;
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (index++ == position)
        {
            newEvent->next = i->next;
            newEvent->prev = i->prev;
            i->next->prev = newEvent;
            i->prev->next = newEvent;
            delete i;
            break;
        }
    }
}

size_t EmployeeEventList::size()
{
    return _size;
}

void EmployeeEventList::save()
{
    fstream fs;
    fs.open(string(DATA_PATH) + string(EVENTS_FILE_NAME), ios::out);
    for (auto i = begin(); i != end(); i = i->next)
    {
        fs << i->ID << " " << i->Event << endl;
    }
    fs.flush();
    fs.close();
}