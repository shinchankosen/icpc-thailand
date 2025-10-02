#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = __int128;

int main() {
    rep(_, 5) {
        int n; cin >> n;
        vector<ll> dp(n + 1, 1);
        dp[0] = 0;
        vector<ll> a(n + 1, 0);
        for(ll i = 1; i <= n; i ++) {
            for(ll j = i; j <= n; j += i) {
                a[i] += dp[j];
            }
        }
        rep(i, n + 1) a[i] = a[i] * a[i] * a[i] * a[i];
        for(ll i = n; i >= 1; i --) {
            for(ll j = i + i; j <= n; j += i) {
                a[i] -= a[j];
            }
        }
        string s = "";
        ll x = a[1];
        while(x) {
            s += char('0' + (x % 10));
            x /= 10;
        }
        reverse(s.begin(), s.end());
        cout << s << endl;
        // cout << a[1] << endl;
        // rep(i, n + 1) cout << a[i] << " ";
        // cout << endl;
    }
}
