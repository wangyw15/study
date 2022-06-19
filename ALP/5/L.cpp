#include <iostream>
#include <string>

using namespace std;

int main()
{
    string line;
    while(getline(cin, line))
    {
        cout << (line[0] % 2 == 1 ? "YES" : "NO") << endl;
    }
    return 0;
}