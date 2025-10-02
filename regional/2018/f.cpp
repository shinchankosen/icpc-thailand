#include<bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < (n); i ++)
#define all(a) (a).begin(), (a).end()
 
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

const int MOD = 1000000007, mod = 1000000007;
using mint = Modint<MOD>;

long long modinv(long long a, long long MOD) {
    long long b = MOD, u = 1, v = 0;
    while (b) {
        long long t = a / b;
        a -= t * b; std::swap(a, b);
        u -= t * v; std::swap(u, v);
    }
    u %= MOD; 
    if (u < 0) u += MOD;
    return u;
}

long long modpow(long long a, long long n, long long MOD) {
    long long res = 1;
    a %= MOD;
    if(n < 0) {
        n = -n;
        a = modinv(a, MOD);
    }
    while (n > 0) {
        if (n & 1) res = res * a % MOD;
        a = a * a % MOD;
        n >>= 1;
    }
    return res;
}

const int base = 1 << 12;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;

    mint inv2 = modinv(2, mod);
    mint inv4 = modinv(4, mod);

    vector<mint> memo(30, 1);
    vector<ll> memo2(30, 1);
    for(int i = 1; i <= 29; i ++) memo[i] = memo[i - 1] * 7;
    for(int i = 1; i <= 27; i ++) memo2[i] = memo2[i - 1] * 7;

    vector<bool> flag(10000, 0);
    vector<mint> d(10000);
    auto f = [&](auto &&f, ll x) -> mint {
        ll i = -1;
        ll y = x;
        while(y > 0) {
            y /= 7;
            i ++;
        }
        if(i <= 0) {
            return mint(0);
        }
        if(x == memo2[i]) {
            if(flag[i + base]) return d[i]; 
            i --;
        }
        ll a = x / memo2[i];
        ll b = x % memo2[i];
        mint ans = f(f, memo2[i]) * mint(a) * mint(a + 1) * inv2;
        mint num1 = f(f, b) * mint(a + 1);
        ans += num1;
        mint num2 = inv2 * mint(b) * (memo[i] * 2 - mint(b + 1)) * mint(a);
        ans += num2;
        mint num3 = inv4 * (memo[i] - mint(1)) * memo[i] * mint(a) * mint(a - 1);
        ans += num3;
        if(x == memo2[i + 1]) {
            flag[i + 1 + base] = 1;
            d[i + 1] = ans;
        }
        return ans.val;
    };
    for(int i = 1; i <= t; i ++) {
        ll x; cin >> x;
        ll ans = f(f, x + 1).val;
        cout << "Case " << i << ": " << ans << '\n';
    }
}
