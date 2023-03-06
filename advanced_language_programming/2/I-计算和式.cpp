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

void printEquation(string line)
{
    // divide string into two numbers
    const char *cstr = line.c_str();
    long num, count;
    string tmp = "";
    for(long i = 0; i < line.length(); i++)
    {
        if(cstr[i] == ' ')
        {
            num = atoi(tmp.c_str());
            tmp = "";
        }
        else
        {
            tmp += cstr[i];
        }
    }
    count = atoi(tmp.c_str());

    long sum = 0;
    
    for(int i = 0; i < count - 1; i++)
    {
        long current = 0;
        for(int j = 0; j <= i; j++)
        {
            current += num * pow(10, j);
        }
        sum += current;
        cout << current << " + ";
    }

    long latest = 0;
    for(int i = 0; i < count; i++)
    {
        latest += num * pow(10, i);
    }
    sum += latest;
    cout << latest << " = " << sum;
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
        if(currentLine != "")
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
    while(current->next != NULL)
    {
        len++;
        cout << "Case " << len << ": ";
        printEquation(current->val);
        cout << endl;
        current = current->next;
    }
    return 0;
}