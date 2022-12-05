#include <iostream>
#include "headers/SeqList.h"

using namespace std;

int main()
{
    SeqList<double>* list;
    int option = 1;

    // construction
    cout << "��ѡ���췽ʽ��1.��˳��� 2.�������ݹ������ݱ�: ";
    cin >> option;
    if (option == 1)
    {
        list = new SeqList<double>;
    }
    else if (option == 2)
    {
        cout << "���������ݸ���: ";
        cin >> option;
        cout << "����������: ";
        double tempArray[1000];
        for (auto i = 0; i < option; i++)
        {
            cin >> tempArray[i];
        }
        list = new SeqList<double>(tempArray, option);
    }

    // (1)
    cout << "���ֵ�����±�: " << list->Max() << endl << "��Сֵ�����±�: " << list->Min() << endl << endl;

    // (2)
    cout << "������Ҫ���������: ";
    double item = 0;
    cin >> item;
    list->InsertByOrder(item);
    cout << "��ǰ˳��������: " << endl;
    cout << *list << endl << endl;

    // (3)
    cout << "ɾ��ĳһ��������ݣ�������Ҫɾ������Сֵ�����ֵ: ";
    double biggest, smallest;
    cin >> smallest >> biggest;
    list->DeleteRange(smallest, biggest);
    cout << "��ǰ˳��������: " << endl;
    cout << *list << endl << endl;

    // (4)
    cout << "������Ҫ�ϲ����б�" << endl;
    cout << "���������ݸ���: ";
    cin >> option;
    cout << "����������: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    auto merge = new SeqList<double>(tempArray, option);
    list->MergeByOrder(*merge);
    cout << "��ǰ˳��������: " << endl;
    cout << *list << endl << endl;

    return 0;
}

/*
void ShowMenu()
{
    cout << "�˵���" << endl
        << " 1. �����˳���" << endl
        << " 2. �����������ݹ���˳���" << endl
        << " 3. ɾ��˳���" << endl
        << " 4. ��ȡ˳�����" << endl
        << " 5. �ж�˳����Ƿ�Ϊ��" << endl
        << " 6. ���˳���" << endl
        << " 7. ����˳������Ԫ��" << endl
        << " 8. ��λԪ��" << endl
        << " 9. ȡ˳����е�i��Ԫ��" << endl
        << "10. �޸�˳����е�i��Ԫ�ص�ֵ" << endl
        << "11. ɾ��˳����е�i��Ԫ��" << endl
        << "12. ��˳����i��λ�ò���Ԫ��" << endl
        << "13. ��˳����β����Ԫ��" << endl
        << "14. �������ֵ��λ��" << endl
        << "15. ������Сֵ��λ��" << endl
        << "16. ���򲢲�����Ԫ��" << endl
        << "17. ɾ��ָ����С��Χ�ڵ�Ԫ��" << endl
        << "18. ��˳��ϲ�����˳���" << endl
        << " 0. �˳�" << endl
        << "ѡ��: ";
}

int oldMain()
{
    SeqList<double>* lists[100];
    double tempArray[10000];
    int option, listsSize = 0;
    while (true)
    {
        ShowMenu();
        cin >> option;

        if (option == 0)
        {
            break;
        }
        else if (option == 1)
        {
            lists[listsSize] = new SeqList<double>();
            cout << "ѡ���˹����˳���������ɵ�˳������Ϊ: " << listsSize++ << endl;
        }
        else if (option == 2)
        {
            cout << "ѡ���˸����������ݹ���˳��������������С: ";
            cin >> option;
            cout << "������Ԫ�أ�" << endl;
            for (int i = 0; i < option; i++)
            {
                cin >> tempArray[i];
            }
            lists[listsSize] = new SeqList<double>(tempArray, option);
            cout << "������ɣ�˳������Ϊ: " << listsSize++ << endl;
        }
        else if (option == 3)
        {
            cout << "ѡ����ɾ��˳�����������Ҫɾ����˳������: ";
            cin >> option;
            if (option < listsSize)
            {
                lists[option]->~SeqList();
                cout << "ɾ���ɹ�" << endl;
            }
            else
            {
                cout << "��ѡ˳�������" << endl;
            }
        }
        else if (option == 4)
        {
            cout << "ѡ���˻�ȡ˳����ȣ�������˳������: ";
            cin >> option;
            if (option < listsSize)
            {
                cout << "����Ϊ: " << lists[option]->Length() << endl;
            }
            else
            {
                cout << "��ѡ˳�������" << endl;
            }
        }
        else if (option == 5)
        {
            cout << "ѡ�����ж�˳����Ƿ�Ϊ�գ�������˳������: ";
            cin >> option;
            if (option < listsSize)
            {
                cout << "��ǰ˳���" << (lists[option]->IsEmpty() ? "Ϊ" : "��") << "��" << endl;
            }
            else
            {
                cout << "��ѡ˳�������" << endl;
            }
        }
        else if (option == 6)
        {
            cout << "ѡ�������˳���������˳������: ";
            cin >> option;
            if (option < listsSize)
            {
                lists[option]->Clear();
                cout << "�����" << endl;
            }
            else
            {
                cout << "��ѡ˳�������" << endl;
            }
        }
        else if (option == 7)
        {
            cout << "ѡ���˴�ӡ˳���������˳������: ";
            cin >> option;
            if (option < listsSize)
            {
                cout << *lists[option] << endl;
            }
            else
            {
                cout << "��ѡ˳�������" << endl;
            }
        }
    }
    return 0;
}
*/
