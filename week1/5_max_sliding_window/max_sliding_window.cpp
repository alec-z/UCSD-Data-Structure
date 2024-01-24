#include <iostream>
#include <vector>
#include <list>

using std::cin;
using std::cout;
using std::vector;
using std::list;
using std::max;

void max_sliding_window_naive(vector<int> const & A, int w) {
    int window_max_pos = 0;
    list<int> aux_w;
    aux_w.push_back(A[0]);

    for (size_t j = 1; j < w; ++j) {
        while (!aux_w.empty() && A[j] > aux_w.back()) {
            aux_w.pop_back();
        }
        aux_w.push_back(A[j]);
    }
    std::cout << aux_w.front() << " ";


    for (size_t i = 1; i < A.size() - w + 1; ++i) {
        if (aux_w.front() == A[i - 1]) aux_w.pop_front();
        int new_comer = A[i + w -1];
        while (!aux_w.empty() && new_comer > aux_w.back()) {
            aux_w.pop_back();
        }
        aux_w.push_back(new_comer);
        cout << aux_w.front() << " ";
    }

    return;
}


int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window_naive(A, w);

    return 0;
}
