#include "headers/Functions.h"
#include "headers/SeqList.h"
#include <iostream>

using namespace std;

int main()
{
    int key = 0;
    cout << "����һԪ����ʽP(x)" << endl;
    Functions f;
    cin >> f;
    cout << "����ʽΪ��" << endl;
    cout << "P(x) = " << f;

    cout << "����һԪ����ʽQ(x)" << endl;
    Functions f2;
    cin >> f2;
    cout << "����ʽΪ��" << endl;
    cout << "Q(x) = " << f2;

    while (1)
    {
        cout << endl;
        cout << "Menu" << endl;
        cout << "1.��P(x)��" << endl;
        cout << "2.����xֵ����P(x)ֵ" << endl;
        cout << "3.��������ʽ���" << endl;
        cout << "0.�˳�" << endl;
        cin >> key;
        switch (key)
        {

        case 1:
            f.Derivation();
            break;

        case 2:
            f.Evaluation();
            break;

        case 3:
            Subtraction(f, f2);
            break;
        case 0:
            return 0;
        }
    }
}