#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;

ll modpow(ll a, ll b, ll p) {
    a %= p;
    ll r = 1;
    while(b) {
        if(b & 1) {
            r *= a;
            r %= p;
        }
        a *= a;
        a %= p;
        b >>= 1;
    }
    return r;
}

int main() {
    int p; cin >> p;
    vector<ll> dp(p - 1, 0);
    for(int i = 0; i < p - 1; i ++) {
        if(i == 0) dp[0] += p - 1;
        else {
            int g = __gcd(i, p - 1);
            dp[g] += g;
        }
    }
    for(int i = p - 2; i >= 1; i --) {
        if((p - 1) % i != 0) continue;
        for(int j = i + i; j <= p - 1; j += i) {
            if(j == p - 1) dp[0] += dp[i];
            else dp[j] += dp[i];
        }
    }

    auto find_p = [&]() -> ll {
        for(ll i = 1; i < p; i ++) {
            vector<int> cnt(p, 0);
            ll s = 1;
            bool ng = 0;
            rep(j, p - 1) {
                if(++ cnt[s] >= 2) {
                    ng = 1;
                    break;
                }
                
                s *= i;
                s %= p;
            }
            if(!ng) return i;
        }
        return -1;
    };
    ll r = find_p();
    vector<ll> ans(p, 0);
    // rep(i, p - 1) cout << dp[i] << " ";
    // cout << endl;
    // cout << r << endl;
    rep(i, p - 1) {
        ans[modpow(r, i, p)] += dp[i];
    }
    for(int i = 1; i < p; i ++) cout << ans[i] << " ";
    cout << endl;
}
