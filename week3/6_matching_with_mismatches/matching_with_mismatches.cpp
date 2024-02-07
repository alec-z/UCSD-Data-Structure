#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solver {
	static const long long m1 = 1000000007;
	static const long long m2 = 1000000009;

	static const long long x = 261;
	string s;
	vector<long long> hash_from_0_m1;
	vector<long long> hash_from_0_m2;
	vector<long long> x_power_m1, x_power_m2;
public:	
	Solver(string s) : s(s) {
		hash_from_0_m1.resize(s.size() + 1, 0);
		hash_from_0_m2.resize(s.size() + 1, 0);
		x_power_m1.resize(s.size() + 1);
		x_power_m2.resize(s.size() + 1);
		x_power_m1[0] = 1;
		x_power_m2[0] = 1;
		// initialization, precalculation
		for (long long i = 1; i <= s.size(); i++) {
			hash_from_0_m1[i] = (hash_from_0_m1[i - 1] * x + s[i - 1]) % m1;
			hash_from_0_m2[i] = (hash_from_0_m2[i - 1] * x + s[i - 1]) % m2;
			x_power_m1[i] = x_power_m1[i - 1] * x % m1;
			x_power_m2[i] = x_power_m2[i - 1] * x % m2;
		}
	}
	bool ask(int a, int b, int l) {
		long long hash_a_m1 = (hash_from_0_m1[a + l] - hash_from_0_m1[a] * x_power_m1[l] % m1) % m1 + m1;
		long long hash_b_m1 = (hash_from_0_m1[b + l] - hash_from_0_m1[b] * x_power_m1[l] % m1) % m1 + m1;
		if (hash_a_m1 % m1 != hash_b_m1 % m1) return false;

		long long hash_a_m2 = (hash_from_0_m2[a + l] - hash_from_0_m2[a] * x_power_m2[l] % m2) % m2 + m2;
		long long hash_b_m2 = (hash_from_0_m2[a + l] - hash_from_0_m2[a] * x_power_m2[l] % m2) % m2 + m2;
		return hash_a_m2 % m2 == hash_b_m2 % m2;
	}
	long long hash_m1(int lo, int hi) {
		int l = hi - lo + 1;
		long long hash_m1 = (hash_from_0_m1[lo + l] - hash_from_0_m1[lo] * x_power_m1[l] % m1) % m1 + m1;
		hash_m1 %= m1;
		return hash_m1;
	}
	long long hash_m2(int lo, int hi) {
		int l = hi - lo + 1;
		long long hash_m2 = (hash_from_0_m2[lo + l] - hash_from_0_m2[lo] * x_power_m2[l] % m2) % m2 + m2;
		hash_m2 %= m2;
		return hash_m2;
	}
};
bool try_solve(int k, Solver & solver_t, int lo_t, int hi_t, Solver & solver_p, int lo_p, int hi_p);

vector<int> solve(int k, const string &text, const string &pattern) {
	vector<int> pos;
	Solver solver_t(text);
	Solver solver_p(pattern);
	for (int i=0; i < text.size() - pattern.size() + 1; i++) {
		if (try_solve(k, solver_t, i, i+pattern.size() -1, solver_p, 0, pattern.size() - 1)) {
			pos.push_back(i);
		}
	}
	return pos;
}

bool check_equality(Solver & solver_t, int lo_t, int hi_t, Solver & solver_p, int lo_p, int hi_p) {
	return (solver_t.hash_m1(lo_t, hi_t) == solver_p.hash_m1(lo_p, hi_p)) && (solver_t.hash_m2(lo_t, hi_t) == solver_p.hash_m2(lo_p, hi_p));
}

bool try_solve(int k, Solver & solver_t, int lo_t, int hi_t, Solver & solver_p, int lo_p, int hi_p) {
	int len = hi_t - lo_t + 1;
	if (len <= 0)  return false;
	if (len <= k) {
		return true;
	}
	if (k == 0) {
		return check_equality(solver_t, lo_t, hi_t, solver_p, lo_p, hi_p);
	}

	if (check_equality(solver_t, lo_t, hi_t, solver_p, lo_p, hi_p)) {
		return true;
	}
	int mid_t = (lo_t + hi_t) / 2, mid_p = (lo_p + hi_p) /2;

	for (int s = 0; s <= k; s++) {
		bool left = try_solve(s, solver_t, lo_t, mid_t, solver_p, lo_p, mid_p);
		bool all = left && try_solve(k - s, solver_t, mid_t + 1, hi_t, solver_p, mid_p + 1, hi_p);
		if (all) {
			return true;
		}
	}
	return false;
}

void test_solution() {
	//solve(0, "ababab", "baaa");
	solve(2, "xabcabc", "ccc");

}
int main() {
	//test_solution();
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
