#include "headers/Functions.h"
#include "headers/SeqList.h"
#include <iostream>

using namespace std;

int main()
{
    int key = 0;
    cout << "创建一元多项式P(x)" << endl;
    Functions f;
    cin >> f;
    cout << "多项式为：" << endl;
    cout << "P(x) = " << f;

    cout << "创建一元多项式Q(x)" << endl;
    Functions f2;
    cin >> f2;
    cout << "多项式为：" << endl;
    cout << "Q(x) = " << f2;

    while (1)
    {
        cout << endl;
        cout << "Menu" << endl;
        cout << "1.对P(x)求导" << endl;
        cout << "2.给定x值后求P(x)值" << endl;
        cout << "3.两个多项式相减" << endl;
        cout << "0.退出" << endl;
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