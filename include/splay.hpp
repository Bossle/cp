#pragma once
#include <memory>
#include <type_traits>
#include "memoize.hpp"

namespace libossle {

// This is not allocator-aware, to be more cache-friendly
template<class T>
class Splay {
 public:
  class iterator;
  Splay();
  Splay(T&&);
  iterator begin() const;
  iterator end() const;
  // TooSmall(const T&) should be bool,
  // typically [](const T& x){ return x < goal; }
  template<class TooSmall>
  iterator lower_bound(TooSmall) const;
  iterator insert(iterator, Splay&&);
  // split returns the elements to the left of the parameter
  Splay&& split(iterator);
  template<class Map, class Reduce>
  typename std::result_of<Map(const T&)>::type applyAssociative(Map, Reduce) const;
 private:
  struct Node;
  mutable std::unique_ptr<Node> data;
};

template<class T>
class Splay<T>::iterator {
 public:
  iterator(Node*);
  T& operator*() const;
  iterator& operator+=(int n);
  int index() const;
  friend Splay<T>;
 private:
  void splay() const;
  Node* data;
};

template<class T>
struct Splay<T>::Node {
  // The root node is the only with
  // no value, treeIfRoot set, and parent == NULL
  // It also has right == NULL, since it represents the end() iterator
  Node(Splay<T>*);
  Node(T&&, Node*);
  void rotateLeft() const;
  void rotateRight() const;
  void rotateUp() const;
  static int size(const Node*);
  // This is static to allow for memoization
  // TODO: move to impl
  template<class Map, class Reduce, class F>
  friend std::pair<bool, typename std::result_of<Map(const T&)>::type> memoize(F& f, const Node*, Map, Reduce, id_t);
  template<class Map, class Reduce>
  static typename std::result_of<Map(const T&)>::type applyAssociative(const Node* n, Map m, Reduce r, id_t=0) {
    MEMOIZE(applyAssociative, n, m, r, n->rangeId);
    auto ans = m(n->value);
    if (n->left != NULL)
      ans = r(applyAssociative(n->left.get(), m, r), ans);
    if (n->right != NULL)
      ans = r(ans, applyAssociative(n->right.get(), m, r));
    return ans;
  }
  // TODO: make a proper IDGenerator class
  using id_t = int;
  static id_t nextId;
  union {
    T value;
    mutable Splay<T>* treeIfRoot;
  };
  mutable std::unique_ptr<Node> left, right;
  mutable Node* parent;
  mutable id_t rangeId;
};

}  // namespace libossle

#include "splay_impl.hpp"

