#include <iostream>
#include <string>

using namespace std;

int main()
{
    string line;
    while(getline(cin, line))
    {
        int count = 0;
        for(int i = 0; i < line.length(); i++)
        {
            if('0' <= line[i] && line[i] <= '9')
                count++;
        }
        cout << count << endl;
    }
    return 0;
}