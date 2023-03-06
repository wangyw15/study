#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int n, m, index = 1;
    while (cin >> n >> m)
    {
        vector<int> people;
        for (int i = 1; i <= n; i++)
            people.push_back(i);

        int currentNumber = 1;
        int currentPeople = 0;
        while (people.size() != 1)
        {
            if(currentNumber == m)
            {
                people.erase(people.begin() + currentPeople);
                currentPeople -= 1;
            }

            currentPeople = (currentPeople + 1) % people.size();
            currentNumber = currentNumber % m + 1;
        }
        cout << "Case " << index++ << ": " << n << ", " << m << ", " << people[0] << endl;
    }
    return 0;
}