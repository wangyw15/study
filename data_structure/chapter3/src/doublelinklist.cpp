#include <iostream>
#include <string>
#include "headers/DoubleLinkList.h"

using namespace std;

struct Student
{
    int ID;
    string Name;
    string Sex;
    string Class;
    int Phone;

    bool operator<(const Student& other)
    {
        return ID < other.ID;
    }

    bool operator>(const Student& other)
    {
        return ID > other.ID;
    }

    bool operator==(const Student& other)
    {
        return ID == other.ID;
    }

    friend ostream& operator<<(ostream& out, Student& stu)
    {
        out << stu.ID << " " << stu.Name << " " << stu.Sex << " " << stu.Class << " " << stu.Phone;
        return out;
    }

    friend istream& operator>>(istream& in, Student& stu)
    {
        in >> stu.ID >> stu.Name >> stu.Sex >> stu.Class >> stu.Phone;
        return in;
    }
};

int main()
{
    /*int arr1[6] = {1, 5, 7, 6, 2, 3};
    DoubleLinkList<int> list1(arr1, 6);
    cout << list1 << endl;
    list1.Sort();
    cout << list1 << endl;
    return 0;*/

    DoubleLinkList<Student>* studentList;
    int option = 1;

    // (1) student
    cout << "请输入数据个数: ";
    cin >> option;
    cout << "请输入数据(学号 姓名 性别 班级 电话): ";
    Student studentTempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> studentTempArray[i];
    }
    studentList = new DoubleLinkList<Student>(studentTempArray, option);
    cout << *studentList << endl << endl;

    // construct
    DoubleLinkList<double>* list;
    cout << "请输入数据个数: ";
    cin >> option;
    cout << "请输入数据: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    list = new DoubleLinkList<double>(tempArray, option);
    cout << *list << endl << endl;

    // (3)
    cout << "swap()函数测试" << endl;
    cout << "交换前: " << *list << endl;
    list->Swap();
    cout << "交换后: " << *list << endl << endl;

    // (2)
    cout << "请输入要插入的数据: ";
    double item = 0;
    cin >> item;
    list->InsertByOrder(item);
    cout << "当前单链表的数据: " << endl;
    cout << *list << endl << endl;

    return 0;
}