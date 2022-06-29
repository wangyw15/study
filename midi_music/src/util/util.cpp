#include <cstdlib>

void ClearConsole()
{
    #ifdef __linux__
    system("clear");
    #else
    system("cls");
    #endif
}