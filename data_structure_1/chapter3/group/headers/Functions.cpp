#include "Functions.h"
#include <cmath>

Functions::Functions(SeqList<int> iid, SeqList<double> ice)
{
    this->id = iid; // ָ��
    this->ce = ice; // ϵ��
    this->nums = iid.GetLength();
}

Functions::Functions(SeqList<int> iid, SeqList<double> ice, int num)
{
    this->id = iid; // ָ��
    this->ce = ice; // ϵ��
    this->nums = num;
}

istream &operator>>(istream &in, Functions &f)
{
    cout << "���������ʽ������" << endl;
    int num = 0;
    in >> num;
    cout << "���������ʽ��ϵ�����Ӵ�С��" << endl;
    int arr[100];
    double b[100];
    for (int i = 0; i <= num - 1; i++)
    {
        in >> b[i];
    }
    cout << "���������ʽ�Ĵ������Ӵ�С��" << endl;
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
        out << f.ce.GetElems()[i] << "x^" << f.id.GetElems()[i];
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

void Functions::Evaluation()
{
    cout << "����x��ֵ:";
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

void Subtraction(Functions &f1, Functions &f2)
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
