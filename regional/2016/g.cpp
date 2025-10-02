#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;

const ll mod = 1000000007;

vector<vector<ll>> mul(vector<vector<ll>> &a, vector<vector<ll>> &b) {
    int n = a.size();
    vector<vector<ll>> c(n, vector(n, 0LL));
    rep(i, n) rep(j, n) rep(k, n) {
        (c[i][j] += a[i][k] * b[k][j]) %= mod;
    }
    return c;
}


vector<vector<ll>> matpow(vector<vector<ll>> a, ll m) {
    int n = a.size();
    vector<vector<ll>> ret(n, vector(n, 0LL));
    rep(i, n) ret[i][i] = 1;
    while(m) {
        if(m & 1) {
            ret = mul(ret, a);
        }
        a = mul(a, a);
        m /= 2;
    }
    return ret;
}

ll calc(ll r, ll k) {
    vector ak(2, vector(2, 1LL));
    ak[1][1] = 0;
    ak = matpow(ak, k);
    vector a(3, vector(3, 0LL));
    a[2][0] = a[2][2] = 1;
    rep(i, 2) rep(j, 2) a[i][j] = ak[i][j];
    r /= k;
    r ++;
    a = matpow(a, r);
    ll ans = 0;
    ans += a[2][0] + a[2][1];
    // cout << ans << endl;
    return ans;
}
void solve(ll t) {
    ll l, r, k; cin >> l >> r >> k;
    l --;
    ll ans = calc(r, k) - calc(l, k);
    ans %= mod;
    ans += mod;
    ans %= mod;
    cout << "Case " << t << ": " << ans << endl;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll t; cin >> t;
    rep(i, t) solve(i + 1);
    return 0;
}
