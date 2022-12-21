#ifndef DTO
#define DTO

#include <string>
#include <iostream>
#include "LinkList/LinkList.h"

const auto EMPLOYEES_FILE_NAME = "employees.txt";
const auto EVENTS_FILE_NAME = "events.txt";

struct EmployeeEvent
{
	int ID;
	std::string Event;

	friend bool operator<(const EmployeeEvent& a, const EmployeeEvent& b)
	{
		return a.ID < b.ID;
	}

	friend std::ostream& operator<<(ostream& out, const EmployeeEvent& e)
	{
		out << e.ID << " " << e.Event;
		return out;
	}

	friend std::istream& operator>>(istream& in, EmployeeEvent& e)
	{
		in >> e.ID >> e.Event;
		return in;
	}
};

struct Employee
{
	int ID;
	std::string Name;
	std::string Department;
	int Salary;
	int DirectLeadership;

	friend bool operator<(const Employee& a, const Employee& b)
	{
		return a.ID < b.ID;
	}

	friend std::ostream& operator<<(ostream& out, const Employee& e)
	{
		out << e.ID << " " 
		    << e.Name << " " 
			<< e.Department << " " 
			<< e.Salary << " " 
			<< e.DirectLeadership;
		return out;
	}

	friend std::istream& operator>>(istream& in, Employee& e)
	{
		in >> e.ID 
		   >> e.Name 
		   >> e.Department 
		   >> e.Salary 
		   >> e.DirectLeadership;
		return in;
	}
};

class EmployeeList: public LinkList<Employee>
{
public:
	EmployeeList()
	{
		Load(EMPLOYEES_FILE_NAME);
		// std::cout << NumNodes() << std::endl;
	}

	bool Exist(int id)
	{
		for (auto i = 0; i < NumNodes(); i++)
		{
			Go(i);
			if (CurData().ID == id)
			{
				return true;
			}
		}
		return false;
	}

	int GetIndexByID(int id)
	{
		for (auto i = 0; i < NumNodes(); i++)
		{
			Go(i);
			if (CurData().ID == id)
			{
				return i;
			}
		}
		return -1;
	}

	void GoByID(int id)
	{
		Go(GetIndexByID(id));
	}
};


class EmployeeEventList : public LinkList<EmployeeEvent>
{
public:
	EmployeeEventList()
	{
		Load(EVENTS_FILE_NAME);
	}
};
#endif