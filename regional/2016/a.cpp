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

template<class S, S (*op)(S, S), S (*e)()> struct segtree {
    public:
    explicit segtree(int n) : segtree(vector<S>(n, e())) {}
    explicit segtree(const vector<S>& v) : _n(int(v.size())) {
        size = 1;
        while(size < _n) size *= 2;
        log = __builtin_ctz(size);
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
    }

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
    }  

    private:
    int _n, size, log;
    vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

ll n, m;
const ll th = 250;

struct S {
    ll ans, sz;
    array<ll, 250> sum;
};

S op(S a, S b) {
    ll num = a.sz / m;
    ll r = a.sz - num * m;
    r = (m - r);
    a.ans += b.ans;
    rep(i, r) {
        a.ans += b.sum[i] * num;
    }
    for(int i = r; i < m; i ++) {
        a.ans += b.sum[i] * (num + 1);
    }
    a.sz += b.sz;
    r = (m - r);
    rep(i, m) {
        int nx = (i + r);
        if(nx >= m) nx -= m;
        a.sum[nx] += b.sum[i]; 
    }
    return a;
}

array<ll, 250> E;
S e() {
    return S{0LL, 0LL, E};
}

void solve0() { 
    // m <= th

    // 降順に座圧
    // クエリ先読み、座圧したらセグ木に乗る
    // mod mごとの和を持つ？
    vector<ll> a(n);
    rep(i, n) cin >> a[i];
    map<pair<ll, ll>, ll> mp;
    int sz = 0;
    rep(i, n) {
        mp[{a[i], i}] ++;
    }
    ll q; cin >> q;
    vector<ll> X(q), Y(q);
    rep(i, q) {
        cin >> X[i] >> Y[i];
        X[i] --;
        mp[{Y[i], X[i]}] ++;
    }
    
    for(auto [x, y] : mp) {
        mp[x] = sz ++;
    }
    {
        int ss = 0;
        for(auto [x, y] : mp) {
            mp[x] = sz - ss - 1;
            ss ++;
        }
    }

    segtree<S, op, e> seg(sz);
    array<ll, 250> base;
    rep(i, 250) base[i] = 0;

    rep(i, n) {
        base[0] = a[i];
        seg.set(mp[{a[i], i}], S{a[i], 1LL, base});
    }
    rep(_, q) {
        ll x = X[_];
        ll y = Y[_];

        seg.set(mp[{a[x], x}], e());
        a[x] = y;
        base[0] = y;
        seg.set(mp[{a[x], x}], S{a[x], 1LL, base});
        cout << seg.all_prod().ans << '\n';
    } 
}
void solve1() {
    vector<ll> a(n);
    rep(i, n) {
        cin >> a[i];
    }
    vector<ll> sum(th);
    vector<multiset<ll>> ms(th);

    auto b = a;
    sort(all(b));
    reverse(all(b));
    rep(i, n) {
        int num = i / m;
        ms[num].insert(b[i]);
        sum[num] += b[i];
    }
    int q; cin >> q;
    rep(_, q) {
        ll x, y; cin >> x >> y;
        x --;
        int id = -1;
        rep(i, th) {
            if(*ms[i].begin() <= a[x]) {
                id = i;
                break;
            }
        }
        sum[id] -= a[x];
        ms[id].erase(ms[id].find(a[x]));
        bool flag = (a[x] < y);
        a[x] = y;
        if(flag) {
            while(id > 0) {
                if(*ms[id - 1].begin() >= y) break;
                else {
                    ll val = *ms[id - 1].begin();
                    sum[id] += val;
                    sum[id - 1] -= val;
                    ms[id].insert(val);
                    ms[id - 1].erase(ms[id - 1].begin());
                    id --;
                }
            }
        } else {
            while(1) {
                if(ms[id + 1].empty() or back(ms[id + 1]) <= y) break;
                else {
                    ll val = back(ms[id + 1]);
                    sum[id] += val;
                    sum[id + 1] -= val;
                    ms[id].insert(val);
                    ms[id + 1].erase(prev(ms[id + 1].end()));
                    id ++;
                }
            }
        }
        ms[id].insert(y);
        sum[id] += y;
        ll ans = 0;
        rep(i, th) {
            if(sum[i] == 0) break;
            ans += sum[i] * (i + 1);
        }
        cout << ans << '\n';
    }
}

void solve(int t) {
    cout << "Case " << t << ":\n";
    cin >> n >> m;
    
    if(m <= th) {
        solve0();
    } else {
        solve1();
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    rep(i, 250) E[i] = 0;
    int t; cin >> t;
    rep(i, t) solve(i + 1);

    return 0;
}
