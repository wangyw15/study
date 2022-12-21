#include <iostream>

#include "String/String.h"

int main()
{
    String a("aaa");
    std::cout << a.IsEmpty() << std::endl;
    String c("");
    std::cout << c.IsEmpty() << std::endl;
    return 0;
}