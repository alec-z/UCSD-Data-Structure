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
};

void test_solution() {
	string s("trololo");
	Solver solver(s);
	assert(solver.ask(0, 0, 7));
	assert(solver.ask(2, 4, 3));
	assert(solver.ask(3, 5, 1));
	assert(solver.ask(1, 3, 2) == false);
}

int main() {
	//test_solution();
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
