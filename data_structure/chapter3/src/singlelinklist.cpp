#include <iostream>
#include <string>
#include "headers/SingleLinkList.h"

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
    int arr2[2] = { 0, 4 };
    SingleLinkList<int> list1(arr1, 6);
    SingleLinkList<int> list2(arr2, 2);
    list1.MergeByOrder(list2);
    cout << list1 << endl;
    return 0;*/

    SingleLinkList<Student>* studentList;
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
    studentList = new SingleLinkList<Student>(studentTempArray, option);
    cout << *studentList << endl << endl;

    SingleLinkList<double>* list;
    // (2)
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    list = new SingleLinkList<double>(tempArray, option);
    cout << *list << endl << endl;

    // (3)
    cout << "������Ҫ���������: ";
    double item = 0;
    cin >> item;
    list->InsertByOrder(item);
    cout << "��ǰ�����������: " << endl;
    cout << *list << endl << endl;

    // (4)
    cout << "������Ҫ�ϲ����б�" << endl;
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������: ";
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    auto merge = new SingleLinkList<double>(tempArray, option);
    list->MergeByOrder(*merge);
    cout << "��ǰ˳��������: " << endl;
    cout << *list << endl << endl;

    return 0;
}