#include <string>

using namespace std;

string convertBase(int num, int baseNum)
{
    string chars[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
    string ret = "", tmp = "";
    int a = num;
    while (a > 0)
    {
        tmp += chars[a % baseNum];
        a /= baseNum;
    }
    for (int i = tmp.size() - 1; i >= 0; i--)
    {
        ret += tmp[i];
    }
    return ret;
}