/*
 * Easy dfs
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

bool used[55][55];
int n, m;

const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, 1, -1};

class Coastlines {
  public:
  int dfs(vector<string> a, int i, int j) {
  	used[i][j] = true;
  	int res = 0;
  	for (int k = 0; k < 4; k++) {
  		int ii = i + di[k], jj = j + dj[k];
  		if (ii < 0 || ii >= n || jj < 0 || jj >= m) {
  			res++;
  			continue;
  		}
  		if (a[ii][jj] == '.') {
  			res++;
  			continue;
  		}
  		if (!used[ii][jj]) {
  			res += dfs(a, ii, jj);
  		}
  	}
  	return res;
  }	
  int longest(vector <string> a) {
  	n = sz(a), m = sz(a[0]);
  	memset(used, 0, sizeof(used));
  	int ans = 0;
  	for (int i = 0; i < sz(a); i++) {
  		for (int j = 0; j < m; j++) {
  			if (!used[i][j] && a[i][j] == 'X') {
  				ans = max(ans, dfs(a, i, j));
  			}
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
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
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
			string map[]              = {"...",
 ".X.",
 "..."};
			int expected__            = 4;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			string map[]              = {".XX",
 ".X.",
 "..."};
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			string map[]              = {"."};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			string map[]              = {".XX...",
 "XX...X",
 "X...XX",
 "......",
 ".XXXX."};
			int expected__            = 12;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			string map[]              = {"XXX",
 "X.X",
 "XXX"};
			int expected__            = 16;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			string map[]              = {"XXXXX",
 "X...X",
 "X.X.X",
 "X...X",
 "XXXXX"};
			int expected__            = 32;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			string map[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			string map[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			string map[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = Coastlines().longest(vector <string>(map, map + (sizeof map / sizeof map[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
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
