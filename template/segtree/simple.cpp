template<class Node>
class SimpleSegtree {
 public:
  SimpleSegtree(int _n) :
    n(_n),
    nodes(4*n) {
  }
  Node query(int l, int r) {
    return _query(l, r, 0, n, 1);
  }
  void update(int x, Node v) {
    _update(x, v, 0, n, 1);
  }
 private:
  Node _query(int l, int r, int nl, int nr, int id) {
    if (l <= nl && nr <= r)
      return nodes[id];
    int mid = (nl+nr)/2;
    if (r <= mid)
      return _query(l, r, nl, mid, id<<1);
    if (mid <= l)
      return _query(l, r, mid, nr, (id<<1)|1);
    return _query(l, r, nl, mid, id<<1).merge(
           _query(l, r, mid, nr, id<<1|1));
  }
  void _update(int x, Node val, int nl, int nr, int id) {
    if (nr-nl == 1) {
      nodes[id] = val;
      return;
    }
    int mid = (nl+nr)/2;
    if (x < mid)
      _update(x, val, nl, mid, id<<1);
    else
      _update(x, val, mid, nr, id<<1|1);
    nodes[id] = nodes[id<<1].merge(nodes[id<<1|1]);
  }
  int n;
  vector<Node> nodes;
};

/*
struct Node {
  Node merge(const Node& rhs) const
};
*/
