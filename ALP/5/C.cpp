#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int count, index = 1;
    while (cin >> count)
    {
        cin.ignore();
        for (int i = 0; i < count; i++)
        {
            string line, tmp;
            getline(cin, line);
            tmp = line;
            reverse(tmp.begin(), tmp.end());
            cout << "Case " << index++ << ": \"" << line << tmp.substr(line.length() % 2, tmp.length()) << "\"" << endl;
        }
    }
    return 0;
}