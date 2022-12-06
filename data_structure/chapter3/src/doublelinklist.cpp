#include <iostream>
#include <string>
#include <ios>
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

ostream& StudentPrinter(ostream& out, DoubleLinkList<Student>& list)
{
    cout << "ѧ�� ���� �Ա� �༶ �绰" << endl;
    Node<Student>* pointer = list.Head();
    while ((pointer = pointer->next) != nullptr)
    {
        out << pointer->data << endl;
    }
    return out;
}

int main()
{
    /*int arr1[6] = {1, 5, 7, 6, 2, 3};
    DoubleLinkList<int> list1(arr1, 6);
    cout << list1 << endl;
    list1.Sort();
    cout << list1 << endl;
    return 0;*/
    int option = 1;

    // (1) student
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������(ѧ�� ���� �Ա� �༶ �绰): ";
    Student studentTempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> studentTempArray[i];
    }
    DoubleLinkList<Student> studentList(studentTempArray, option);
    studentList.SetPrintMethod(StudentPrinter);
    cout << studentList << endl << endl;

    // construct
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    DoubleLinkList<double> list(tempArray, option);
    cout << list << endl;

    // (3)
    cout << "swap()��������" << endl;
    cout << "����ǰ: " << list << endl;
    list.Swap();
    cout << "������: " << list << endl << endl;

    // (2)
    cout << "������Ҫ���������: ";
    double item = 0;
    cin >> item;
    list.InsertByOrder(item);
    cout << "��ǰ˫���������: " << endl;
    cout << list << endl << endl;

    return 0;
}