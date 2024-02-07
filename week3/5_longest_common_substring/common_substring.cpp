#include <iostream>
#include <set>
#include <vector>
#include <cassert>
#include <map>


using namespace std;

struct Answer {
	size_t i, j, len;
};

Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	for (size_t i = 0; i < s.size(); i++)
		for (size_t j = 0; j < t.size(); j++)
			for (size_t len = 0; i + len <= s.size() && j + len <= t.size(); len++)
				if (len > ans.len && s.substr(i, len) == t.substr(j, len))
					ans = {i, j, len};
	return ans;
}

static const long long p = 1000000007;
static const long long x = 17;
map<long long,set<int> > map_l;

bool string_equal(const string & s, int s_start, const string & t, int t_start, int len) {
	int s_end = s_start + len;
	while (s_start < s_end && s[s_start] == t[t_start]) {s_start++; t_start++;}
	if (s_start == s_end) return true;
	return false;
}

Answer find_answer_quick(const string & s, const string & t, const int len) {
	long long s_hash = 0;
	long long t_hash = 0;
	map_l.clear();
	long long x_power_l_m_1 = 1;

	for (int i = 0; i < len; i++) {
		s_hash = (s_hash * x + s[i]) % p;
		t_hash = (t_hash * x + t[i]) % p;
	}
	for (int i = 1; i < len; i++) {
		x_power_l_m_1 = (x_power_l_m_1 * x) % p; 
	}
	map_l[s_hash] = set<int> {0};
	
	for (int i = 1; i < s.size() - len + 1; i++) {
		s_hash = (((s_hash - s[i - 1] * x_power_l_m_1) * x + s[i + len - 1]) % p + p) % p;
		if (map_l.find(s_hash) == map_l.end()) {
			map_l[s_hash] = set<int> {i};
		} else {
			map_l[s_hash].insert(i);
		}
	}

	for (int i = 0; i < t.size() - len + 1; i++) {
		if (i > 0) {
			t_hash = (((t_hash - t[i -1] * x_power_l_m_1) * x + t[i + len - 1]) % p + p) % p;
		}
		if (map_l.find(t_hash) != map_l.end()) {
			for (int ind : map_l[t_hash]) {
				if (string_equal(s, ind, t, i, len)) 
				return Answer {(size_t)ind, (size_t)i, (size_t)len};
			}
		}
	}
	return Answer {0, 0, 0};

}

Answer solve_new(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	int s_len = s.size(), t_len = t.size();
	int min_len = min(s_len, t_len);
	int lo = 0, hi = min_len;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		Answer tmp = find_answer_quick(s, t, mid);
		if (tmp.len == 0) {
			hi = mid - 1;
		} else {
			ans = tmp;
			lo = mid + 1;
		}
	}
	return ans;
}

void test_solution() {
	assert(solve_new("aaa", "bb").i == 0);
}


int main() {
	//test_solution();
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve_new(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
