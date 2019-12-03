/*
  Here we cannot change value at fixed point, so let's not move it at all.

  We find how many elements from left and from right we must move, and how many are 
  equal to fixed point so they are optional to move.

  Based on these, we check if we can move enough elemets, and if not, return impossible.

  Then we move elements we need to move in L and R so that they are around fixed point,
  and do one mirror swap around fixed point.

  Then we simply sort elements in L and R similar to selection sort.

  Total number of swaps should be ~3/2 n, so ~75 as we need (it should be a bit less).
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

using namespace std;

class FixedPointReversals {
  public:
  vector<int> bad() {
    vector<int> result;
    result.push_back(-1);
    return result;
  }
  void rev(vector<int> &a, int l, int r, vector<int> &ans) {
    ans.push_back(l); ans.push_back(r + 1);
    while (l < r) {
      swap(a[l], a[r]);
      l++; r--;
    }
  }
  vector <int> sort(vector <int> A, int fixed) {
    int n = sz(A);

  	vector<int> b;
    for (int x : A) {
      b.push_back(x);
    }
    std::sort(all(b));

    if (b[fixed] != A[fixed]) {
      cerr << "Bad fixed" << endl;
      return bad();
    }
    int f = A[fixed];

    vector<int> ans;
    int lb = 0, le = 0;
    int rl = 0, re = 0;
    for (int i = 0; i < fixed; i++) {
      if (A[i] > f) {
        lb++;
      } else if (A[i] == f) {
        le++;
      }
    }
    for (int i = fixed + 1; i < n; i++) {
      if (A[i] < f) {
        rl++;
      } else if (A[i] == f) {
        re++;
      }
    }

    int needToMove = max(lb, rl);
    if (lb > rl) {
      if (rl + re < lb) {
        cerr << "rl + re < ll" << endl;
        return bad();
      }
    } else if (rl > lb) {
      if (lb + le < rl) {
        cerr << "lb + le < rl" << endl;
        return bad();
      }
    }

    int canMove = min(fixed, n - 1 - fixed);
    if (canMove < needToMove) {
      return bad();
    }

    for (int i = fixed - 1; i >= fixed - needToMove; i--) {
      int cur = fixed - i;
      if (cur <= lb) {
        if (A[i] > f) {
          continue;
        }
        for (int j = 0; j < i; j++) {
          if (A[j] > f) {
            rev(A, j, i, ans);
            break;
          }
        }
      } else {
        if (A[i] == f) {
          continue;
        }
        for (int j = 0; j < i; j++) {
          if (A[j] == f) {
            rev(A, j, i, ans);
            break;
          }
        }
      }
    }

    for (int i = fixed + 1; i <= fixed + needToMove; i++) {
      int cur = i - fixed;
      if (cur <= rl) {
        if (A[i] < f) {
          continue;
        }
        for (int j = n - 1; j > i; j--) {
          if (A[j] < f) {
            rev(A, i, j, ans);
            break;
          }
        }
      } else {
        if (A[i] == f) {
          continue;
        }
        for (int j = n - 1; j > i; j--) {
          if (A[j] == f) {
            rev(A, i, j, ans);
            break;
          }
        }
      }
    }

    if (needToMove > 0) {
      rev(A, fixed - needToMove, fixed + needToMove, ans);
    }

    for (int i = 0; i < fixed; i++) {
      if (A[i] == b[i]) {
        continue;
      }
      for (int j = i + 1; j < fixed; j++) {
        if (A[j] == b[i]) {
          rev(A, i, j, ans);
          break;
        }
      }
    }

    for (int i = fixed + 1; i < n; i++) {
      if (A[i] == b[i]) {
        continue;
      }
      for (int j = i + 1; j < n; j++) {
        if (A[j] == b[i]) {
          rev(A, i, j, ans);
          break;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (A[i] != b[i]) {
        cerr << "No sorted" << endl;
        return bad();
      }
    }

    return ans;
  }
};

// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	template<typename T> std::ostream& operator<<(std::ostream &os, const vector<T> &v) { os << "{"; for (typename vector<T>::const_iterator vi=v.begin(); vi!=v.end(); ++vi) { if (vi != v.begin()) os << ","; os << " " << *vi; } os << " }"; return os; }

	int verify_case(int casenum, const vector <int> &expected, const vector <int> &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int A[]                   = {10, 20, 30, 40, 50};
			int fixed                 = 2;
			int expected__[]          = { };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 1: {
			int A[]                   = {10, 20, 40, 30, 50};
			int fixed                 = 2;
			int expected__[]          = {-1 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 2: {
			int A[]                   = {20, 10, 10, 10, 10, 10};
			int fixed                 = 4;
			int expected__[]          = {0, 6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 3: {
			int A[]                   = {1, 50, 40, 30, 20, 10};
			int fixed                 = 0;
			int expected__[]          = {1, 6 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}
		case 4: {
			int A[]                   = {20, 10, 30, 50, 40};
			int fixed                 = 2;
			int expected__[]          = {0, 2, 3, 5 };

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}

		// custom cases

/*      case 5: {
			int A[]                   = ;
			int fixed                 = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 6: {
			int A[]                   = ;
			int fixed                 = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
/*      case 7: {
			int A[]                   = ;
			int fixed                 = ;
			int expected__[]          = ;

			std::clock_t start__      = std::clock();
			vector <int> received__   = FixedPointReversals().sort(vector <int>(A, A + (sizeof A / sizeof A[0])), fixed);
			return verify_case(casenum__, vector <int>(expected__, expected__ + (sizeof expected__ / sizeof expected__[0])), received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
