#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(),(v).end()
#define pb emplace_back
#define rep(i, n) for(int i=0;i<(n);i++)
#define foa(e, v) for(auto& e : v)
#define dout(a) cout<<fixed<<setprecision(10)<<a<<'\n';
#define Cout(a) cout<<a<<'\n';

using ll = long long;
using ld = long double;
using Int = __int128;
template <class T> using pqr = priority_queue<T, vector<T>, greater<T>>;

template <typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
template <typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}
template <typename T> inline T back(std::set<T> &s) {
    return *s.rbegin();
}
template <typename T> inline T back(std::multiset<T> &s) {
    return *s.rbegin();
}
template <typename T> inline T pop_back(std::set<T> &s) {
    auto it = prev(s.end());
    T val = *it;
    s.erase(it); 
    return val;
}
template <typename T> inline T pop_back(std::multiset<T> &s) {
    auto it = prev(s.end());
    T val = *it;
    s.erase(it); 
    return val;
}

const int dy[8] = {-1, 0, 0, 1, 1, -1, 1, -1};
const int dx[8] = {0, -1, 1, 0, -1, -1, 1, 1};

const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (3LL << 59);
const int inf = 1 << 30;
const char br = '\n';

// base: bafcf8
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

Int cross(Int x1, Int y1, Int x2, Int y2) {
    return x1 * y2 - x2 * y1;
}

const Int MOD = 10000000019;
Int modinv(Int a) {
    Int b = MOD, u = 1, v = 0;
    while (b) {
        Int t = a / b;
        a -= t * b; std::swap(a, b);
        u -= t * v; std::swap(u, v);
    }
    u %= MOD; 
    if (u < 0) u += MOD;
    return u;
}

const Int zero = Int(0);

struct S {
    Int xsum, ysum, bsum, xone, yone, bone, cnt;
};

S op(S a, S b) {
    return S{a.xsum + b.xsum + b.cnt * a.xone, a.ysum + b.ysum + b.cnt * a.yone, a.bsum + b.bsum + b.cnt * a.bone, a.xone + b.xone, a.yone + b.yone, a.bone + b.bone, a.cnt + b.cnt};
}

S e() {
    return S{zero, zero, zero, zero, zero, zero, zero};
}

void solve() {
    ll n; cin >> n;
    vector<Int> x(n), y(n);
    rep(i, n) {
        ll a, b; cin >> a >> b;
        x[i] = a;
        y[i] = b;
    }

    Int xp, yp, xq, yq;
    {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        xp = x1;
        yp = y1;
        xq = x2;
        yq = y2;
    }
    rep(i, n + n) x.pb(x[i]);
    rep(i, n + n) y.pb(y[i]);
    Int cnt = 0, ans = 0;
    { // clockwise
        vector<S> base(n * 2);
        rep(i, n * 2) {
            Int X = y[i + 1] - y[i];
            Int Y = x[i] - x[i + 1];
            Int B = -cross(x[i], y[i], x[i + 1], y[i + 1]);
            base[i] = S{X, Y, B, X, Y, B, Int(1)};
        }
        segtree<S, op, e> seg(base);

        Int allarea2 = 0;
        {
            auto [_, _1, _2, X, Y, B, __] = seg.prod(1, n);
            allarea2 = X * x[0] + Y * y[0] + B;
        }
        // cout << ll(allarea2) << endl;
        int j1 = 0, j2 = 0, j3 = 0;
        
        rep(i, n) {
            Int num = 0;
            chmax(j1, i + 1);
            while(cross(xp - x[i], yp - y[i], x[j1 + 1] - x[i], y[j1 + 1] - y[i]) >= 0 and cross(xq - x[i], yq - y[i], x[j1 + 1] - x[i], y[j1 + 1] - y[i]) >= 0) j1 ++;
            chmax(j2, i + 1);
            while(1) {
                auto [_, _1, _2, X, Y, B, __] = seg.prod(i + 1, j2 + 1);
                Int area = X * x[i] + Y * y[i] + B;
                if(area * 2 <= allarea2) j2 ++;
                else {
                    // cout << ll(area) << endl;
                    break;
                }
            }
            
            chmax(j3, j1);
            while(cross(xp - x[i], yp - y[i], x[j3] - x[i], y[j3] - y[i]) > 0 or cross(xq - x[i], yq - y[i], x[j3] - x[i], y[j3] - y[i]) > 0) j3 ++;
            if(j1 >= j3 - 1) continue;
            if(j2 <= j1) {
                auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j3 - 1);
                auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j1);
                xsum1 %= MOD;
                ysum1 %= MOD;
                xsum2 %= MOD;
                ysum2 %= MOD;

                Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                
                num += area1 - area2;
            } else if(j2 >= j3) {
                auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j3 - 1);
                auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j1);
                xsum1 %= MOD;
                ysum1 %= MOD;
                xsum2 %= MOD;
                ysum2 %= MOD;
                Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                num -= area1 - area2;
            } else {
                {
                    auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j2);
                    auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j1);
                    xsum1 %= MOD;
                    ysum1 %= MOD;
                    xsum2 %= MOD;
                    ysum2 %= MOD;
                    Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                    Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                    num -= area1 - area2;
                }{
                    auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j3 - 1);
                    auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j2);
                    xsum1 %= MOD;
                    ysum1 %= MOD;
                    xsum2 %= MOD;
                    ysum2 %= MOD;
                    Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                    Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                    num += area1 - area2;
                }
            }
            // cout << j1 << " " << j2 << " " << j3 << " " << ll(num) << endl;
            ans += num;
            ans %= MOD;
            cnt += Int(max(j3 - j1 - 1, 0));
        }
        // cout << ll(cnt) << " " << ll(ans) << endl;
        reverse(all(x));
        reverse(all(y));
    }{ // clockwise
        vector<S> base(n * 2);
        rep(i, n * 2) {
            Int X = y[i + 1] - y[i];
            Int Y = x[i] - x[i + 1];
            Int B = -cross(x[i], y[i], x[i + 1], y[i + 1]);
            base[i] = S{X, Y, B, X, Y, B, Int(1)};
        }
        segtree<S, op, e> seg(base);

        Int allarea2 = 0;
        {
            auto [_, _1, _2, X, Y, B, __] = seg.prod(1, n);
            allarea2 = X * x[0] + Y * y[0] + B;
            allarea2 = -allarea2;
        }
        // cout << ll(allarea2) << endl;
        int j1 = 0, j2 = 0, j3 = 0;
        
        rep(i, n) {
            Int num = 0;
            chmax(j1, i + 1);
            while(cross(xp - x[i], yp - y[i], x[j1 + 1] - x[i], y[j1 + 1] - y[i]) <= 0 and cross(xq - x[i], yq - y[i], x[j1 + 1] - x[i], y[j1 + 1] - y[i]) <= 0) j1 ++;
            chmax(j2, i + 1);
            while(1) {
                auto [_, _1, _2, X, Y, B, __] = seg.prod(i + 1, j2 + 1);
                Int area = X * x[i] + Y * y[i] + B;
                area = -area;
                if(area * 2 < allarea2) j2 ++;
                else {
                    // cout << ll(area) << endl;
                    break;
                }
            }
            chmax(j3, j1);
            while(cross(xp - x[i], yp - y[i], x[j3] - x[i], y[j3] - y[i]) < 0 or cross(xq - x[i], yq - y[i], x[j3] - x[i], y[j3] - y[i]) < 0) j3 ++;
            if(j1 >= j3 - 1) continue;
            if(j2 <= j1) {
                auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j3 - 1);
                auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j1);
                xsum1 %= MOD;
                ysum1 %= MOD;
                xsum2 %= MOD;
                ysum2 %= MOD;

                Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                
                num -= area1 - area2;
            } else if(j2 >= j3) {
                auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j3 - 1);
                auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j1);
                xsum1 %= MOD;
                ysum1 %= MOD;
                xsum2 %= MOD;
                ysum2 %= MOD;
                Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                num += area1 - area2;
            } else {
                {
                    auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j2);
                    auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j1);
                    xsum1 %= MOD;
                    ysum1 %= MOD;
                    xsum2 %= MOD;
                    ysum2 %= MOD;
                    Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                    Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                    num += area1 - area2;
                }{
                    auto [xsum1, ysum1, bsum1, xone1, yone1, bone1, cnt1] = seg.prod(i + 1, j3 - 1);
                    auto [xsum2, ysum2, bsum2, xone2, yone2, bone2, cnt2] = seg.prod(i + 1, j2);
                    xsum1 %= MOD;
                    ysum1 %= MOD;
                    xsum2 %= MOD;
                    ysum2 %= MOD;
                    Int area1 = xsum1 * x[i] + ysum1 * y[i] + bsum1;
                    Int area2 = xsum2 * x[i] + ysum2 * y[i] + bsum2;
                    num -= area1 - area2;
                }
            }
            // cout << j1 << " " << j2 << " " << j3 << " " << ll(num) << endl;
            ans += num;
            ans %= MOD;
        }
        // cout << ll(ans) << endl;
        reverse(all(x));
        reverse(all(y));
    }
    if(cnt == zero) {
        cout << -1 << endl;
        return ;
    }
    cnt *= 2;
    cnt %= MOD;
    cnt = modinv(cnt);
    ans *= cnt;
    ans %= MOD;
    if(ans < zero) ans += MOD;
    cout << ll(ans) << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int testcase = 1; 
    // cin >> testcase;
    while(testcase --) solve();

    return 0;
}
