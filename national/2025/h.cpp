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



void solve() {
    ll n; cin >> n;
    n *= 2;
    ll m = n;
    vector<ll> cnt(21, 0LL);
    int x = 0;
    while(m) {
        x ++;
        cnt[x] += m / 5;
        m /= 5;
    }
    rep(i, 20) cnt[i] -= cnt[i + 1];
    cnt[0] = 0;
    while(!cnt.empty() and cnt.back() == 0) cnt.pop_back();
    if(cnt.empty()) {
        cout << 0 << endl;
        return;
    }
    x = cnt.size() - 1;
    ll mod = MOD7;
    ll ans = 0;

    auto sum = [&](ll le, ll ri, ll d = 1) -> ll {
        ll num1 = ((ri - le) / d) + 1;
        ll num2 = ((le + ri));
        if(num1 & 1) num2 /= 2;
        else num1 /= 2;
        num1 %= mod;
        num2 %= mod;
        return ((num1 * num2) % mod);
    };
    while(x) {
        while(n % 5) {
            ans += n * x;
            ans %= mod;
            n --;
            cnt[x] --;
            if(cnt[x] == 0) x --;
            if(x == 0) break;
        }
        if(x == 0) {
            if(ans < 0) ans += mod;
            cout << ans << endl;
            return;
        }
        ll num = cnt[x] / 4;
        ll r = cnt[x] % 4;
        ans += sum(n - num * 5, n) * x;
        ans -= sum(n - num * 5, n, 5) * x;
        ans %= mod;
        n -= num * 5;
        n --;
        while(r --) {
            ans += n * x;
            ans %= mod;
            n --;
        }
        x --;
    }
    if(ans < 0) ans += mod;
    cout << ans << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int testcase = 1; 
    cin >> testcase;
    while(testcase --) solve();

    return 0;
}
