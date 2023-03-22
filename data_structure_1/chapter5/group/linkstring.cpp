#include <iostream>
#include <string>
#include "SingleLinkList.hpp"

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
    LinkString s1("Hello World"), s2(" from c++");
    s1.StrConcat(s2);
    cout << s1 << endl;
    s1.Upper();
    cout << s1 << endl;
    s1.Lower();
    cout << s1 << endl;
    return 0;
}
