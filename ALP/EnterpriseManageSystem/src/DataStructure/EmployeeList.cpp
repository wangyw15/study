#ifndef COMMON
#include "../Common.h"
#endif

using namespace std;

EmployeeList::EmployeeList()
{
    _head = newNode();
    _tail = newNode();
    _head->next = _tail;
    _head->prev = nullptr;
    _tail->prev = _head;
    _tail->next = nullptr;
    _size = 0;
    fstream fs;
    fs.open(string(DATA_PATH) + string(EMPLOYEES_FILE_NAME), ios::in);
    string line;
    while (getline(fs, line))
    {
        stringstream ss(line);
        auto employee = newNode();
        ss >> employee->ID >> employee->Name >> employee->Department >> employee->Salary >> employee->DirectLeadership;
        append(employee);
    }
    fs.close();
    sortByID();
}

EmployeeNode* EmployeeList::newNode()
{
    return new EmployeeNode;
}

EmployeeNode* EmployeeList::begin()
{
    return _head->next;
}

EmployeeNode* EmployeeList::end()
{
    return _tail;
}

EmployeeNode& EmployeeList::operator[](long n)
{
    auto ret = begin();
    for(long i = 0; i < n; i++)
    {
        ret = ret->next;
    }
    return *ret;
}

void EmployeeList::append(EmployeeNode *employee)
{
    employee->next = end();
    employee->prev = end()->prev;
    end()->prev->next = employee;
    end()->prev = employee;
    _size++;
}

void EmployeeList::remove(long id)
{
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (i->ID == id)
        {
            i->prev->next = i->next;
            i->next->prev = i->prev;
            delete i;
            _size--;
            break;
        }
    }
}

void EmployeeList::modify(long id, EmployeeNode *newEmployee)
{
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (i->ID == id)
        {
            newEmployee->next = i->next;
            newEmployee->prev = i->prev;
            i->next->prev = newEmployee;
            i->prev->next = newEmployee;
            delete i;
            break;
        }
    }
}

bool EmployeeList::exists(long id)
{
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (i->ID == id)
        {
            return true;
        }
    }
    return false;
}

void EmployeeList::swap(EmployeeNode *a, EmployeeNode *b)
{
    auto tmp = newNode();
    tmp->ID = a->ID;
    tmp->Name = a->Name;
    tmp->Salary = a->Salary;
    tmp->Department = a->Department;
    tmp->DirectLeadership = a->DirectLeadership;

    a->ID = b->ID;
    a->Name = b->Name;
    a->Salary = b->Salary;
    a->Department = b->Department;
    a->DirectLeadership = b->DirectLeadership;

    b->ID = tmp->ID;
    b->Name = tmp->Name;
    b->Salary = tmp->Salary;
    b->Department = tmp->Department;
    b->DirectLeadership = tmp->DirectLeadership;

    delete tmp;
}

EmployeeNode EmployeeList::get(long id)
{
    for (auto i = begin(); i != end(); i = i->next)
    {
        if (i->ID == id)
        {
            return *i;
        }
    }
    EmployeeNode ret;
    ret.ID = -1;
    return ret;
}

size_t EmployeeList::size()
{
    return _size;
}

void EmployeeList::sortByID()
{
    for (long i = 0; i < size() - 1; i++)
    {
        for (long j = 0; j < size() - 1 - i; j++)
        {
            if ((*this)[j].ID > (*this)[j + 1].ID)
            {
                swap(&((*this)[j]), &((*this)[j + 1]));
            }
        }
    }
}

void EmployeeList::sortBySalary()
{
    for (long i = 0; i < size() - 1; i++)
    {
        for (long j = 0; j < size() - 1 - i; j++)
        {
            if ((*this)[j].Salary < (*this)[j + 1].Salary)
            {
                swap(&((*this)[j]), &((*this)[j + 1]));
            }
        }
    }
}

void EmployeeList::save()
{
    sortByID();
    fstream fs;
    fs.open(string(DATA_PATH) + string(EMPLOYEES_FILE_NAME), ios::out);
    for (auto i = begin(); i != end(); i = i->next)
    {
        fs << i->ID << " " << i->Name << " " << i->Department << " " << i->Salary << " " << i->DirectLeadership << endl;
    }
    fs.flush();
    fs.close();
}