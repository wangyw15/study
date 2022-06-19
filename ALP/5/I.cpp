#include <iostream>
#include <string>
#include <vector>

using namespace std;

char toLower(char c)
{
    if ('a' <= c && c <= 'z')
        return c;
    return c - 'A' + 'a';
}

bool isExcluded(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        word[i] = tolower(word[i]);
    }
    string excludeList[] = {"the", "a", "an", "of", "for", "and"};
    for (int i = 0; i < 6; i++)
    {
        if (word == excludeList[i])
            return true;
    }
    return false;
}

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
            if (line[i] != ' ' && line[i] != '-')
            {
                current += line[i];
                if (i + 1 < line.length() && (line[i + 1] != ' ' && line[i + 1] != '-'))
                    continue;
                words.push_back(current);
                current = "";
            }
        }
        cout << "Case " << index++ << ": ";

        for (int i = 0; i < words.size(); i++)
        {
            string current = words[i];
            if (!isExcluded(current))
            {
                cout << current[0];
            }
        }
        cout << endl;
    }
    return 0;
}