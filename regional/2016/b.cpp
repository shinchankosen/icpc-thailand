#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;

ll mod = 1000000007;
int main() {
    int n, m; cin >> n >> m;
    while(n) {
        vector<ll> dp(n, 0LL);
        rep(j, m + 1) dp[j % (n - 1)] ++;
        auto a = dp;
        vector<int> r(n + n);
        rep(i, n + n) r[i] = i % (n - 1);
        rep(i, n - 2) {
            vector<ll> nx(n, 0LL);
            rep(j, n - 1) {
                rep(k, n - 1) {
                    (nx[r[j + k]] += (dp[j] * a[k])) %= mod;
                     
                }
            }
            dp = move(nx);
        }
        
        cout << (dp[0] * n) % mod << endl;
        cin >> n >> m;
    }
}
