#include <cmath>

using namespace std;

void solve(const double a, const double b, const double c, double &x1, double &x2)
{
    double delta = b * b - 4 * a * c;
    x1 = (0 - b + sqrt(delta)) / (2 * a);
    x2 = (0 - b - sqrt(delta)) / (2 * a);
}