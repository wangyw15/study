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

long sumPrimeFactor(long num)
{
    long sum = 0;
    for (long i = 1; i <= (long)sqrt(num) + 1; i++)
    {
        if(num % i == 0)
        {
            sum += i;
            if(i != sqrt(num) && i != 1)
            {
                sum += num / i;
            }
        }
    }
    return sum;
}

void eachLineProcess(string line)
{
    const char *cstr = line.c_str();
    long a, b;
    string tmp = "";
    for(long i = 0; i < line.length(); i++)
    {
        if(cstr[i] == ' ')
        {
            a = atoi(tmp.c_str());
            tmp = "";
        }
        else
        {
            tmp += cstr[i];
        }
    }
    b = atoi(tmp.c_str());

    long num = atoi(line.c_str());
    bool result = (a == sumPrimeFactor(b)) && (b == sumPrimeFactor(a));
    cout << a << ", " << b << ", " << (result ? "Yes" : "No");
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