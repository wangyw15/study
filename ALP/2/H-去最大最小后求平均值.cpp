#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

struct DoubleListNode
{
    double val;
    DoubleListNode *next;
};

int main()
{
    double a;

    DoubleListNode *head = new DoubleListNode();
    head->next = NULL;

    long length = 0;
    DoubleListNode *latest = head;

    while (cin >> a)
    {
        DoubleListNode *newNode = new DoubleListNode();
        newNode->next = NULL;
        latest->val = a;
        latest->next = newNode;
        latest = newNode;
        length++;
        if (cin.get() == '\n')
            break;
    }

    DoubleListNode *current = head;
    double* num = new double[length];
    int index = 0;
    while (current->next != NULL)
    {
        num[index] = current->val;
        current = current->next;
        index++;
    }
    
    // TODO
    double tmp;
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
            if (num[j] > num[j + 1])
            {
                tmp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = tmp;
            }
        }
    }

    double sum = 0;

    for(int i = 1; i < length - 1;i++)
    {
        sum += num[i];
    }
    
    cout << length << ", " << num[0] << ", " << num[length - 1] << ", " << sum / (length - 2);

    return 0;
}