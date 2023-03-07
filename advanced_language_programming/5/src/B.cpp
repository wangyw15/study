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
            string line;
            getline(cin, line);
            reverse(line.begin(), line.end());
            cout << "Case " << index++ << ": " << line << endl;
        }
    }
    return 0;
}