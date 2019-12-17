template<class Node, class Lazy>
class Segtree {
 public:
  Segtree(int _n) :
    n(_n),
    nodes(4*n),
    lazy(4*n) {
  }
  Node query(int l, int r) {
    return _query(l, r, 0, n, 1);
  }
  void update(int l, int r, const Lazy& v) {
    _update(l, r, v, 0, n, 1);
  }
 private:
  Node _query(int l, int r, int nl, int nr, int id) {
    if (l <= nl && nr <= r)
      return nodes[id];
    pushDown(id);
    int mid = (nl+nr)/2;
    if (r <= mid)
      return _query(l, r, nl, mid, id<<1);
    if (mid <= l)
      return _query(l, r, mid, nr, (id<<1)|1);
    return _query(l, r, nl, mid, id<<1).merge(
           _query(l, r, mid, nr, id<<1|1));
  }
  void _update(int l, int r, const Lazy& val, int nl, int nr, int id) {
    if (r <= nl || nr <= l)
      return;
    if (l <= nl && nr <= r) {
      nodes[id].update(val);
      lazy[id].update(val);
      return;
    }
    pushDown(id);
    int mid = (nl+nr)/2;
    _update(l, r, val, nl, mid, id<<1);
    _update(l, r, val, mid, nr, id<<1|1);
    nodes[id] = nodes[id<<1].merge(nodes[id<<1|1]);
  }
  void pushDown(int id) {
    nodes[id<<1].update(lazy[id]);
    lazy[id<<1].update(lazy[id]);
    nodes[id<<1|1].update(lazy[id]);
    lazy[id<<1|1].update(lazy[id]);
    lazy[id] = Lazy();
  }
  int n;
  vector<Node> nodes;
  vector<Lazy> lazy;
};

/*
struct Lazy {
  Lazy()
  void update(const Lazy& rhs)
};

struct Node {
  Node merge(const Node& rhs) const
  void update(const Lazy& lazy)
};
*/
