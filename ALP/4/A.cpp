#include <iostream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

double *mySort(vector<double> nums)
{
    double *ret = (double *)(malloc(sizeof(double) * nums.size()));
    memcpy(ret, &(nums[0]), nums.size() * sizeof(double));
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < nums.size() - i; j++)
        {
            if (ret[j] < ret[j + 1])
            {
                double tmp = ret[j + 1];
                ret[j + 1] = ret[j];
                ret[j] = tmp;
            }
        }
    }
    return ret;
}

int main()
{
    double a;
    string currentLine;
    int index = 1;
    while (getline(cin, currentLine))
    {
        istringstream iss(currentLine);
        vector<double> nums;
        while (iss >> a)
        {
            nums.push_back(a);
        }
        double *sorted = mySort(nums);
        cout << "Case " << index++ << ":" << endl;

        for(int i = 0; i < nums.size(); i++)
        {
            double current = nums[i];
            for(int j = 0; j < nums.size(); j++)
            {
                if(current == sorted[j])
                {
                    cout << j + 1;
                    break;
                }
            }
            if(i != nums.size() - 1)
            {
                cout << ", ";
            }
        }

        cout << endl;
    }

    return 0;
}