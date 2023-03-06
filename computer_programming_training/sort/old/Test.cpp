#include <iostream>

using namespace std;

void BubbleA(char (*str)[20], int size);
void BubbleB(char *str[], int size);

int main()
{
    char strA[][20]={"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
    char *strB[]   ={"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "an", "cake", "side"};
    BubbleA(strA, 12);
    BubbleB(strB, 12);
    for (int i = 0; i < 12; i++)
    {
        cout << strA[i] << endl;
    }
    cout << endl;
    for (int i = 0; i < 12; i++)
    {
        cout << strB[i] << endl;
    }
    return 0;
}