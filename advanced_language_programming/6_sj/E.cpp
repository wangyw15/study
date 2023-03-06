#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>

using namespace std;

typedef struct Ship
{
    int time;
    vector<int> passengers;
} Ship;

int abs(int x)
{
    return x >= 0 ? x : -x;
}

int main()
{
    int n;
    while (cin >> n)
    {
        vector<Ship> ships;

        for (int i = 0; i < n; i++)
        {
            int ti, ki, tmp;
            cin >> ti >> ki;

            vector<int> passengers, countries;

            for (int j = 0; j < ki; j++)
            {
                cin >> tmp;
                passengers.push_back(tmp);
                countries.push_back(tmp);
            }
            Ship current;
            current.time = ti;
            current.passengers = passengers;
            ships.push_back(current);


            for (int j = 0; j < i; j++)
            {
                if (abs(current.time - ships[j].time) < 86400)
                {
                    countries.reserve(ships[j].passengers.size());
                    countries.insert(countries.end(), ships[j].passengers.begin(), ships[j].passengers.end());
                }
            }
            sort(countries.begin(), countries.end());
            auto pos = unique(countries.begin(), countries.end());
            cout << pos - countries.begin() << endl;
        }
    }
    return 0;
}