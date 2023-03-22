#include "headers/UFSets.hpp"
#include <iostream>

using namespace std;

int main()
{
    char data[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    UFSets<char> sets(data, sizeof(data) / sizeof(char));
    sets.HeightedUnion('A', 'B');
    sets.ShowRawData();
    sets.HeightedUnion('G', 'D');
    sets.ShowRawData();
    sets.HeightedUnion('I', 'J');
    sets.ShowRawData();
    sets.HeightedUnion('C', 'B');
    sets.ShowRawData();
    sets.HeightedUnion('A', 'C');
    sets.ShowRawData();
    sets.HeightedUnion('H', 'I');
    sets.ShowRawData();
    sets.HeightedUnion('F', 'E');
    sets.ShowRawData();
    sets.HeightedUnion('F', 'D');
    sets.ShowRawData();
    cout << sets << endl;
    return 0;
}