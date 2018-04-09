#pragma once

template<type T>
class StandardIterator : public Splay<T>::iterator {
 public:
  using difference_type = int;
  using value_type = *Iterator;
  using pointer = value_type*;
  using reference = value_type&;
  using iterator_category = std::random_access_iterator_tag;

  int operator-(const iterator& rhs) { return index() - rhs.index(); }
  T* operator->() const { return &**this; }
  T& operator[](int n) const { return *(*this + n); }
  iterator& operator++() { return *this += 1; }
  iterator operator++(int) { auto it = *this; ++*this; return it; }
  iterator& operator--() { return *this -= 1; }
  iterator operator--(int) { auto it = *this; --*this; return it; }
  iterator& operator-=(int n) { return *this += -n; }
  iterator operator+(int n) const { auto it = *this; it += n; return it; }
  iterator operator-(int n) const { return *this + -n; }
  bool operator<(const iterator& rhs) const { return *this - rhs < 0; }
  bool operator>(const iterator& rhs) const { return *this - rhs > 0; }
  bool operator<=(const iterator& rhs) const { return *this - rhs <= 0; }
  bool operator>=(const iterator& rhs) const { return *this - rhs >= 0; }
}

template<class T>
StandardIterator<T> operator+(int n, const StandardIterator<T>& it) {
  return it + n;
}

