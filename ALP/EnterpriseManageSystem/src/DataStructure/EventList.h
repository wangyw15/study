#define EVENT_LIST

#ifndef COMMON
#include "../Common.h"
#endif

struct EmployeeEventNode
{
    long ID;
    std::string Event;

    EmployeeEventNode *prev;
    EmployeeEventNode *next;
};

class EmployeeEventList
{
private:
    EmployeeEventNode *_head, *_tail;
    long _size;

public:
    EmployeeEventList();
    EmployeeEventNode* newNode();
    EmployeeEventNode* begin();
    EmployeeEventNode* end();
    EmployeeEventNode& operator[](long n);
    void append(EmployeeEventNode *event);
    void remove(long position);
    void removeByID(long id);
    void modify(long position, EmployeeEventNode *newEvent);
    size_t size();
    void save();
};