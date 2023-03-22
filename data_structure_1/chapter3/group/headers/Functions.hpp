#ifndef FUNCTIONS
#define FUNCTIONS

#include "SeqList.h"
#include <iostream>
#include <cmath>

using namespace std;

class Functions
{
  private:
    SeqList<double> ce; // 系数
    SeqList<int> id;    // 指数
    int nums;           // 项数
  public:
    Functions() : nums(0){};

    Functions(SeqList<int> id, SeqList<double> ce)
    {
        this->id = id; // 指数
        this->ce = ce; // 系数
        this->nums = id.GetLength();
    }

    Functions(SeqList<int> id, SeqList<double> ce, int num)
    {
        this->id = id; // 指数
        this->ce = ce; // 系数
        this->nums = num;
    }

    ~Functions(){};

    friend istream &operator>>(istream &in, Functions &f)
    {
        cout << "请输入多项式的项数" << endl;
        int num = 0;
        in >> num;
        cout << "请输入多项式的系数（从大到小）" << endl;
        int arr[100];
        double b[100];
        for (int i = 0; i <= num - 1; i++)
        {
            in >> b[i];
        }
        cout << "请输入多项式的次数（从大到小）" << endl;
        for (int i = 0; i <= num - 1; i++)
        {
            in >> arr[i];
        }
        f.ce = SeqList<double>(b, num);
        f.id = SeqList<int>(arr, num);
        f.nums = num;
        return in;
    }

    friend ostream &operator<<(ostream &out, Functions &f)
    {
        for (int i = 0; i < f.nums; i++)
        {
            out << f.ce.GetElems()[i] << "x^" << f.id.GetElems()[i];
            if (i != f.nums - 1)
                out << " + ";
        }
        out << endl;
        return out;
    }

    void Derivation()
    {
        cout << "P'(x) = ";
        for (int i = 0; i < this->nums; i++)
        {
            if (this->id.GetElems()[i] == 0)
            {
                cout << 0;

                if (i != this->nums - 1)
                    cout << " + ";
                continue;
            }
            cout << (this->ce.GetElems()[i]) * (this->id.GetElems()[i]) << "x^"
                 << (this->id.GetElems()[i]) - 1;
            if (i != this->nums - 1)
                cout << " + ";
        }
        cout << endl;
    }

    void Evaluation()
    {
        cout << "输入x的值:";
        double x;
        cin >> x;
        double temp = 0;
        cout << "P(x) = ";
        for (int i = 0; i < this->nums; i++)
        {
            temp += (this->ce.GetElems()[i]) * pow(x, (this->id.GetElems()[i]));
        }
        cout << temp << endl;
        cout << endl;
    }

    friend void Subtraction(Functions &f1, Functions &f2)
    {
        int i = 0, j = 0;
        cout << "P(x)-Q(x) = ";
        while (i < f1.nums && j < f2.nums)
        {
            if (f1.id.GetElems()[i] == f2.id.GetElems()[j])
            {
                cout << "(";
                cout << f1.ce.GetElems()[i] - f2.ce.GetElems()[j];
                cout << "x^";
                cout << f1.id.GetElems()[i];
                cout << ")";

                i++;
                j++;

                if (i < f1.nums || j < f2.nums)
                    cout << " + ";
            }

            else if (f1.id.GetElems()[i] > f2.id.GetElems()[j])
            {
                cout << "(";
                cout << f1.ce.GetElems()[i];
                cout << "x^";
                cout << f1.id.GetElems()[i];
                cout << ")";

                i++;
                if (i < f1.nums || j < f2.nums)
                    cout << " + ";
            }

            else if (f1.id.GetElems()[i] < f2.id.GetElems()[j])
            {
                cout << "(";
                cout << -f2.ce.GetElems()[j];
                cout << "x^";
                cout << f2.id.GetElems()[j];
                cout << ")";

                j++;

                if (i < f1.nums || j < f2.nums)
                    cout << " + ";
            }
        }
        while (i < f1.nums)
        {
            cout << "(";
            cout << f1.ce.GetElems()[i];
            cout << "x^";
            cout << f1.id.GetElems()[i];
            cout << ")";

            i++;

            if (i < f1.nums)
                cout << " + ";
        }

        while (j < f2.nums)
        {
            cout << "(";
            cout << -f2.ce.GetElems()[j];
            cout << "x^";
            cout << f2.id.GetElems()[j];
            cout << ")";

            j++;

            if (j < f2.nums)
                cout << " + ";
        }
    }
};

#endif
