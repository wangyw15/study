#include "headers/UFSets.hpp"
#include <iostream>

using namespace std;

int main()
{
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    UFSets<char> sets(data, sizeof(data) / sizeof(char));
    sets.Union('A', 'B');
    sets.ShowRawData();
    sets.Union('G', 'D');
    sets.ShowRawData();
    sets.Union('I', 'J');
    sets.ShowRawData();
    sets.Union('C', 'B');
    sets.ShowRawData();
    sets.Union('A', 'C');
    sets.ShowRawData();
    sets.Union('H', 'I');
    sets.ShowRawData();
    sets.Union('F', 'E');
    sets.ShowRawData();
    sets.Union('F', 'D');
    sets.ShowRawData();
    cout << sets << endl;
    return 0;
}