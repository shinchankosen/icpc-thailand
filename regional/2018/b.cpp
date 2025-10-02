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

namespace comb {
    vector<mint> fac, finv, inv;
}

void cominit(int n) {
    if(!comb::fac.empty()) return;
    n = max(n + 1, 3);
    comb::fac.resize(n);
    comb::finv.resize(n);
    comb::inv.resize(n);
    comb::fac[0] = 1;
    for(int i = 1; i < n; i ++) {
        comb::fac[i] = comb::fac[i - 1] * i;
    }
    comb::finv[n - 1] = comb::fac[n - 1].inv();
    for(int i = n - 2; i >= 0; i --) {
        comb::finv[i] = comb::finv[i + 1] * (i + 1);
        comb::inv[i + 1] = comb::finv[i + 1] * comb::fac[i];
    }
}

mint com(int n, int k) {
    if(n < k || n < 0 || k < 0) return 0;
    return comb::fac[n] * comb::finv[k] * comb::finv[n - k];
}

mint k4memo[6][9];

int t = 0;
void Out(mint val) {
    cout << "Case " << t << ": " << val <<  endl;
}
void solve() {
    cominit(1000003);
    ll h, w, k;
    cin >> h >> w >> k;
    if(h > w) swap(h, w);
    if(h < k) {
        if(w < k) Out(mint(1));
        else Out(com(w, k - 1).pow(h));
        return;
    }
    if(h * w >= (k - 1) * (h + w)) {
        Out(mint(1));
        return;
    }
    assert(k != 2);
    ll r = (k - 1) * (h + w) - h * w;
    if(k == 3) {
        if(h == 3 and w == 3) {
            assert(r == 3);
            Out(mint(78));
        } else {
            assert(r <= 2);
            Out(com(h * w, r));
        }
    } else {
        if((h - 3) * (w - 3) <= 5LL) {
            assert(h == 4 or h == 5);
            if(h == 4) assert(4LL <= w or w <= 8LL);
            if(h == 5) assert(w == 5LL);
            Out(k4memo[h][w]);
        } else {
            assert(r <= 3);
            Out(com(h * w, r));
        }
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    k4memo[4][4] = 8490 - 48;
    k4memo[4][5] = 64320;
    k4memo[4][6] = 123600;
    k4memo[4][7] = 95088;
    k4memo[4][8] = 35672;
    k4memo[5][5] = 52120;

    

    int testcase = 1; 
    cin >> testcase;
    rep(i, testcase) {
        t = i + 1;
        solve();
    } 

    return 0;
}
