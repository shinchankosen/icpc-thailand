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

template<int MOD> struct Modint {
    long long val;
    constexpr Modint(long long v = 0) noexcept : val(v % MOD) { if (val < 0) val += MOD; }
    constexpr int mod() const { return MOD; }
    constexpr long long value() const { return val; }
    constexpr Modint operator - () const noexcept { return val ? MOD - val : 0; }
    constexpr Modint operator + (const Modint& r) const noexcept { return Modint(*this) += r; }
    constexpr Modint operator - (const Modint& r) const noexcept { return Modint(*this) -= r; }
    constexpr Modint operator * (const Modint& r) const noexcept { return Modint(*this) *= r; }
    constexpr Modint operator / (const Modint& r) const noexcept { return Modint(*this) /= r; }
    constexpr Modint& operator += (const Modint& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Modint& operator -= (const Modint& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Modint& operator *= (const Modint& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Modint& operator /= (const Modint& r) noexcept {
        long long a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator == (const Modint& r) const noexcept { return this->val == r.val; }
    constexpr bool operator != (const Modint& r) const noexcept { return this->val != r.val; }
    friend constexpr istream& operator >> (istream& is, Modint<MOD>& x) noexcept {
        is >> x.val;
        x.val %= MOD;
        if (x.val < 0) x.val += MOD;
        return is;
    }
    friend constexpr ostream& operator << (ostream& os, const Modint<MOD>& x) noexcept {
        return os << x.val;
    }
    constexpr Modint<MOD> pow(long long n) noexcept {
        if (n == 0) return 1;
        if (n < 0) return this->pow(-n).inv();
        Modint<MOD> ret = pow(n >> 1);
        ret *= ret;
        if (n & 1) ret *= *this;
        return ret;
    }
    constexpr Modint<MOD> inv() const noexcept {
        long long a = this->val, b = MOD, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b, swap(a, b);
            u -= t * v, swap(u, v);
        }
        return Modint<MOD>(u);
    }
};

const int MOD = MOD7;
using mint = Modint<MOD>;

vector<int> ps = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int psz = 15;

using ar = array<int, psz>;
ar base;

struct UnionFind {
    vector<int> par;
    UnionFind(int n) :par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    bool connect(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    int size(int x) {
        return -par[root(x)];
    }
};

void solve() {
    int n; cin >> n;
    vector<mint> p(n);
    rep(i, n) {
        string s; cin >> s;
        int id = -1;
        int sz = s.size();
        rep(j, sz) {
            if(s[j] == '.') id = j;
        }
        if(id == -1) {
            p[i] = stoi(s);
        } else {
            int num = (s[0] - '0');
            for(int j = id + 1; j < sz; j ++) {
                num *= 10;
                num += s[j] - '0';
            }
            p[i] = mint(num) / mint(10).pow(sz - id - 1);
        }
    }
    map<int, mint> mp;
    vector<mint> p0;
    for(int i = 1; i <= n; i ++) {
        int sum = 0;
        rep(j, psz) {
            if(i % ps[j] == 0) sum |= 1 << j;
        }
        if(sum == 0) {
            p0.pb(p[i - 1]);
            continue;
        }
        if(mp.count(sum)) {
            mp[sum] = mint(1) - (mint(1) - mp[sum]) * (mint(1) - p[i - 1]);
        } else {
            mp[sum] = p[i - 1];
        }
    }


    vector<pair<int, mint>> vec;
    vector<vector<pair<int, mint>>> task(16);
    for(auto [x, y] : mp) {
         {
            int id = 0;
            rep(i, psz) if(x >> i & 1) id = i;
            if(id >= 6) {
                task[id].pb(x, y);
            } else {
                vec.pb(x, y);
            }
        }
    }
    map<ar, mint> dp1;
    dp1[base] = mint(1);

    auto ch1 = [&](ar v, int bit) -> ar {
        ar arr;
        fill(all(arr), -1);
        UnionFind uf(psz);
        rep(i, psz) {
            if(v[i] == 0) continue;
            if(arr[v[i]] != -1) uf.connect(arr[v[i]], i);
            arr[v[i]] = i; 
        }
        int p = -1;
        rep(i, psz) if(bit >> i & 1) {
            if(p != -1) uf.connect(i, p);
            p = i;
        }
        rep(i, psz) if(v[i]) bit |= 1 << i;
        ar c = base;
        int sz = 0;
        rep(i, psz) {
            if(bit >> i & 1) {
                if(c[uf.root(i)]) {
                    v[i] = c[uf.root(i)];
                } else {
                    v[i] = c[uf.root(i)] = ++sz;
                }
            }
        }
        return v;
    };

    for(auto [bit, val] : vec) {
        map<ar, mint> nx;
        for(auto [v, val2] : dp1) {
            nx[ch1(v, bit)] += val2 * val;
            nx[v] += val2 * (mint(1) - val);
        }
        dp1 = move(nx);
    }
    

    using P = pair<array<int, 3>, int>; // 下位3bit, 連結成分数
    map<P, mint> dp2;

    for(auto [v, val] : dp1) {
        array<int, 3> bit;
    
        int ma = 0;
        rep(i, 3) {
            bit[i] = v[i];
        }
        rep(i, psz) chmax(ma, v[i]);
        dp2[make_pair(bit, ma)] += val;
    }

    auto ch2 = [&](P tmp, int bit) -> P {
        assert(bit < 8);
        auto [state, cnt] = tmp;
        if(bit == 0) {
            cnt ++;
            return make_pair(state, cnt);
        }

        array<int, 4> arr;
        fill(all(arr), -1);
        UnionFind uf(3);
        rep(i, 3) {
            if(state[i] == 0) continue;
            if(arr[state[i]] != -1) uf.connect(arr[state[i]], i);
            arr[state[i]] = i; 
        }
        int p = -1;
        rep(i, 3) if(bit >> i & 1) {
            if(p != -1) uf.connect(i, p);
            p = i;
        }
        rep(i, 3) if(state[i]) bit |= 1 << i;
        array<int, 3> c;
        fill(all(c), 0);
        int sz = 0;
        int ma = 0;
        rep(i, 3) chmax(ma, state[i]);
        rep(i, 3) {
            if(bit >> i & 1) {
                if(c[uf.root(i)]) {
                    state[i] = c[uf.root(i)];
                } else {
                    state[i] = c[uf.root(i)] = ++sz;
                }
            }
        }
        int m2 = 0;
        rep(i, 3) chmax(m2, state[i]);
        cnt += m2 - ma;
        return make_pair(state, cnt);
    };
    for(int j = 6; j < psz; j ++) {
        int sz = task[j].size();
        map<int, mint> tmp;
        rep(bit, 1 << sz) {
            mint pr = mint(1);
            int sum = 0;
            rep(i, sz) {
                if(bit >> i & 1) {
                    sum |= task[j][i].first;
                    pr *= task[j][i].second;
                } else {
                    pr *= mint(1) - task[j][i].second;
                }
            }
            tmp[sum] += pr;
        }
        map<P, mint> nx;
        for(auto [pa, val] : dp2) {
            for(auto [bit, val2] : tmp) {
                if(bit == 0) {
                    nx[pa] += val * val2;
                    continue;
                }
                nx[ch2(pa, bit ^ (1 << j))] += val * val2;
            }
        }
        dp2 = move(nx);
    }
    mint ans = 0;
    for(auto [tmp, val] : dp2) {
        auto [state, cnt] = tmp;
        ans += mint(cnt) * val;
    }
    foa(e, p0) {
        ans += e;
    }
    ans *= mint(100).pow(n);
    cout << ans << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    rep(i, psz) base[i] = 0;

    int testcase = 1; 
    cin >> testcase;
    while(testcase --) solve();

    return 0;
}
