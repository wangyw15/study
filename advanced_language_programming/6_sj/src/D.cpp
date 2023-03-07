#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int abs(int x)
{
    return x >= 0 ? x : -x;
}

int main()
{
    int n, input;
    cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; i++)
    {
        cin >> input;
        nums.push_back(input);
    }
    int count = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        for(int j = 0; j < nums.size(); j++)
        {
            if(abs(nums[i] - nums[j]) == 1)
                count++;
        }
    }
    cout << count / 2;
    return 0;
}