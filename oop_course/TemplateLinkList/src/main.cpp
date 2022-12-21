#include <iostream>
#include <iomanip>

#include "LinkList/LinkList.h"
#include "Util/Util.h"
#include "dto.h"

const auto SPLIT_LINE = "==============================";
EmployeeList employees;
EmployeeEventList events;

void employeeLogic()
{
    cout << SPLIT_LINE << "\n1. 查看所有人\n2. 找某个人\n3. 添加员工\n4. 删除员工\n5. 修改员工信息\n6. 查看领导层级" << endl;
    string choice = getSingleInput("选择功能：");
    if (choice == "1")
    {
        cout << SPLIT_LINE << endl;
        cout << "员工编号 姓名 所属部门 薪水 直属领导编号" << endl;
        std::cout << employees << std::endl;
    }
    else if (choice == "2")
    {
        cout << SPLIT_LINE << endl;
        auto id = parseInt(getSingleInput("请输入员工编号："));
        if (employees.Exist(id))
        {
            employees.GoByID(id);
            cout << employees.CurData() << endl;
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
        Employee employee;
        cin >> employee.ID >> employee.Name >> employee.Department >> employee.Salary >> employee.DirectLeadership;
        if (!employees.Exist(employee.ID))
        {
            employees.Append(employee);
            employees.Save(EMPLOYEES_FILE_NAME);
        }
        else
        {
            cout << "编号已存在" << endl;
        }
        cin.get();
    }
    else if (choice == "4")
    {
        cout << SPLIT_LINE << endl;
        cout << "员工编号 姓名 所属部门 薪水 直属领导编号" << endl;
        std::cout << employees << std::endl;
        auto id = parseInt(getSingleInput("请输入要删除的员工编号："));
        if (employees.Exist(id))
        {
            employees.GoByID(id);
            employees.DeleteCurNode();
            employees.Save(EMPLOYEES_FILE_NAME);

            for (auto i = events.NumNodes() - 1; i >= 0; i--)
            {
                events.Go(i);
                if (events.CurData().ID == id)
                {
                    events.DeleteCurNode();
                }
            }
            events.Save(EVENTS_FILE_NAME);
        }
        else
        {
            cout << "查无此人" << endl;
        }
    }
    else if (choice == "5")
    {
        cout << SPLIT_LINE << endl;
        cout << "员工编号 姓名 所属部门 薪水 直属领导编号" << endl;
        std::cout << employees << std::endl;
        auto id = parseInt(getSingleInput("请输入要修改的员工编号："));
        if (employees.Exist(id))
        {
            cout << "请输入修改后的姓名、所属部门、薪水及直属领导编号（如没有则输入0），以空格分隔" << endl;
            employees.GoByID(id);
            auto employee = employees.CurData();
            cin >> employee.Name >> employee.Department >> employee.Salary >> employee.DirectLeadership;
            employees.ModifyData(employee);
            employees.Save(EMPLOYEES_FILE_NAME);
        }
        else
        {
            cout << "查无此人" << endl;
        }
        cin.get();
    }
    else if (choice == "6")
    {
        cout << SPLIT_LINE << endl;
        cout << "员工编号 姓名 所属部门 薪水 直属领导编号" << endl;
        std::cout << employees << std::endl;
        auto id = parseInt(getSingleInput("请输入要查看的员工编号："));
        if (employees.Exist(id))
        {
            cout << "请输入修改后的姓名、所属部门、薪水及直属领导编号（如没有则输入0），以空格分隔" << endl;
            employees.GoByID(id);
            auto employee = employees.CurData();
            cin >> employee.Name >> employee.Department >> employee.Salary >> employee.DirectLeadership;
            employees.ModifyData(employee);
            employees.Save(EMPLOYEES_FILE_NAME);

            cout << "领导层级：";
            while (employees.Exist(id))
            {
                employees.GoByID(id);
                auto leader = employees.CurData();
                cout << leader.Name << (employees.Exist(id = leader.DirectLeadership) ? " < " : "");
            }
            cout << endl;
        }
        else
        {
            cout << "查无此人" << endl;
        }
        cin.get();
    }
    else if (choice == "test")
    {
        cout << "这不是你该来的地方！！！" << endl;
    }
}

void eventLogic()
{
    cout << SPLIT_LINE << "\n1. 查看所有事务\n2. 找某个人的事务\n3. 添加事务\n4. 删除事务\n5. 修改事务" << endl;
    string choice = getSingleInput("选择功能：");
    if (choice == "1")
    {
        cout << SPLIT_LINE << endl;
        std::cout << events << std::endl;
    }
    else if (choice == "2")
    {
        cout << SPLIT_LINE << endl;
        choice = getSingleInput("请输入员工编号：");
        int targetID = parseInt(choice);
        if (employees.Exist(targetID))
        {
            bool found = false;
            for (auto i = 0; i < events.NumNodes(); i++)
            {
                events.Go(i);
                auto current = events.CurData();
                if (current.ID == targetID)
                {
                    if (!found)
                    {
                        found = true;
                        cout << left << setw(8) << "员工编号" << setw(16) << "事件" << endl;
                    }
                    cout << left << setw(8) << current.ID << setw(16) << current.Event << endl;
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
        EmployeeEvent newEvent;
        cin >> newEvent.ID >> newEvent.Event;
        events.Append(newEvent);
        events.Save(EVENTS_FILE_NAME);
        cin.get();
    }
    else if (choice == "4")
    {
        cout << SPLIT_LINE << endl;
        cout << left << setw(16) << "事件序号" << left << setw(16) << "员工编号" << left << setw(10) << "事务" << endl;
        int index = 0;
        for (auto i = 0; i < events.NumNodes(); i++)
        {
            events.Go(i);
            auto currentEvent = events.CurData();
            cout << left << setw(16) << ++index << left << setw(16) << currentEvent.ID << setw(10) << currentEvent.Event << endl;
        }
        auto toBeRemove = parseInt(getSingleInput("请输入要删除的事件序号：")) - 1;
        events.Go(toBeRemove);
        events.DeleteCurNode();
        events.Save(EVENTS_FILE_NAME);
    }
    else if (choice == "5")
    {
        cout << SPLIT_LINE << endl;
        cout << left << setw(16) << "事件序号" << left << setw(16) << "员工编号" << left << setw(10) << "事务" << endl;
        int index = 0;
        for (auto i = 0; i < events.NumNodes(); i++)
        {
            events.Go(i);
            auto currentData = events.CurData();
            cout << left << setw(16) << ++index << left << setw(16) << currentData.ID << setw(10) << currentData.Event << endl;
        }
        auto position = parseInt(getSingleInput("请输入要修改的事件序号："));
        events.Go(position);
        auto event = events.CurData();
        cout << "请输入员工编号和事务，以空格分隔" << endl;
        cin >> event.ID >> event.Event;
        events.ModifyData(event);
        events.Save(EVENTS_FILE_NAME);
        cin.get();
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
            employeeLogic();
        }
        else if (choice == "2")
        {
            eventLogic();
        }
        else if (choice == "q")
        {
            employees.Save(EMPLOYEES_FILE_NAME);
            events.Save(EVENTS_FILE_NAME);
            break;
        }
    }
}