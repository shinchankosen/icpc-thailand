#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto&& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

void chmin(ll &a, ll b) { a = min(a, b); }
int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> dp(1 << k, INF);
    rep(i, n) {
        ll a, c; cin >> a >> c;
        ll sum = 0;
        rep(j, a) {
            ll x; cin >> x;
            x --;
            sum |= (1LL << x);
        }
        chmin(dp[sum], c);
    }
    for(int bit = (1 << k) - 1; bit >= 0; bit --) {
        rep(i, k) {
            if(bit >> i & 1) continue;
            chmin(dp[bit], dp[bit | (1 << i)]);
        }
    }
    rep(bit, 1 << k) {
        for(int bit1 = (bit - 1) & bit; bit1 > 0; bit1 = (bit1 - 1) & bit) {
            chmin(dp[bit], dp[bit1] + dp[bit ^ bit1]);
        }
    }
    for(int bit = (1 << k) - 1; bit >= 0; bit --) {
        rep(i, k) {
            if(bit >> i & 1) continue;
            chmin(dp[bit], dp[bit | (1 << i)]);
        }
    }
    rep(i, m) {
        ll a;
        cin >> a;
        ll sum = 0;
        rep(j, a) {
            ll x; cin >> x;
            x --;
            sum |= (1LL << x);
        }
        cout << (dp[sum] == INF ? -1 : dp[sum]) << endl;
    }
    return 0;
}
