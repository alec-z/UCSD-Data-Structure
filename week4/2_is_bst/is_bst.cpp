#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;
  int max_t;
  int min_t;

  Node() : key(0), left(-1), right(-1), max_t(std::numeric_limits<int>::min()), min_t(std::numeric_limits<int>::max()) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_), max_t(std::numeric_limits<int>::min()), min_t(std::numeric_limits<int>::max()) {}
};

int getMaxFromBST(vector<Node>& tree, int root_index) {
  if (tree[root_index].max_t > std::numeric_limits<int>::min()) return tree[root_index].max_t;
  int right = tree[root_index].right;
  if (right == -1) tree[root_index].max_t = tree[root_index].key;
  else tree[root_index].max_t = getMaxFromBST(tree, right);

  return tree[root_index].max_t;
}

int getMinFromBst(vector<Node>& tree, int root_index) {
  if (tree[root_index].min_t < std::numeric_limits<int>::max()) return tree[root_index].min_t;
  int left = tree[root_index].left;
  if (left == -1) tree[root_index].min_t = tree[root_index].key;
  else tree[root_index].min_t = getMinFromBst(tree, left);

  return tree[root_index].min_t;
}

bool checkBST(vector<Node>& tree, int root_index) {
  if (root_index == -1) return true;
  int key = tree[root_index].key, left = tree[root_index].left, right = tree[root_index].right;
  return checkBST(tree, left) && (left == -1 || getMaxFromBST(tree, left) < key) && checkBST(tree, right) && (right == -1 || getMinFromBst(tree, right) > key);
}

bool IsBinarySearchTree(vector<Node>& tree) {
  // Implement correct algorithm here
  if (tree.size() == 0) return true;
  return checkBST(tree, 0);
}


int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
