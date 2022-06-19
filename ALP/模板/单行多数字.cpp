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

    return 0;
}