#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string line;
    int index = 1;
    while (getline(cin, line))
    {
        string current = "";
        vector<string> nums;
        for (int i = 0; i < line.length(); i++)
        {
            if ('0' <= line[i] && line[i] <= '9')
            {
                current += line[i];
                if (i + 1 < line.length() && line[i + 1] >= '0' && line[i + 1] <= '9')
                    continue;
                nums.push_back(current.c_str());
                current = "";
            }
        }
        cout << "Case " << index++ << ": (" << nums.size() << ")";
        for (int i = 0; i < nums.size(); i++)
        {
            cout << " " << nums[i];
        }
        cout << endl;
    }
    return 0;
}