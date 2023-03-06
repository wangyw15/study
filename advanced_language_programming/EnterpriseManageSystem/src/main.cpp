#ifndef COMMON
#include "Common.h"
#endif

using namespace std;

EmployeeList employees;
EmployeeEventList events;

void printAllEmployees(bool sort = false)
{
    if (sort)
    {
        employees.sortByID();
    }
    cout << left << setw(8) << "编号" << left << setw(16) << "姓名" << left << setw(16) << "所属部门" << left << setw(16) << "薪水" << left << setw(16) << "直属领导" << endl;
    for (auto i = employees.begin(); i != employees.end(); i = i->next)
    {
        cout << left << setw(8) << i->ID << left << setw(16) << i->Name << left << setw(16) << i->Department << left << setw(16) << i->Salary << left << setw(16) << i->DirectLeadership << endl;
    }
}

void printAllEvents()
{
    cout << left << setw(8) << "员工编号" << setw(16) << "事件" << endl;
    for (auto i = events.begin(); i != events.end(); i = i->next)
    {
        cout << left << setw(8) << i->ID << setw(16) << i->Event << endl;
    }
}

void employee_logic()
{
    cout << SPLIT_LINE << "\n1. 查看所有人\n2. 找某个人\n3. 添加员工\n4. 删除员工\n5. 修改员工信息\n6. 看看薪水排名\n7. 查看领导层级" << endl;
    string choice = getSingleInput("选择功能：");
    if (choice == "1")
    {
        cout << SPLIT_LINE << endl;
        printAllEmployees(true);
    }
    else if (choice == "2")
    {
        cout << SPLIT_LINE << endl;
        auto id = parseLong(getSingleInput("请输入员工编号："));
        if (employees.exists(id))
        {
            auto employee = employees.get(id);
            cout << left << setw(8) << "编号" << left << setw(16) << "姓名" << left << setw(16) << "所属部门" << left << setw(16) << "薪水" << left << setw(16) << "直属领导编号" << endl;
            cout << left << setw(8) << employee.ID << left << setw(16) << employee.Name << left << setw(16) << employee.Department << left << setw(16) << employee.Salary << left << setw(16) << employee.DirectLeadership << endl;
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == "3")
    {
        cout << SPLIT_LINE << endl;
        cout << "请输入员工编号、姓名、所属部门、薪水及直属领导编号（如没有则输入0），以空格分隔" << endl;
        auto employee = employees.newNode();
        cin >> employee->ID >> employee->Name >> employee->Department >> employee->Salary >> employee->DirectLeadership;
        if (!employees.exists(employee->ID))
        {
            employees.append(employee);
            employees.save();
        }
        else
        {
            delete employee;
            cout << "编号已存在" << endl;
        }
    }
    else if (choice == "4")
    {
        cout << SPLIT_LINE << endl;
        printAllEmployees(true);
        auto id = parseLong(getSingleInput("请输入要删除的员工编号："));
        if (employees.exists(id))
        {
            employees.remove(id);
            employees.save();
            events.removeByID(id);
            events.save();
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == "5")
    {
        cout << SPLIT_LINE << endl;
        printAllEmployees(true);
        auto id = parseLong(getSingleInput("请输入要修改的员工编号："));
        if (employees.exists(id))
        {
            cout << "请输入修改后的姓名、所属部门、薪水及直属领导编号（如没有则输入0），以空格分隔" << endl;
            auto employee = employees.newNode();
            employee->ID = id;
            cin >> employee->Name >> employee->Department >> employee->Salary >> employee->DirectLeadership;
            employees.modify(id, employee);
            employees.save();
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == "6")
    {
        employees.sortBySalary();
        cout << setw(16) << left << "姓名" << setw(12) << left << "薪水" << endl;
        for (auto i = employees.begin(); i != employees.end(); i = i->next)
        {
            cout << setw(16) << left << i->Name << setw(12) << left << i->Salary << endl;
        }
    }
    else if (choice == "7")
    {
        cout << SPLIT_LINE << endl;
        printAllEmployees(true);
        auto id = parseLong(getSingleInput("请输入要查看的员工编号："));
        if (employees.exists(id))
        {
            cout << "领导层级：";
            while (employees.exists(id))
            {
                auto leader = employees.get(id);
                cout << leader.Name << (employees.exists(id = leader.DirectLeadership) ? " < " : "");
            }
            cout << endl;
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == "test")
    {
        cout << "这不是你该来的地方！！！" << endl;
    }
}

void event_logic()
{
    cout << SPLIT_LINE << "\n1. 查看所有事务\n2. 找某个人的事务\n3. 添加事务\n4. 删除事务\n5. 修改事务" << endl;
    string choice = getSingleInput("选择功能：");
    if (choice == "1")
    {
        cout << SPLIT_LINE << endl;
        printAllEvents();
    }
    else if (choice == "2")
    {
        cout << SPLIT_LINE << endl;
        choice = getSingleInput("请输入员工编号：");
        long targetID = parseLong(choice);
        if (employees.exists(targetID))
        {
            bool found = false;
            for (auto i = events.begin(); i != events.end(); i = i->next)
            {
                if (i->ID == targetID)
                {
                    if (!found)
                    {
                        found = true;
                        cout << left << setw(8) << "员工编号" << setw(16) << "事件" << endl;
                    }
                    cout << left << setw(8) << i->ID << setw(16) << i->Event << endl;
                }
            }
            if (!found)
            {
                cout << "===========这人没事===========" << endl;
            }
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == "3")
    {
        cout << SPLIT_LINE << endl;
        cout << "请输入员工编号和事务，以空格分隔" << endl;
        auto event = events.newNode();
        cin >> event->ID >> event->Event;
        events.append(event);
        events.save();
    }
    else if (choice == "4")
    {
        cout << SPLIT_LINE << endl;
        cout << left << setw(16) << "事件序号" << left << setw(16) << "员工编号" << left << setw(10) << "事务" << endl;
        long index = 0;
        for (auto i = events.begin(); i != events.end(); i = i->next)
        {
            cout << left << setw(16) << ++index << left << setw(16) << i->ID << setw(10) << i->Event << endl;
        }
        events.remove(parseLong(getSingleInput("请输入要删除的事件序号：")) - 1);
        events.save();
    }
    else if (choice == "5")
    {
        cout << SPLIT_LINE << endl;
        cout << left << setw(16) << "事件序号" << left << setw(16) << "员工编号" << left << setw(10) << "事务" << endl;
        long index = 0;
        for (auto i = events.begin(); i != events.end(); i = i->next)
        {
            cout << left << setw(16) << ++index << left << setw(16) << i->ID << setw(10) << i->Event << endl;
        }
        auto position = parseLong(getSingleInput("请输入要修改的事件序号："));
        auto event = events.newNode();
        cout << "请输入员工编号和事务，以空格分隔" << endl;
        cin >> event->ID >> event->Event;
        events.modify(position - 1, event);
        events.save();
    }
}

int main()
{
    while (true)
    {
        cout << "=====欢迎使用企业管理系统=====\n1. 员工信息\n2. 事务信息\nq. 退出\n";
        string choice = getSingleInput("选择功能：");
        if (choice == "1")
        {
            employee_logic();
        }
        else if (choice == "2")
        {
            event_logic();
        }
        else if (choice == "q")
        {
            employees.save();
            events.save();
            break;
        }
    }
}