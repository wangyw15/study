#include <iostream>
#include <string>
#include "headers/SingleLinkList.hpp"

using namespace std;

class LinkString : SingleLinkList<char>
{
public:
    LinkString(string str = "")
    {
        for (size_t i = 0; i < str.size(); i++)
        {
            Append(str[i]);
        }
    }

    void Upper()
    {
        auto pointer = _head;
        while ((pointer = pointer->next) != nullptr)
        {
            if (pointer->data >= 'a' && pointer->data <= 'z')
            {
                pointer->data = pointer->data - 'a' + 'A';
            }
        }
    }

    void Lower()
    {
        auto pointer = _head;
        while ((pointer = pointer->next) != nullptr)
        {
            if (pointer->data >= 'A' && pointer->data <= 'Z')
            {
                pointer->data = pointer->data - 'A' + 'a';
            }
        }
    }

    void StrConcat(const LinkString& str)
    {
        Concat(str);
    }

    friend std::ostream& operator<< (std::ostream& out, LinkString& list)
    {
        Node<char>*pointer = list._head;
        while ((pointer = pointer->next) != nullptr)
        {
            out << pointer->data;
        }
        return out;
    }
};

int main()
{
    LinkString s1("Hello"), s2("World");
    s1.StrConcat(s2);
    cout << s1 << endl;
    s1.Upper();
    cout << s1 << endl;
    s1.Lower();
    cout << s1 << endl;
    return 0;

    int option = 1;

    // construct
    cout << "请输入数据个数: ";
    cin >> option;
    cout << "请输入数据: ";
    double tempArray[1000];
    for (auto i = 0; i < option; i++)
    {
        cin >> tempArray[i];
    }
    SingleLinkList<double> list(tempArray, option);
    cout << endl << endl;

    // (2)
    cout << "请输入要插入的数据: ";
    double item = 0;
    cin >> item;
    list.InsertByOrder(item);
    cout << "当前串的数据: " << endl;
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
    SingleLinkList<double> merge(tempArray, option);
    list.MergeByOrder(merge);
    cout << "当前顺序表的数据: " << endl;
    cout << list << endl << endl;

    return 0;
}