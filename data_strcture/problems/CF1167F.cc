// data_strcture/problems/CF1167F.cc

// red_black_tree.h
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
using namespace std;

// A red-black tree is a binary search tree with four properties:
// 1. Each node is red or black.
// 2. Root is black.
// 3. Red node has only black children.
// 4. Any path from root to a null leaf has the same number of black nodes.
enum RBColor {
    RED = 0,
    BLACK = 1
};

template <typename T>
class RBTreeNode {
public:
    RBTreeNode* Lookup(const T& key) const;
    pair<RBTreeNode<T>*, bool> Insert(const T& key);
    // Returns cnt and sum of nodes greater or equal to key.
    pair<int, long long> GetStats(const T& key) const;
    void Print() const;

private:
    // Returns a new red node that is a child of this.
    RBTreeNode<T>* CreateNode(const T& key);
    // Returns node and true if a new node created.
    // This one does insertion without fixing red/black property
    pair<RBTreeNode<T>*, bool> InsertHelper(const T& key);
    // Restore red/black property at this node.
    void Fixup();

public:
    T key;
    RBColor color;
    int rcnt;  // number of nodes in subtree, including self
    long long rsum;  // sum of values of subtree, including self

    RBTreeNode *left, *right;
    RBTreeNode *parent;
};

template <typename T>
class RBTree {
public:
    // Returns the node, or null if not found.
    RBTreeNode<T>* Lookup(const T& key) const;

    // Returns (cnt, sum) of equal or larger nodes
    pair<int, long long> GetStats(const T& key) const {
      return root->GetStats(key);
    }

    // Returns true if a new key inserted, false if key already exists.
    pair<RBTreeNode<T>*, bool> Insert(const T& key) {
      if (root == nullptr) {
        // cerr << "root is null\n";
        RBTreeNode<T>* newnode = new RBTreeNode<T>();
        newnode->key = key;
        newnode->color = BLACK;  // root is black
        newnode->left = newnode->right = nullptr;
        newnode->parent = nullptr;
        newnode->rcnt = 1;
        newnode->rsum = key;
        root = newnode;
        return make_pair(root, true);
      } else {
        auto ret = root->Insert(key);
        // update root because rotation may move old root down.
        while (root->parent) {
            root = root->parent;
        }
        return ret;
      }
    }

    void Print() const {
        if (root) { root->Print(); }
        else { cout << "Empty tree.\n"; }
    }

    // Not implemented.
    bool Delete(const T& key) { return false; }

private:
    RBTreeNode<T>* root = nullptr;
};

// impl
template <typename T>
RBTreeNode<T>* RBTreeNode<T>::Lookup(const T& key) const {
  if (this->key == key) return this;
  else if (this->key < key) return right->Lookup(key);
  else return left->Lookup(key);
}

template <typename T>
pair<RBTreeNode<T>*, bool> RBTreeNode<T>::Insert(const T& key) {
    auto ret = InsertHelper(key);
    ret.first->Fixup();
    return ret;
}

template <typename T>
RBTreeNode<T>* RBTreeNode<T>::CreateNode(const T& key) {
   RBTreeNode<T>* newnode = new RBTreeNode<T>();
   newnode->key = key;
   newnode->color = RED;
   newnode->left = newnode->right = nullptr;
   newnode->parent = this;
   newnode->rcnt = 1;
   newnode->rsum = key;
}

template <typename T>
pair<RBTreeNode<T>*, bool> RBTreeNode<T>::InsertHelper(const T& key) {
    if (this->key == key) return make_pair(this, false);
    else if (this->key < key) {
        if (right == nullptr) {
            RBTreeNode<T>* newnode = CreateNode(key);
            this->right = newnode;
            RBTreeNode<T>* curr = newnode->parent;
            while (curr != nullptr) {  // only root has parent = null
              curr->rcnt++;
              curr->rsum += key;
              curr = curr->parent;
            }
            // traverse up to root to ++rcnt and rsum += key
            return make_pair(newnode, true);
        } else {
            return right->InsertHelper(key);
        }
    } else {
        if (left == nullptr) {
            RBTreeNode<T>* newnode = CreateNode(key);
            this->left = newnode;
            // traverse up to root to ++rcnt and rsum += key
            RBTreeNode<T>* curr = newnode->parent;
            while (curr != nullptr) {
              curr->rcnt++;
              curr->rsum += key;
              curr = curr->parent;
            }
            return make_pair(newnode, true);
        } else {
            return left->InsertHelper(key);
        }
    }
}

template <typename T>
void RBTreeNode<T>::Fixup() {
    // cerr << "Fixup for " << key << endl;
    // fix root is simple, just color it to black
    if (parent == nullptr) {
        color = BLACK;
        return;
    }
    if (parent->color == BLACK) {  // red child must have black parent
        return;
    }
    // red child and red parent, need fix
    // Notice that in this case, child must have grant parent, because
    // root cannot be red, so parent cannot be root.
    // Case 1: parent P has sibling S that is black, or sibling is null
    // Case 2: parent P has sibling S that is red
    assert(parent->parent != nullptr);

    RBTreeNode<T>* oldparent = parent;
    RBTreeNode<T>* grandpa = parent->parent;
    RBTreeNode<T>* greatpa = grandpa->parent;
    // Subcases
    // Sub1: P(red), S(black), K(red), G(black)
    // Sub1' P(black), S(black), K(red), G(red)
    //     G                   P
    //    / \                 / \
    //   P   S        =>     K   G
    //  / \ / \                 / \
    // K  1 2  3               1   S
    //                            / \
    //                           2   3
    if (parent->left == this && grandpa->left == parent &&
        (grandpa->right == nullptr || grandpa->right->color == BLACK)) {
        // cerr << "Subcase 1\n";
        // Record G and P
        int gcnt = grandpa->rcnt;
        int g1cnt = grandpa->right ? grandpa->right->rcnt : 0;
        int p1cnt = parent->right ? parent->right->rcnt : 0;
        long long gsum = grandpa->rsum;
        long long g1sum = grandpa->right ? grandpa->right->rsum : 0;
        long long p1sum = parent->right ? parent->right->rsum : 0;
        // stitch P into G's parent
        parent->parent = greatpa;
        if (greatpa != nullptr) {
            if (greatpa->left == grandpa) { greatpa->left = parent; }
            else { greatpa->right = parent; }
        }
        RBTreeNode<T>* p1 = parent->right;
        parent->right = grandpa; grandpa->parent = parent;
        grandpa->left = p1; if (p1 != nullptr) p1->parent = grandpa;
        // color
        parent->color = BLACK;
        grandpa->color = RED;
        // cnt and sum
        parent->rcnt = gcnt;
        parent->rsum = gsum;
        grandpa->rcnt = p1cnt + 1 + g1cnt;
        grandpa->rsum = p1sum + grandpa->key + g1sum;
        return;
    }
    // Sub2: P(red), S(black), K(red), G(black)
    // Sub2' P(red), S(black), K(black), G(red)
    //     G                   K
    //    / \                 / \
    //   P   S        =>     P    G
    //  / \ / \             / \  / \
    // 1  K 2  3           1  4  5  S
    //   / \                       / \
    //  4   5                     2   3
    if (parent->right == this && grandpa->left == parent &&
        (grandpa->right == nullptr || grandpa->right->color == BLACK)) {
        // cerr << "Subcase 2\n";
        // record K, P, G
        int k1cnt = (this->left) ? this->left->rcnt : 0;
        int k2cnt = (this->right) ? this->right->rcnt : 0;
        int pcnt = parent->rcnt;
        int p1cnt = (parent->left) ? parent->left->rcnt : 0;
        int gcnt = grandpa->rcnt;
        int scnt = (grandpa->right) ? grandpa->right->rcnt : 0;
        long long k1sum = (this->left) ? this->left->rsum : 0;
        long long k2sum = (this->right) ? this->right->rsum : 0;
        long long psum = parent->rsum;
        long long p1sum = (parent->left) ? parent->left->rsum : 0;
        long long gsum = grandpa->rsum;
        long long ssum = (grandpa->right) ? grandpa->right->rsum : 0;

        RBTreeNode<T>* p4 = this->left;
        RBTreeNode<T>* p5 = this->right;
        // reset parent to greatpa, must use oldparent for
        this->parent = greatpa;
        if (greatpa != nullptr) {
            if (greatpa->left == grandpa) { greatpa->left = this; }
            else { greatpa->right = this; }
        }
        // must use oldparent because parent is greatpa now.
        this->left = oldparent; oldparent->parent = this;
        this->right = grandpa; grandpa->parent = this;
        oldparent->right = p4; if (p4) p4->parent = oldparent;
        grandpa->left = p5; if (p5) p5->parent = grandpa;
        // color
        this->color = BLACK;
        grandpa->color = RED;
        // cnt and sum
        this->rcnt = gcnt; this->rsum = gsum;
        oldparent->rcnt = p1cnt + 1 + k1cnt;
        oldparent->rsum = p1sum + oldparent->key + k1sum;
        grandpa->rcnt = k2cnt + 1 + scnt;
        grandpa->rsum = k2sum + grandpa->key + ssum;
        return;
    }
    // Sub3: P(red), S(black), K(red), G(black)
    // Sub3' P(red), S(black), K(black), G(red)
    //     G                   K
    //    / \                 / \
    //   S   P        =>     G   P
    //  / \ / \             / \  / \
    // 2  3 K  1           S   4 5  1
    //     / \             / \
    //    4   5           2   3
    if (parent->left == this && grandpa->right == parent &&
        (grandpa->left == nullptr || grandpa->left->color == BLACK)) {
        // cerr << "Subcase 3\n";
        // record cnt and sum
        int gcnt = grandpa->rcnt;
        int scnt = grandpa->left ? grandpa->left->rcnt : 0;
        int p1cnt = parent->right ? parent->right->rcnt : 0;
        int k1cnt = this->left ? this->left->rcnt : 0;
        int k2cnt = this->right ? this->right->rcnt : 0;
        long long gsum = grandpa->rsum;
        long long ssum = grandpa->left ? grandpa->left->rsum : 0;
        long long p1sum = parent->right ? parent->right->rsum : 0;
        long long k1sum = this->left ? this->left->rsum : 0;
        long long k2sum = this->right ? this->right->rsum : 0;

        RBTreeNode<T>* p4 = this->left;
        RBTreeNode<T>* p5 = this->right;
        // reset parent to greatpa, must use oldparent for
        // P from here.
        this->parent = greatpa;
        if (greatpa != nullptr) {
            if (greatpa->left == grandpa) { greatpa->left = this; }
            else { greatpa->right = this; }
        }
        // must use oldparent for P because parent is greatpa now
        this->left = grandpa; grandpa->parent = this;
        this->right = oldparent; oldparent->parent = this;
        grandpa->right = p4; if (p4) p4->parent = grandpa;
        oldparent->left = p5; if (p5) p5->parent = oldparent;
        // color
        this->color = BLACK;
        grandpa->color = RED;
        // cnt and sum
        this->rcnt = gcnt;
        this->rsum = gsum;
        oldparent->rcnt = k2cnt + 1 + p1cnt;
        oldparent->rsum = k2sum + oldparent->key + p1sum;
        grandpa->rcnt = scnt + 1 + k1cnt;
        grandpa->rsum = ssum + grandpa->key + k1sum;
        return;
    }
    // Sub4: P(red), S(black), K(red), G(black)
    // Sub4' P(black), S(black), K(red), G(red)
    //     G                   P
    //    / \                 / \
    //   S   P        =>     G   K
    //  / \ / \             / \
    // 2  3 1  K           S  1
    //                    / \
    //                   2   3
    if (parent->right == this && grandpa->right == parent &&
        (grandpa->left == nullptr || grandpa->left->color == BLACK)) {
        // cerr << "Subcase 4\n";
        // record cnt and sum
        int gcnt = grandpa->rcnt;
        int p1cnt = (parent->left) ? parent->left->rcnt : 0;
        int p2cnt = this->rcnt;
        int scnt = (grandpa->left) ? grandpa->left->rcnt : 0;
        long long gsum = grandpa->rsum;
        long long p1sum = (parent->left) ? parent->left->rsum : 0;
        long long p2sum = this->rsum;
        long long ssum = (grandpa->left) ? grandpa->left->rsum : 0;

        parent->parent = greatpa;
        if (greatpa != nullptr) {
            if (greatpa->left == grandpa) { greatpa->left = parent; }
            else { greatpa->right = parent; }
        }
        RBTreeNode<T>* p1 = oldparent->left;
        parent->left = grandpa; grandpa->parent = parent;
        grandpa->right = p1; if (p1 != nullptr) p1->parent = grandpa;
        // color
        parent->color = BLACK;
        grandpa->color = RED;
        // cnt and sum
        parent->rcnt = gcnt;
        parent->rsum = gsum;
        grandpa->rcnt = scnt + 1 + p1cnt;
        grandpa->rsum = ssum + grandpa->key + p1sum;
        return;
    }
    // Sub5: G(black), P(red), S(red), K(red)
    // Sub5' G(red), P(black), S(black), K(red)
    // No restructure, just recolor, may need to recurse on G
    //     G                   G
    //    / \                 / \
    //   P   S        =>     P   S
    //  / \ / \             / \ / \
    // K  1 2  3           K  1 2  3
    // cerr << "Subcase 5\n";
    assert(grandpa->left != nullptr);
    assert(grandpa->right != nullptr);
    assert(grandpa->left->color == RED);
    assert(grandpa->right->color == RED);
    // recolor
    grandpa->left->color = BLACK;
    grandpa->right->color = BLACK;
    grandpa->color = RED;
    grandpa->Fixup();
    return;
}

template <typename T>
pair<int, long long>
RBTreeNode<T>::GetStats(const T& key) const {
  if (this->key == key) {
    int cnt = this->right ? this->right->rcnt : 0;
    long long sum = this->right ? this->right->rsum : 0;
    return make_pair(1+cnt, this->key + sum);
  } else if (this->key < key) {
    // we know key is in the tree
    assert(this->right != nullptr);
    return this->right->GetStats(key);
  } else {
    // we know key is in the tree
    assert(this->left != nullptr);
    int cnt = this->right ? this->right->rcnt : 0;
    long long sum = this->right ? this->right->rsum : 0;
    pair<int, long long> pans = this->left->GetStats(key);
    pans.first += 1 + cnt;
    pans.second += this->key + sum;
    return pans;
  }
}

template <typename T>
void RBTreeNode<T>::Print() const {
    cout << "(" << key << "," 
      << (color == RED ? "red" : "black")
      << "," << "cnt=" << rcnt
      << "," << "sum=" << rsum
      << "), parent(" << (parent ? parent->key : T{}) << ")"
      << endl;
    if (left) left->Print();
    if (right) right->Print();
}

int main() {
  int n; cin >> n;
  int a[100000+5];
  long long sum = 0;
  RBTree<int> tree;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    tree.Insert(a[i]);
    tree.Print();
    pair<int, long long> p = tree.GetStats(a[i]);
    // cout << "cnt=" << p.first << ", sum=" << p.second << endl;
    const int M = 1e9+7;
    sum += 1LL * (i+1 - p.first + 1) * p.second % M;
    sum %= M;
    cout << sum << endl;
  }
}

// No algorithm yet, but made RBTree keep cnt and sum.
