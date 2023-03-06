#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main()
{
    int n, input;
    cin >> n;
    int count[n];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; i++)
    {
        cin >> input;
        cout << ++count[input] << (i < n - 1 ? " " : "");
    }
    return 0;
}