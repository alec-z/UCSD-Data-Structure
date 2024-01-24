#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::swap;
using std::vector;

class HeapBuilder {
 private:
  vector<int> data_;
  vector<pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for (int i = 0; i < n; ++i) cin >> data_[i];
  }

  void siftDown(int i) {
    int c = i * 2 + 1;
    while (c < data_.size()) {
      if (c + 1 < data_.size() && data_[c] > data_[c+1]) { c++; };
      if (data_[i] > data_[c]) {
        swap(data_[i], data_[c]);
        swaps_.push_back(make_pair(i, c));
        i = c;
        c = i * 2 + 1;
      } else {
        break;
      }
    }
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap,
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for (int i = data_.size() / 2 - 1; i >= 0; i--) {
      siftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
