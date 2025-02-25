#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; i++)
#define pb push_back
#define ff first
#define ss second
#define ii pair<int, int>
#define vii vector<ii>
#define lli long long int
#define vi vector<lli>
#define fast_io                                                                \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);                                                                  \
  cout.tie(0);
using namespace std;
ostream &operator<<(ostream &os, const vector<int> &v) {
  for (auto const &i : v) {
    os << i << " ";
  }
  os << endl;
  return os;
}
const lli mod = (1e9) + 7;
const int N = 1e4 + 1;
struct st {
  st *left, *right;
  int l, r, mid;
  lli val, lazy;
 
  st(int l, int r, vi &v) : l(l), r(r), lazy(0) {
    if (l != r) {
      mid = (l + r) / 2;
      left = new st(l, mid, v);
      right = new st(mid + 1, r, v);
      val = left->val + right->val;
    } else
      val = v[l - 1];
  }
 
  void propagate() {
    if (l == r || lazy == 0)
      return;
    left->lazy += lazy;
    right->lazy += lazy;
 
    int hl = left->r - left->l + 1;
    int hr = right->r - right->l + 1;
    left->val += hl * lazy;
    right->val += hr * lazy;
    lazy = 0;
  }
 
  void update(int a, int b, lli v) {
    // no sirve
    if (a > r || b < l)
      return;
    if (a <= l && r <= b){
      int h = r - l + 1;
      lazy += v;
      val += (h * v);
      return;
    }
    left->update(a, b, v);
    right->update(a, b, v);
    val = left->val + right->val;
  }
 
  lli get(int a, int b) {
    propagate();
    // sirve
    if (a <= l && r <= b)
      return val;
    // no sirve
    if (b < l || a > r)
      return 0;
    return left->get(a, b) + right->get(a, b);
  }
};
int main() {
  fast_io;
  int n, q;
  cin >> n >> q;
  vi nums(n);
  REP(i, n) cin >> nums[i];
  st tree(1, n, nums);
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int a, b, u;
      cin >> a >> b >> u;
      tree.update(a, b, u);
    } else {
      int k;
      cin >> k;
      cout << tree.get(k, k) << endl;
    }
  }
  return 0;
}
