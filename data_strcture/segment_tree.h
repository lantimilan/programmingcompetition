// segment_tree.h
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

ostream& operator<<(ostream& os, const pair<int, int>& data) {
  return os << "(" << data.first << "," << data.second << ")";
}

template<typename Data, typename Op>
class TreeNode {
 public:
  Data query(int start, int end) const;

 public:
  int l, r;
  Data data;
  TreeNode* left;
  TreeNode* right;
  // friend class SegmentTree;
};

template<typename Data, typename Op>
class SegmentTree {
public:
  SegmentTree(const vector<Data>& input);
  Data query(int l, int r) const {
    return nodes[0].query(l, r);
  }

private:
  // We use array of nodes instead of a tree with new/delete because too many
  // malloc cause fragmented memory and slow.
  vector<TreeNode<Data, Op>> nodes;
  // returns size of occupied slots in nodes
  int build_sub(int k, int l, int r, const vector<Data>& input);
};

template<typename Data, typename Op>
Data TreeNode<Data, Op>::query(int start, int end) const {
  assert(start+1 <= end);  // never query empty range
  assert(!(start >= r || end <= l));  // must have overlap
  if (start <= l && r <= end) {  // singleton, leaf
    return data;
  }
  int l1 = left->l;
  int r1 = left->r;
  int l2 = right->l;
  int r2 = right->r;
  if (start >= r1) {
    return right->query(max(l2, start), min(r2, end));
  } else if (end <= l2) {
    return left->query(max(l1, start), min(r1, end));
  }
  Data ldata = left->query(max(l1, start), min(r1, end));
  Data rdata = right->query(max(l2, start), min(r2, end));
  Op op;
  return op(ldata, rdata);
}

template<typename Data, typename Op>
SegmentTree<Data, Op>::SegmentTree(const vector<Data>& input) :
  nodes(input.size() * 2) {
  // Can we actually build the tree backwards, because root is at leftmost pos
  int total =  build_sub(0, 0, input.size(), input);
  cout << "done ctor\n";
  for (int i = 0; i < total; ++i) {
    cout << i << " "  << nodes[i].data << " " << nodes[i].l
      << " " << nodes[i].r << endl;
  }
}

// Returns the number of elements occupied in nodes array
// recursively build segment tree with preorder traversal (root, left, right)
template<typename Data, typename Op>
int
SegmentTree<Data, Op>::build_sub(int k, int l, int r, const vector<Data>& input) {
  TreeNode<Data, Op>& node = nodes[k];
  if (l + 1 >= r) {  // leaf
    node.l = l; node.r = r;
    node.data = input[l];
    node.left = node.right = nullptr;
    return k+1;
  }
  int m = (l + r) / 2;
  int lnext = k+1;
  int rnext = build_sub(k+1, l, m, input);
  int last = build_sub(rnext, m, r, input);
  node.l = l; node.r = r;
  node.left = &nodes[lnext];
  node.right = &nodes[rnext];
  Op op;
  node.data = op(node.left->data, node.right->data);
  return last;
}
