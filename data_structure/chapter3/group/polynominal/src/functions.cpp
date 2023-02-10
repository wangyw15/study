#include "headers/Functions.h"
#include <cmath>

Functions::Functions(SeqList<int> iid, SeqList<double> ice)
{
    this->id = iid; // 指数
    this->ce = ice; // 系数
    this->nums = iid.Length();
}

Functions::Functions(SeqList<int> iid, SeqList<double> ice, int num)
{
    this->id = iid; // 指数
    this->ce = ice; // 系数
    this->nums = num;
}

istream &operator>>(istream &in, Functions &f)
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

ostream &operator<<(ostream &out, Functions &f)
{
    for (int i = 0; i < f.nums; i++)
    {
        out << f.ce[i] << "x^" << f.id[i];
        if (i != f.nums - 1)
            out << " + ";
    }
    out << endl;
    return out;
}

void Functions::Derivation()
{
    cout << "P'(x) = ";
    for (int i = 0; i < this->nums; i++)
    {
        if (this->id[i] == 0)
        {
            cout << 0;

            if (i != this->nums - 1)
                cout << " + ";
            continue;
        }
        cout << (this->ce[i]) * (this->id[i]) << "x^" << (this->id[i]) - 1;
        if (i != this->nums - 1)
            cout << " + ";
    }
    cout << endl;
}

void Functions::Evaluation()
{
    cout << "输入x的值:";
    double x;
    cin >> x;
    double temp = 0;
    cout << "P(x) = ";
    for (int i = 0; i < this->nums; i++)
    {
        temp += (this->ce[i]) * pow(x, (this->id[i]));
    }
    cout << temp << endl;
    cout << endl;
}

void Subtraction(Functions &f1, Functions &f2)
{
    int i = 0, j = 0;
    cout << "P(x)-Q(x) = ";
    while (i < f1.nums && j < f2.nums)
    {
        if (f1.id[i] == f2.id[j])
        {
            cout << "(";
            cout << f1.ce[i] - f2.ce[j];
            cout << "x^";
            cout << f1.id[i];
            cout << ")";

            i++;
            j++;

            if (i < f1.nums || j < f2.nums)
                cout << " + ";
        }

        else if (f1.id[i] > f2.id[j])
        {
            cout << "(";
            cout << f1.ce[i];
            cout << "x^";
            cout << f1.id[i];
            cout << ")";

            i++;
            if (i < f1.nums || j < f2.nums)
                cout << " + ";
        }

        else if (f1.id[i] < f2.id[j])
        {
            cout << "(";
            cout << -f2.ce[j];
            cout << "x^";
            cout << f2.id[j];
            cout << ")";

            j++;

            if (i < f1.nums || j < f2.nums)
                cout << " + ";
        }
    }
    while (i < f1.nums)
    {
        cout << "(";
        cout << f1.ce[i];
        cout << "x^";
        cout << f1.id[i];
        cout << ")";

        i++;

        if (i < f1.nums)
            cout << " + ";
    }

    while (j < f2.nums)
    {
        cout << "(";
        cout << -f2.ce[j];
        cout << "x^";
        cout << f2.id[j];
        cout << ")";

        j++;

        if (j < f2.nums)
            cout << " + ";
    }
}
