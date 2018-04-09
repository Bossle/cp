#include "memoize.hpp"

namespace libossle {

// Splay

template<class T>
Splay<T>::Splay() :
  data(new Node(this)) {
}

template<class T>
Splay<T>::Splay(T&& elem) :
  Splay() {
  data->left.reset(new Node(std::move(elem), data->left.get()));
}

template<class T>
typename Splay<T>::iterator Splay<T>::begin() const {
  return this->lower_bound([](const T&){ return false; });
}

template<class T>
typename Splay<T>::iterator Splay<T>::end() const {
  return iterator(data);
}

template<class T> template<class TooSmall>
typename Splay<T>::iterator Splay<T>::lower_bound(TooSmall tooSmall) const {
  Node* candidate = data.get();
  Node* probe = data.get();
  while (probe != NULL) {
    if (tooSmall(probe->value)) {
      probe = probe->right.get();
    } else {
      candidate = probe;
      probe = probe->left.get();
    }
  }
  return iterator(candidate);
}

template<class T>
typename Splay<T>::iterator Splay<T>::insert(iterator next, Splay<T>&& tree) {
  Node* parent = next.data;
  std::unique_ptr<Node>* insertionPoint = &parent->left;
  while (*insertionPoint != NULL) {
    parent = insertionPoint->get();
    insertionPoint = &parent->right;
  }
  swap(*insertionPoint, tree.data->left);
  std::unique_ptr<Node>& inserted = *insertionPoint;
  inserted->parent = parent;
  return iterator(inserted.get());
}

template<class T>
Splay<T>&& Splay<T>::split(iterator next) {
  next.splay();
  return Splay{next.data->left.release()};
}

template<class T> template<class Map, class Reduce>
typename std::result_of<Map(const T&)>::type Splay<T>::applyAssociative(Map m, Reduce r) const {
  return nodeApplyAssociative(data->left, m, r);
}

// iterator

template<class T>
Splay<T>::iterator::iterator(Node* n) :
  data(n) {
  splay();
}

template<class T>
T& Splay<T>::iterator::operator*() const {
  splay();
  return data->value;
}

template<class T>
typename Splay<T>::iterator& Splay<T>::iterator::operator+=(int n) {
  splay();
  while (n != 0) {
    if (n > 0) {
      data = data->right.get();
      n -= Node::size(data->left.get()) + 1;
    } else {
      data = data->left.get();
      n += Node::size(data->right.get()) + 1;
    }
  }
  splay();
  return *this;
}

template<class T>
int Splay<T>::iterator::index() const {
  splay();
  return Node::size(data->left.get());
}

template<class T>
void Splay<T>::iterator::splay() const {
  if (data->parent == NULL)
    return;
  while (data->parent->parent != NULL) {
    Node* parent = data->parent;
    Node* grandparent = parent->parent;
    if (grandparent->parent == NULL) {
      data->rotateUp();
    } else if ((parent->left.get() == data) == (grandparent->left.get() == parent)) {
      parent->rotateUp();
      data->rotateUp();
    } else {
      data->rotateUp();
      data->rotateUp();
    }
  }
}

// Node

template<class T>
Splay<T>::Node::Node(Splay<T>* tree) :
  treeIfRoot(tree),
  rangeId(nextId++) {
}

template<class T>
Splay<T>::Node::Node(T&& v, Node* p) :
  value(v),
  parent(p),
  rangeId(nextId++) {
}

template<class T>
void Splay<T>::Node::rotateLeft() const {
  std::unique_ptr<Node>& ptrToRoot = (treeIfRoot == NULL ?
    (parent->left.get() == this ? parent->left : /*assert(parent->right == this),*/ parent->right) :
    treeIfRoot->data);
  swap(ptrToRoot, right);
  Node& newRoot = *ptrToRoot;
  std::swap(right, newRoot.left);
  std::swap(parent, newRoot.parent);
  std::swap(treeIfRoot, newRoot.treeIfRoot);
  std::swap(rangeId, newRoot.rangeId);
  parent = &newRoot;
  rangeId = nextId++;
}

template<class T>
void Splay<T>::Node::rotateRight() const {
  std::unique_ptr<Node>& ptrToRoot = (treeIfRoot == NULL ?
    (parent->left.get() == this ? parent->left : /*assert(parent->right == this),*/ parent->right) :
    treeIfRoot->data);
  swap(ptrToRoot, left);
  Node& newRoot = *ptrToRoot;
  std::swap(left, newRoot.right);
  std::swap(parent, newRoot.parent);
  std::swap(treeIfRoot, newRoot.treeIfRoot);
  std::swap(rangeId, newRoot.rangeId);
  parent = &newRoot;
  rangeId = nextId++;
}

template<class T>
void Splay<T>::Node::rotateUp() const {
  if (parent->left.get() == this) {
    parent->rotateRight();
  } else {
    //assert(parent->right.get() == this);
    parent->rotateLeft();
  }
}

template<class T>
int Splay<T>::Node::size(const Node* n) {
  if (n == NULL)
    return 0;
  static auto map = [](const T&){ return 1; };
  static auto reduce = [](int a, int b){ return a+b; };
  return applyAssociative(n, map, reduce);
}

/*
template<class T> template<class Map, class Reduce>
typename std::result_of<Map(const T&)>::type Splay<T>::Node::applyAssociative(const Node* n, Map m, Reduce r, typename Splay<T>::Node::id_t) const {
  MEMOIZE(applyAssociative, n, m, r, rangeId);
  auto ans = m(n->value);
  if (n->left != NULL)
    ans = r(applyAssociative(n->left, m, r), ans);
  if (n->right != NULL)
    ans = r(ans, applyAssociative(n->right, m, r));
  return ans;
}
*/

template<class T>
typename Splay<T>::Node::id_t Splay<T>::Node::nextId = 0;

}  // namespace libossle

