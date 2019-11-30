/* 
  Author: Adilet Zhaxybay

  My idea is very similar to editorial (https://codeforces.com/blog/entry/70898?locale=en),
  but I started from the other end (calculation from start to finish, not vice versa), and
  used prefix sums to do the summation for each dp[i][j][k]

  Here dp[i][j][k] is number of ways to get to (i, j) if last moves were 
  k (where k = 0 - from above, k = 1 - from left).
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
#define y1 stupid_cmath
#define left stupid_left
#define right stupid_right

const int MAXN = 2050;
const int mod = (int) 1e9 + 7;

int n, m;
char c[MAXN][MAXN];
int up[MAXN][MAXN];
int left[MAXN][MAXN];
int dp[MAXN][MAXN][2];
int sum[MAXN][MAXN][2];


int getSum(int i, int j, int k) {
  if (i < 0 || j < 0) {
    return 0;
  }
  return sum[i][j][k];
}

int main() {
  //assert(freopen("input.txt","r",stdin));
  //assert(freopen("output.txt","w",stdout));  

  scanf("%d %d\n", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%c", &c[i][j]);
    }
    scanf("\n");
  }

  if (n == 1 && m == 1) {
    cout << 1 << endl;
    return 0;
  }

  for (int j = 0; j < m; j++) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
      if (c[i][j] == 'R') {
        sum++;
      }
    }
    int p = 0;
    for (int i = 0; i < n; i++) {
      int below = n - 1 - i;
      while (sum > below) {
        p++;
        if (c[p][j] == 'R') {
          sum--;
        }
      }
      up[i][j] = p;
    }
  }

  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = 1; j < m; j++) {
      if (c[i][j] == 'R') {
        sum++;
      }
    }
    int p = 0;
    for (int j = 0; j < m; j++) {
      int toR = m - 1 - j;
      while (sum > toR) {
        p++;
        if (c[i][p] == 'R') {
          sum--;
        }
      }
      left[i][j] = p;
    }
  }

  for (int i = 0; i < n; i++) {
    if (up[i][0] == 0) {
      dp[i][0][0] = 1;
      sum[i][0][0] = 1; 
    }
  }
  for (int j = 0; j < m; j++) {
    if (left[0][j] == 0) {
      dp[0][j][1] = 1;
      sum[0][j][1] = 1;
    }
  }

  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      for (int k = 0; k < 2; k++) {
        if (k == 0) {
          int from = up[i][j];
          dp[i][j][k] = (getSum(i - 1, j, 1 - k) - getSum(from - 1, j, 1 - k) + mod) % mod;
        } else {
          int from = left[i][j];
          dp[i][j][k] = (getSum(i, j - 1, 1 - k) - getSum(i, from - 1, 1 - k) + mod) % mod;
        }
        if (k == 0) {
          sum[i][j][k] = (j == 0 ? 0 : sum[i][j - 1][k]);
          sum[i][j][k] = (sum[i][j][k] + dp[i][j][k]) % mod;
        } else {
          sum[i][j][k] = (i == 0 ? 0 : sum[i - 1][j][k]);
          sum[i][j][k] = (sum[i][j][k] + dp[i][j][k]) % mod;
        }
        //cerr << "DP: " << i << " " << j << " " << k << " : " << dp[i][j][k] << endl;
        //cerr << "SUM: " << i << " " << j << " " << k << " : " << sum[i][j][k] << endl;
      }
    }
  }

  cout << (dp[n - 1][m - 1][0] + dp[n - 1][m - 1][1]) % mod << endl;

  return 0;
}