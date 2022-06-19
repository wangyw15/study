#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    int index = 0, target;
    string line;
    while (cin >> target)
    {
        if (cin.get() == '\n')
        {
            getline(cin, line);
            int location = -1, num, arrayIndex = 0;
            stringstream ss;
            ss << line;
            while (ss >> num)
            {
                if (num == target)
                    location = arrayIndex;

                arrayIndex++;
            }
            cout << "Case " << index++ << ": " << target << ", " << location << endl;
        }
    }
    return 0;
}