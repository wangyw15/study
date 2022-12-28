#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

// https://www.cnblogs.com/cherryljr/p/6519748.html
void GetFailure(const string &pat, int f[])
{
    int j = 0, k = -1;
    f[0] = -1;
    while (j < pat.length() - 1)
    {
        if (k == -1 || pat[k] == pat[j])
        {
            j++;
            k++;
            if (pat[j] == pat[k])
            {
                f[j] = f[k];
            }
            else
            {
                f[j] = k;
            }
        }
        else
        {
            k = f[k];
        }
    }
}

int KMPFind(const string &str, const string &pat, int p = 0)
{
    int *f= new int[pat.length()];
    GetFailure(pat, f);
    int i = p, j = 0;
    while (i < str.length() && j < pat.length() && pat.length() - j <= str.length() - i)
    {
        if (j == -1 || pat[j] == str[i])
        {
            i++;
            j++;
        }
        else
        {
            j = f[j];
        }
    }
    delete []f;
    if (j < pat.length())
    {
        return -1;
    }
    else
    {
        return i - j;
    }
}

int main()
{
    cout << KMPFind("aaabdasxd", "abda") << endl;
    return 0;
}