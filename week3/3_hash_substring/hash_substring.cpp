#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (long long i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (long long i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

const static long long x = 263;
const static long long p = 1000000007;

long long get_hash_code(const string &s, long long len) {
    long long hash = 0;
    for (long long i = 0; i < len; i++) {
        hash = ((hash * x) + (long long)s[i]) % p;
    }
    return hash;
}

bool string_equal(const string & s1, long long s1_start,  const string &s2, long long len) {
    long long i = s1_start;
    long long j = 0;
    while (j < len && s1[i] == s2[j]) { i++; j++; }
    if (j == len) return true;
    return false;

}

std::vector<int> get_occurrences_new(const Data& input) {
    std::vector<int> ans;
    const string& s = input.pattern, t = input.text;
    long long hash_p = get_hash_code(s, s.size());
    long long hash_t = get_hash_code(t, s.size());
    if (hash_p == hash_t && string_equal(t, 0, s, s.size())) {
        ans.push_back(0);
    }

    long long x_pow_pl =  1;
    for (long long i = 1; i < s.size(); i++) x_pow_pl = (x_pow_pl * x) % p;
    
    for (long long i = 1; i < t.size() - s.size() + 1; i++) {
        hash_t = (hash_t - (long long)t[i - 1] * x_pow_pl % p) * x % p + (long long)t[i + s.size() - 1];
        hash_t = (hash_t % p + p) % p;
        if (hash_t == hash_p) {
            if (string_equal(t, i, s, s.size())) {
                ans.push_back((int)i);
            }
        }
    }

    return ans;
}

void test_solution() {
    Data input{"aaaaa", "baaaaaaa"};
    get_occurrences_new(input);
}




int main() {
    //test_solution();
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences_new(read_input()));
    return 0;
}
