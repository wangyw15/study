#include <iostream>
#include <string>
#include "SingleLinkList.h"

using namespace std;

struct Student
{
    long ID;
    string Name;
    string Sex;
    string Class;
    long Phone;

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

ostream& StudentPrinter(ostream& out, SingleLinkListWithoutHead<Student>& list)
{
    out << "学号 姓名 性别 班级 电话" << endl;
    Node<Student>* pointer = list.Head();
    if (list.Length() == 1)
    {
        out << pointer->data;
    }
    else
    {
        for (auto i = 0; i < list.Length(); i++)
        {
            out << pointer->data << endl;
            pointer = pointer->next;
        }
    }
    return out;
}

int main()
{
    int arr1[6] = { 1, 5, 7, 6, 2, 3 };
    int arr2[3] = { 0, 4, 8 };
    SingleLinkListWithoutHead<int> list1(arr1, 6);
    list1.Insert(3, 10);
    list1.Insert(6, 11);
    cout << list1 << endl;
    SingleLinkListWithoutHead<int> list2(list1);
    list1.Clear();
    list2.Reverse();
    cout << list2 << endl;
    return 0;

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
    SingleLinkListWithoutHead<Student> studentList(studentTempArray, option);
    studentList.SetPrintMethod(StudentPrinter);
    cout << studentList << endl << endl;

    // construct
    cout << "请输入数据个数: ";
    cin >> option;
    cout << "请输入数据: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    SingleLinkListWithoutHead<double> list(tempArray, option);
    cout << endl << endl;

    // (2)
    cout << "请输入要插入的数据: ";
    double item = 0;
    cin >> item;
    list.InsertByOrder(item);
    cout << "当前单链表的数据: " << endl;
    cout << list << endl << endl;

    // (3)
    cout << "原数据：" << list << endl;
    list.Reverse();
    cout << "reversal后：" << list << endl << endl;

    // (4)
    cout << "构造需要合并的列表" << endl;
    cout << "请输入数据个数: ";
    cin >> option;
    cout << "请输入数据: ";
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    SingleLinkListWithoutHead<double> merge(tempArray, option);
    list.MergeByOrder(merge);
    cout << "当前顺序表的数据: " << endl;
    cout << list << endl << endl;

    return 0;
}