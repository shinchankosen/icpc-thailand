#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < (n); i ++)
#define all(a) (a).begin(), (a).end()

unsigned int bit_ceil(unsigned int n) {
   unsigned int x = 1;
   while(x < (unsigned int)(n)) x *= 2;
   return x;
}
int countr_zero(unsigned int n) { return __builtin_ctz(n); }
constexpr int countr_zero_constexpr(unsigned int n) {
   int x = 0;
   while(!(n & (1 << x))) x++;
   return x;
}
template<class S, S (*op)(S, S), S (*e)()> struct segtree {
   public:
   segtree() : segtree(0) {}
   explicit segtree(int n) : segtree(vector<S>(n, e())) {}
   explicit segtree(const vector<S>& v) : _n(int(v.size())) {
      size = (int)bit_ceil((unsigned int)(_n));
      log = countr_zero((unsigned int)size);
      d = vector<S>(2 * size, e());
      for(int i = 0; i < _n; i++) d[size + i] = v[i];
      for(int i = size - 1; i >= 1; i--) { update(i); }
   }

   void set(int p, S x) {
      p += size;
      d[p] = x;
      for(int i = 1; i <= log; i++) update(p >> i);
   }

   S get(int p) const { return d[p + size]; }

   S prod(int l, int r) const {
      S sml = e(), smr = e();
      l += size;
      r += size;

      while(l < r) {
         if(l & 1) sml = op(sml, d[l++]);
         if(r & 1) smr = op(d[--r], smr);
         l >>= 1;
         r >>= 1;
      }
      return op(sml, smr);
   }

   S all_prod() const { return d[1]; }

   template<class F> int max_right(int l, F f) {
      if(l == _n) return _n;
      l += size;
      S sm = e();
      do {
         while(l % 2 == 0) l >>= 1;
         if(!f(op(sm, d[l]))) {
            while(l < size) {
               l = (2 * l);
               if(f(op(sm, d[l]))) {
                  sm = op(sm, d[l]);
                  l++;
               }
            }
            return l - size;
         }
         sm = op(sm, d[l]);
         l++;
      } while((l & -l) != l);
      return _n;
   }  // faa03f

   template<class F> int min_left(int r, F f) {
      if(r == 0) return 0;
      r += size;
      S sm = e();
      do {
         r--;
         while(r > 1 && (r % 2)) r >>= 1;
         if(!f(op(d[r], sm))) {
            while(r < size) {
               r = (2 * r + 1);
               if(f(op(d[r], sm))) {
                  sm = op(d[r], sm);
                  r--;
               }
            }
            return r + 1 - size;
         }
         sm = op(d[r], sm);
      } while((r & -r) != r);
      return 0;
   }  // efa466

   private:
   int _n, size, log;
   vector<S> d;

   void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

using S = pair<int, int>;

S op(S a, S b) {
    return max(a, b);
}

S e() {
    return {-1, -1};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    vector<S> base(n);
    rep(i, n) base[i] = {a[i], i};


    vector<vector<int>> vec(n + 1, vector(1, -1));
    rep(i, n) {
        vec[a[i]].push_back(i);
    }
    rep(i, n + 1) vec[i].push_back(n);
    segtree<S, op, e> seg(base);

    vector<vector<int>> v(n);
    int root = -1;
    vector<int> L(n), R(n);
    auto dfs = [&](auto &&dfs, int p, int le, int ri) -> void {
        if(le >= ri) return; 
        int nx = seg.prod(le, ri).second;
        if(p == -1) root = nx;
        else v[p].push_back(nx);
        L[nx] = le;
        R[nx] = ri;
        dfs(dfs, nx, le, nx);
        dfs(dfs, nx, nx + 1, ri);
    };
    dfs(dfs, -1, 0, n);

    // vector<int> height(n, 0);
    vector<int> depth(n, 0);
    vector<S> base1(n);
    rep(i, n) base1[i] = {0, i};
    segtree<S, op, e> segh(base1);
    auto f = [&](auto &&f, int now) -> void {
        for(int to : v[now]) {
            depth[to] = depth[now] + (a[now] > a[to] ? 1 : 0);
            f(f, to);
            auto [val, id] = op(segh.prod(L[now], now), segh.prod(now + 1, R[now]));
            // cout << now << " " << L[now] << " " << R[now] << " " <<  val << endl;
            if(a[id] < a[now]) val ++;
            // cout << now << " " << val << endl;
            segh.set(now, make_pair(val, now));
        }
    };
    f(f, root);

    // rep(i, n) cout << height[i] << " ";
    // cout << '\n';

    

    rep(_, q) {
        int x, y; cin >> x >> y;
        x --;
        y --;
        if(y < 0) {
            int id = lower_bound(all(vec[a[x]]), x) - vec[a[x]].begin();
            int le = vec[a[x]][id - 1] + 1;
            int ri = vec[a[x]][id + 1] - 1;
            // cout << le << " " << ri << '\n';
            le = max(le, L[x]);
            ri = min(ri, R[x] - 1);
            // for(int e : v[x]) {
            //     if(e < x) le = max(le, e);
            //     if(e > x) ri = min(ri, e);
            // }
            // cout << le << " " << ri << '\n';
            le = segh.prod(le, x).first;
            ri = segh.prod(x + 1, ri + 1).first;
            cout << max({le + 1, ri + 1, 0}) << '\n';
        } else {
            int num = seg.prod(min(x, y) + 1, max(x, y)).first;
            if(num >= max(a[x], a[y])) {
                cout << 0 << '\n';
            } else {
                cout << abs(depth[x] - depth[y]) << '\n';
            }
        }
    }
}
