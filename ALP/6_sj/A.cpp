#include <iostream>

using namespace std;

int main()
{
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        double grade1, grade2, grade3;
        cin >> grade1 >> grade2 >> grade3;
        cout << grade1 * 0.45 + grade2 * 0.45 + grade3 * 0.1 << endl;
    }
    return 0;
}