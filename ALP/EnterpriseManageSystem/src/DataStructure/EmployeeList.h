#define EMPLOYEE_LIST

#ifndef COMMON
#include "../Common.h"
#endif

struct EmployeeNode
{
    long ID;
    std::string Name;
    std::string Department;
    long Salary;
    long DirectLeadership;

    EmployeeNode *prev;
    EmployeeNode *next;
};

class EmployeeList
{
private:
    EmployeeNode *_head, *_tail;
    long _size;

public:
    EmployeeList();
    EmployeeNode* newNode();
    EmployeeNode* begin();
    EmployeeNode* end();
    EmployeeNode& operator[](long n);
    void append(EmployeeNode *employee);
    void remove(long id);
    void modify(long id, EmployeeNode *newEmployee);
    bool exists(long id);
    void swap(EmployeeNode *a, EmployeeNode *b);
    EmployeeNode get(long id);
    size_t size();
    void sortByID();
    void sortBySalary();
    void save();
};