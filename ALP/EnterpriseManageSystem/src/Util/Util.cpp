#ifndef COMMON
#include "../Common.h"
#endif

using namespace std;

long parseLong(string str)
{
    return atoi(str.c_str());
}

string getSingleInput(string prompt = "")
{
    cout << (prompt.length() == 0 ? "Input:" : prompt);
    string ret = "";
    getline(cin, ret);
    return ret;
}