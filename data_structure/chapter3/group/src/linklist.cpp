#include "headers/SingleLinkList.h"
#include <iostream>
#include <string>

using namespace std;

struct Student
{
    long ID;
    string Name;
    string Sex;
    string Class;
    long Phone;

    bool operator<(const Student &other) { return ID < other.ID; }

    bool operator>(const Student &other) { return ID > other.ID; }

    bool operator==(const Student &other) { return ID == other.ID; }

    friend ostream &operator<<(ostream &out, Student &stu)
    {
        out << stu.ID << " " << stu.Name << " " << stu.Sex << " " << stu.Class
            << " " << stu.Phone;
        return out;
    }

    friend istream &operator>>(istream &in, Student &stu)
    {
        in >> stu.ID >> stu.Name >> stu.Sex >> stu.Class >> stu.Phone;
        return in;
    }
};

ostream &StudentPrinter(ostream &out, SingleLinkListWithoutHead<Student> &list)
{
    out << "ѧ�� ���� �Ա� �༶ �绰" << endl;
    Node<Student> *pointer = list.Head();
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
    /* int arr1[6] = {1, 5, 7, 6, 2, 3};
    int arr2[3] = { 0, 4, 8 };
    SingleLinkListWithoutHead<int> list1(arr1, 6);
    list1.Insert(3, 10);
    list1.Insert(6, 11);
    cout << list1 << endl;
    SingleLinkListWithoutHead<int> list2(list1);
    list1.Clear();
    list2.Reverse();
    cout << list2 << endl;
    return 0;*/

    int option = 1;

    // construct
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    SingleLinkListWithoutHead<double> list(tempArray, option);
    cout << endl << endl;

    // (2)
    cout << "������Ҫ���������: ";
    double item = 0;
    cin >> item;
    list.InsertByOrder(item);
    cout << "��ǰ�����������: " << endl;
    cout << list << endl << endl;

    // (3)
    cout << "ԭ���ݣ�" << list << endl;
    list.Reverse();
    cout << "reversal��" << list << endl << endl;

    // (4)
    cout << "������Ҫ�ϲ����б�" << endl;
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������: ";
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    SingleLinkListWithoutHead<double> merge(tempArray, option);
    list.MergeByOrder(merge);
    cout << "��ǰ˳��������: " << endl;
    cout << list << endl << endl;

    return 0;
}