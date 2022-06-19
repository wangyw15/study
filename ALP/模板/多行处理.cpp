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
    // TODO
}

int main()
{
    // get all lines
    DataListNode *head = new DataListNode();
    head->next = NULL;

    DataListNode *tail = head;
    while (true)
    {
        string currentLine;
        getline(cin, currentLine);
        if(currentLine != "")
        {
            DataListNode *newNode = new DataListNode();
            newNode->next = NULL;
            tail->val = currentLine;
            tail->next = newNode;
            tail = newNode;
        }
        else
        {
            break;
        }
    }

    // real output
    DataListNode *current = head;
    int len = 0;
    while(current->next != NULL)
    {
        cout << "Case " << ++len << ": ";
        eachLineProcess(current->val);
        cout << endl;
        current = current->next;
    }
    return 0;
}