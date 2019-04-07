#include "segment_tree.h"

#include <iostream>
using namespace std;

template <typename T>
class adder {
 public:
  T operator()(const T& a, const T& b) const { return a + b; }
};

template <typename T>
class getmin {
 public:
  T operator()(const T& a, const T& b) const { return std::min<T>(a, b); }
};

template <typename T>
class getgcd {
 public:
  T operator()(const T& a, const T& b) const {
    return gcd(a, b);
  }
 private:
  static T gcd(const T& a, const T& b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
  }
};

template <typename T>
class Combine {
 public:
  T operator()(const T& a, const T& b) const {
    int first = getmin<int>()(a.first, b.first);
    int second = getgcd<int>()(a.second, b.second);
    return T{first, second};
  }
};

template <typename T>
class GcdCount {
 public:
  T operator()(const T& a, const T& b) const {
    // cout << "op1: " << a << "," << "op2: " << b << endl;
    int second = getgcd<int>()(a.second, b.second);
    int first = 0;
    if (a.second == second) first += a.first;
    if (b.second == second) first += b.first;
    return T{first, second};
  }
};

int main() {
  // vector<int> v = {1, 2, 3};
  // SegmentTree<int, adder<int>> stree(v);
  // SegmentTree<int, getmin<int>> stree(v);
  // vector<int> v = {4, 3, 6};
  // SegmentTree<int, getgcd<int>> stree(v);
  vector<int> v = {1, 3, 2, 4, 2};
  vector<pair<int,int>> v2(5);
  for (int i = 0; i < 5; ++i) {
    v2[i] = make_pair(1, v[i]);
  }
  SegmentTree<pair<int, int>, GcdCount<pair<int,int>>> stree(v2);

  cout << "(cnt, gcd)" << endl;
  cout << stree.query(0, 5) << endl;
  cout << stree.query(1, 5) << endl;
  cout << stree.query(2, 5) << endl;
  cout << stree.query(3, 5) << endl;
  cout << stree.query(4, 5) << endl;
}
