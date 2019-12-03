/*
  Based on editorial from https://codeforces.com/blog/entry/70654 
  and this submission: https://codeforces.com/contest/1236/submission/62802483
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <utility>
#include <iomanip>

using namespace std;

#define sz(x) (int) x.size()
#define unique(x) x.erase(unique(x.begin(), x.end()), x.end())
#define all(a) a.begin(), a.end()
#define sqr(x) ((x) * (x)) 
#define y1 aksjdaskdjksjfksdjf
#define left kdnvldvoiwejifejg
#define right lkdsjflksdjfdjfk

const int MAXN = 105000;

int n, m;
int a[MAXN];
int l[MAXN], r[MAXN];

void solveL() {
  map<int, int> mp;
  for (int i = m - 1; i >= 0; i--) {
    mp[a[i] + i + 1] = mp[a[i] + i + 2] + 1;
  }
  for (int i = 0; i < n; i++) {
    l[i] = max(i - m - 1 + mp[i], 0);
  }
}

void solveR() {
  map<int, int> mp;
  for (int i = m - 1; i >= 0; i--) {
    mp[a[i] - i - 1] = mp[a[i] - i - 2] + 1;
  }
  for (int i = 0; i < n; i++) {
    r[i] = min(i + m + 1 - mp[i], n - 1);
  }
}

int main() { 

  scanf("%d %d", &n, &m);

  if (n == 1) {
    printf("0\n");
    return 0;
  }

  for (int i = 0; i < m; i++) {
    scanf("%d", &a[i]);
    a[i]--;
  }

  solveL();
  solveR();

  long long ans = 0;

  for (int i = 0; i < n; i++) {
    cerr << l[i] << " " << r[i] << endl;
    ans += 1ll * (r[i] - l[i] + 1);
  }

  cout << ans << endl;

  return 0;
}