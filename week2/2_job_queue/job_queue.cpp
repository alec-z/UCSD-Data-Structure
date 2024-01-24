#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;
  vector<pair<long, long>> heap;
  int sh = 0;


  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  bool less(pair<long, long> p1, pair<long, long> p2) {
    if (p1.first == p2.first) {
      return p1.second < p2.second;
    }
    return p1.first < p2.first;
  }

  void addHeap(long finish_time, long thread_id) {
    if (sh == heap.size()) heap.resize(2 * sh + 1);
    heap[sh++] = make_pair(finish_time, thread_id);
    int cur = sh - 1;
    int parent = (cur - 1) / 2;
    while (parent >= 0) {
      if (!less(heap[cur], heap[parent])) break;
      swap(heap[cur], heap[parent]);
      cur = parent;
      parent = (cur - 1) / 2;
    }
  }

  pair<long, long> removeMin() {
    if (sh == 0) return make_pair(-1, -1);
    pair<long, long> min = heap[0];
    swap(heap[--sh], heap[0]);
    int cur = 0, c = cur * 2 + 1;
    while (c < sh) {
      if (c + 1 < sh && less(heap[c + 1], heap[c])) c++;
      if (!less(heap[c], heap[cur])) break;
      swap(heap[cur], heap[c]);
      cur = c;
      c = cur * 2 + 1;
    }
    return min;
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    for (int i = 0; i < num_workers_; i ++){
      addHeap(0, i);
    }
    for (int i = 0; i < jobs_.size(); i++) {
      pair<long, long> cur = removeMin();
      assigned_workers_[i] = cur.second;
      start_times_[i] = cur.first;
      addHeap(cur.first + jobs_[i], cur.second);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
