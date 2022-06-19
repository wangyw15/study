#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
    int index = 1;
    string str;
    while (getline(cin, str))
    {
        cout << "Case " << index++ << ": \"";
        for (int i = str.length() - 1; i >= 0; i--)
        {
            if (0 <= str[i] && str[i] <= 127)
            {
                cout << str[i];
            }
            else
            {
                cout << str[i - 1] << str[i];
                i--;
            }
        }
        cout << "\"" << endl;
    }
    return 0;
}

int otherSolution()
{
    int index = 1;
    string str;
    while (getline(cin, str))
    {
        reverse(str.begin(), str.end());
        for(int i = 0; i < str.length(); i++)
        {
            if(str[i] < 0)
            {
                swap(str[i], str[i + 1]);
                i++;
            }
        }
        cout << "\"" << endl;
    }
    return 0;
}