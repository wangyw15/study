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
        vector<string> words;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] != ' ')
            {
                current += line[i];
                if (i + 1 < line.length() && line[i + 1] != ' ')
                    continue;
                words.push_back(current);
                current = "";
            }
        }
        cout << "Case " << index++ << ": " << words.size() << endl;
    }
    return 0;
}