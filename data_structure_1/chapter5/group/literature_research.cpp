#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ios>

using namespace std;

inline bool is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// detect if the line contains the word
bool contains_word(string line, string word)
{
    int i = 0, pos = 0;
    string current_word = "";
    
    // convert the word to lower case
    for (auto c = word.begin(); c != word.end(); c++)
    {
        *c = tolower(*c);
    }
    
    for (auto c = line.begin(); c != line.end(); c++)
    {
        if (is_letter(*c))
        {
            current_word += tolower(*c);
        }
        else
        {
            if (current_word == word)
            {
                return true;
            }
            current_word = "";
        }
    }

    // the word at the end of the line
    if (current_word == word)
    {
        return true;
    }
    return false;
}

int main() {
    vector<string> passage, words;
    string buffer;
    ifstream in;
    
    // read passage
    in.open("passage.txt");
    while (getline(in, buffer))
    {
        passage.push_back(buffer);
    }
    in.close();
    
    // read words
    in.open("words.txt");
    while (in >> buffer)
    {
        words.push_back(buffer);
    }
    in.close();

    // initialize result
    vector<vector<int>> result;
    for (size_t i = 0; i < words.size(); i++)
    {
        result.push_back(vector<int>());
    }

    // count words
    size_t line_num = 0;
    string current_word = "";
    for (auto line = passage.begin(); line != passage.end(); line++)
    {
        line_num++;
        for (auto c = (*line).begin(); c != (*line).end(); c++)
        {
            if (is_letter(*c))
            {
                current_word += tolower(*c);
            }
            else
            {
                for (size_t i = 0; i < words.size(); i++)
                {
                    string word = words[i];
                    if (current_word == word)
                    {
                        result[i].push_back(line_num);
                    }
                }
                current_word = "";
            }
        }

        // the word at the end of the line
        for (size_t i = 0; i < words.size(); i++)
        {
            string word = words[i];
            if (current_word == word)
            {
                result[i].push_back(line_num);
            }
        }
    }

    // print result
    for (size_t i = 0; i < words.size(); i++)
    {
        cout << "Word \"" << words[i] << "\" appeared " << result[i].size()
             << " times, " << "line numbers: " << endl;
        for (auto j = result[i].begin(); j != result[i].end(); j++)
        {
            cout << *j << ", ";
        }
        cout << endl << endl;
    }

    /*for (auto word = words.begin(); word != words.end(); word++)
    {
        vector<int> current_result;
        size_t line_num = 0;
        for (auto line = passage.begin(); line != passage.end(); line++)
        {
            line_num++;
            if (contains_word(*line, *word))
            {
                cout << line_num << ", ";
            }
        }
        cout << endl << endl;
    }*/

    return 0;
}