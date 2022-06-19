#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string str1, str2;
    int index = 1;
    while (getline(cin, str1))
    {
        getline(cin, str2);
        string::size_type pos = str2.find(str1);
        cout << "Case " << index++ << ": ";
        if(pos == string::npos)
            cout << "-1";
        else
            cout << pos;
        cout << endl;
    }
    return 0;
}