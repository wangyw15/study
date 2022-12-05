#include <iostream>
#include "headers/SeqList.h"

using namespace std;

int main()
{
    SeqList<double>* list;
    int option = 1;

    // construction
    cout << "请选择构造方式：1.空顺序表 2.给定数据构造数据表: ";
    cin >> option;
    if (option == 1)
    {
        list = new SeqList<double>;
    }
    else if (option == 2)
    {
        cout << "请输入数据个数: ";
        cin >> option;
        cout << "请输入数据: ";
        double tempArray[1000];
        for (auto i = 0; i < option; i++)
        {
            cin >> tempArray[i];
        }
        list = new SeqList<double>(tempArray, option);
    }

    // (1)
    cout << "最大值所在下标: " << list->Max() << endl << "最小值所在下标: " << list->Min() << endl << endl;

    // (2)
    cout << "请输入要插入的数据: ";
    double item = 0;
    cin >> item;
    list->InsertByOrder(item);
    cout << "当前顺序表的数据: " << endl;
    cout << *list << endl << endl;

    // (3)
    cout << "删除某一区间的数据，请输入要删除的最小值和最大值: ";
    double biggest, smallest;
    cin >> smallest >> biggest;
    list->DeleteRange(smallest, biggest);
    cout << "当前顺序表的数据: " << endl;
    cout << *list << endl << endl;

    // (4)
    cout << "构造需要合并的列表" << endl;
    cout << "请输入数据个数: ";
    cin >> option;
    cout << "请输入数据: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    auto merge = new SeqList<double>(tempArray, option);
    list->MergeByOrder(*merge);
    cout << "当前顺序表的数据: " << endl;
    cout << *list << endl << endl;

    return 0;
}

/*
void ShowMenu()
{
    cout << "菜单：" << endl
        << " 1. 构造空顺序表" << endl
        << " 2. 根据数组内容构造顺序表" << endl
        << " 3. 删除顺序表" << endl
        << " 4. 获取顺序表长度" << endl
        << " 5. 判断顺序表是否为空" << endl
        << " 6. 清空顺序表" << endl
        << " 7. 访问顺序表各个元素" << endl
        << " 8. 定位元素" << endl
        << " 9. 取顺序表中第i个元素" << endl
        << "10. 修改顺序表中第i个元素的值" << endl
        << "11. 删除顺序表中第i个元素" << endl
        << "12. 在顺序表第i个位置插入元素" << endl
        << "13. 在顺序表表尾插入元素" << endl
        << "14. 查找最大值的位置" << endl
        << "15. 查找最小值的位置" << endl
        << "16. 排序并插入新元素" << endl
        << "17. 删除指定大小范围内的元素" << endl
        << "18. 按顺序合并两个顺序表" << endl
        << " 0. 退出" << endl
        << "选项: ";
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
            cout << "选择了构造空顺序表，构造完成的顺序表序号为: " << listsSize++ << endl;
        }
        else if (option == 2)
        {
            cout << "选择了根据数组内容构造顺序表，请输入数组大小: ";
            cin >> option;
            cout << "请输入元素：" << endl;
            for (int i = 0; i < option; i++)
            {
                cin >> tempArray[i];
            }
            lists[listsSize] = new SeqList<double>(tempArray, option);
            cout << "构造完成，顺序表序号为: " << listsSize++ << endl;
        }
        else if (option == 3)
        {
            cout << "选择了删除顺序表，请输入想要删除的顺序表序号: ";
            cin >> option;
            if (option < listsSize)
            {
                lists[option]->~SeqList();
                cout << "删除成功" << endl;
            }
            else
            {
                cout << "所选顺序表不存在" << endl;
            }
        }
        else if (option == 4)
        {
            cout << "选择了获取顺序表长度，请输入顺序表序号: ";
            cin >> option;
            if (option < listsSize)
            {
                cout << "长度为: " << lists[option]->Length() << endl;
            }
            else
            {
                cout << "所选顺序表不存在" << endl;
            }
        }
        else if (option == 5)
        {
            cout << "选择了判断顺序表是否为空，请输入顺序表序号: ";
            cin >> option;
            if (option < listsSize)
            {
                cout << "当前顺序表" << (lists[option]->IsEmpty() ? "为" : "非") << "空" << endl;
            }
            else
            {
                cout << "所选顺序表不存在" << endl;
            }
        }
        else if (option == 6)
        {
            cout << "选择了清空顺序表，请输入顺序表序号: ";
            cin >> option;
            if (option < listsSize)
            {
                lists[option]->Clear();
                cout << "已清空" << endl;
            }
            else
            {
                cout << "所选顺序表不存在" << endl;
            }
        }
        else if (option == 7)
        {
            cout << "选择了打印顺序表，请输入顺序表序号: ";
            cin >> option;
            if (option < listsSize)
            {
                cout << *lists[option] << endl;
            }
            else
            {
                cout << "所选顺序表不存在" << endl;
            }
        }
    }
    return 0;
}
*/
