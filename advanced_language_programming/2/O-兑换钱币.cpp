#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

struct DataListNode
{
    string val;
    DataListNode *next;
};

void eachLineProcess(string line)
{
    long num = atoi(line.c_str());
    long count = 0;
    for(long a = 0; a <= num / 5; a++)
    {
        long remain = num - a * 5;
        count += remain / 2 + 1;
    }
    cout << num << ", " << count;
}

int main()
{
    // get all lines
    DataListNode *head = new DataListNode();
    head->next = NULL;

    DataListNode *latest = head;
    while (true)
    {
        string currentLine;
        getline(cin, currentLine);
        if (currentLine != "")
        {
            DataListNode *newNode = new DataListNode();
            newNode->next = NULL;
            latest->val = currentLine;
            latest->next = newNode;
            latest = newNode;
        }
        else
        {
            break;
        }
    }

    // real output
    DataListNode *current = head;
    int len = 0;
    while (current->next != NULL)
    {
        len++;
        cout << "Case " << len << ": ";
        eachLineProcess(current->val);
        cout << endl;
        current = current->next;
    }
    return 0;
}