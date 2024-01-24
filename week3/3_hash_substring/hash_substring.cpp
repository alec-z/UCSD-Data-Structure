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
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}

const static size_t x = 263;
const static size_t p = 1000000007;

size_t get_hash_code(const string &s, size_t len) {
    size_t hash = 1;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash * x) + s[i]) % p;
    }
    return hash;
}

bool string_equal(const string & s1, size_t s1_start,  const string &s2, size_t len) {
    size_t i = s1_start;
    size_t j = 0;
    while (j < len && s1[i++] == s2[j++]) {}
    if (j == len) return true;
    return false;

}

std::vector<int> get_occurrences_new(const Data& input) {
    std::vector<int> ans;
    const string& s = input.pattern, t = input.text;
    size_t hash_p = get_hash_code(s, s.size());
    size_t hash_t = get_hash_code(t, s.size());
    if (hash_p == hash_t && string_equal(t, 0, s, s.size())) {
        ans.push_back(0);
    }

    size_t x_pow_pl =  1;
    for (size_t i = 1; i < s.size(); i++) x_pow_pl = (x_pow_pl * x) % p;
    
    for (size_t i = 1; i < t.size() - s.size() + 1; i++) {
        hash_t = (hash_t - t[i - 1] * x_pow_pl) * x  + t[i + s.size() - 1];
        hash_t %= p;
        if (hash_t == hash_p) {
            if (string_equal(t, i, s, s.size())) {
                ans.push_back((int)i);
            }
        }
    }

    return ans;
}




int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences_new(read_input()));
    return 0;
}
