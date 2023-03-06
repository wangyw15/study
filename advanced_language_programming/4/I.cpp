#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    int index = 1;

    string line;
    long double num, sum = 0;
    int row = 0, col = 0;
    while (getline(cin, line))
    {
        if (line.length() == 0)
        {
            cout << "Case " << index++ << ": " << row << ", " << col << ", " << sum << endl;
            sum = row = col = 0;
            continue;
        }
        stringstream ss(line);
        while (ss >> num)
        {
            sum += num;
            if (row == 1)
            {
                col++;
            }
        }
        row++;
    }
    cout << "Case " << index++ << ": " << row << ", " << col << ", " << sum << endl;
    return 0;
}