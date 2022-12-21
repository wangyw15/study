#include <algorithm>
#include <iostream>
using namespace std;
const long long inf = 1e18;
int tot;
long long K;
long long Base[100], fax[100], fay[100];

long long find_fa(long long x) {
  long long p;
  for (int i = 0; i < tot; ++i)
    if (Base[i + 1] >= x) {
      p = Base[i];
      break;
    }
  return (x - p - 1) / K + 1;
}

void solve(int &Siz, long long x, long long f[]) {
  Siz = 0;
  do {
    if (x == 1)
      break;
    f[++Siz] = x;
    x = find_fa(x);
  } while (x != 1);
  f[++Siz] = 1;
}

void solve() {
  long long x, y;
  K = 0ll;
  tot = 0;
  cin >> K >> x >> y;
  for (int i = 0; i < 100; ++i)
    Base[i] = 0ll;
  Base[1] = 1ll;
  Base[0] = 0ll;
  for (int i = 2; i <= 99; ++i) {
    Base[i] = Base[i - 1] * (K + 1);
    if (Base[i] > inf || Base[i] < 0) {
      tot = i - 1;
      break;
    }
  }
  int Sizex = 0, Sizey = 0;
  solve(Sizex, x, fax);
  solve(Sizey, y, fay);
  // do
  // {
  // 	if(x == 1) break;
  // 	fax[++sizex] = x; x = find_fa(x);
  // }while(x != 1);
  // fax[++sizex] = 1;

  for (int i = 1; i <= Sizex; ++i)
    cout << fax[i] << ' ';
  cout << '\n';

  // do
  // {
  // 	if(y == 1) break;
  // 	fay[++Sizey] = y; y = find_fa(y);
  // }while(y != 1);
  // fay[++Sizey] = 1;

  for (int i = 1; i <= Sizey; ++i)
    cout << fay[i] << ' ';
  cout << '\n';
  
  long long lst = 1;
  for (int i = 1; i <= min(Sizex, Sizey); ++i) {
    if (fax[Sizex - i] != fay[Sizey - i])
      break;
    lst = fax[Sizex - i];
  }
  cout << lst << '\n';
}

signed main() {
  long long T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}
/*
3
2 6 7
2 4 5
3 20 2
100
10000000000000 20000000000005 20000000000006
*/