#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

bool inRange(int num, int upper)
{
    return num < upper && num >= 0;
}

vector<vector<int>> calculate(vector<vector<int>> matrix)
{
    vector<vector<int>> ret;
    for (int i = 0; i < matrix.size(); i++)
    {
        vector<int> current;
        for (int j = 0; j < matrix[i].size(); j++)
        {
            int total = 0;
            for (int a = -1; a <= 1; a++)
            {
                for (int b = -1; b <= 1; b++)
                {
                    if (inRange(i + a, matrix.size()) && inRange(j + b, matrix[i].size()))
                    {
                        total += matrix[i + a][j + b];
                    }
                }
            }
            current.push_back(total);
        }
        ret.push_back(current);
    }
    return ret;
}

void print_matrix(vector<vector<int>> matrix)
{
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j];
            if(j != matrix[i].size() - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main()
{
    int index = 1, count = 0;
    string line;
    vector<vector<int>> matrix;
    bool is_first_line = true;
    while (getline(cin, line))
    {
        if (line.length() != 0)
        {
            vector<int> current;
            stringstream ss(line);
            int tmp;
            while (ss >> tmp)
            {
                if(is_first_line)
                {
                    current.push_back(tmp);
                }
                else
                {
                    if(count < matrix[0].size())
                    {
                        current.push_back(tmp);
                        count++;
                    }
                }
            }
            is_first_line = false;
            count = 0;
            matrix.push_back(current);
            continue;
        }

        cout << "Case " << index++ << ":" << endl;
        print_matrix(calculate(matrix));
        //print_matrix(matrix);
        matrix.clear();
        is_first_line = true;
    }
    return 0;
}