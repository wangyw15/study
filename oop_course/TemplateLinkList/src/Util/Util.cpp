#include <string>
#include <iostream>

int parseInt(std::string str)
{
    return atoi(str.c_str());
}

std::string getSingleInput(std::string prompt = "")
{
    std::cout << (prompt.length() == 0 ? "Input:" : prompt);
    std::string ret = "";
    std::getline(std::cin, ret);
    return ret;
}