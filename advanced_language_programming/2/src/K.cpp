#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

struct IntListNode
{
    double data;
    IntListNode *next;
};

long f(long n)
{
    if (n % 2 == 0)
        return n / 2;
    return n * 3 + 1;
}

int main()
{
    double a;
    cin >> a;

    IntListNode *head = new IntListNode();
    head->data = a;
    head->next = NULL;

    long length = 1;
    IntListNode *latest = head;

    while (cin >> a)
    {
        IntListNode *current = new IntListNode();
        current->data = a;
        current->next = NULL;
        latest->next = current;
        latest = current;
        length++;
        if (cin.get() == '\n')
            break;
    }

    IntListNode *current = head;
    double *num = new double[length];
    int index = 0;
    while (current->next != NULL)
    {
        num[index] = current->data;
        index++;
        current = current->next;
    }
    num[index] = current->data;

    for (int i = 0; i < length; i++)
    {
        long current = num[i];
        cout << "Case " << i + 1 << ": " << current << ", ";
        if (num[i] > 0)
        {
            int count = 0;
            while (current != 1)
            {
                current = f(current);
                count++;
            }
            cout << count << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }

    return 0;
}