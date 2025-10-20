#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")


#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;
#define pb emplace_back
void chmin(int &a, int b) { a = min(a, b); }
void chmax(int &a, int b) { a = max(a, b); }

int inf = 1 << 29;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector a(n, vector(m, 0));
    rep(i, n) rep(j, m) cin >> a[i][j];
    vector<int> dp(10001, -inf);
    dp[a[0][0]] = a[0][m - 1];

    vector<int> md(n + 1, 0);
    for(int i = n - 1; i >= 0; i --) {
        md[i] = *max_element(all(a[i])) + md[i + 1];
    }
    int ans = 0;
    for(int i = 1; i < n; i ++) {
        rep(j, 9900) {
            if(dp[j] >= 0) {
                chmax(ans, (j + md[i]) * dp[j]);
                chmax(ans, j * (dp[j] + md[i]));
                
            }
        }
        vector<int> nx(10001, -inf);
        vector<int> le(10, m);
        rep(j, m) chmin(le[a[i][j]], j);
        vector<int> ma(m + 1, 0);
        for(int j = m - 1; j >= 0; j --) {
            ma[j] = ma[j + 1];
            chmax(ma[j], a[i][j]);
        }
        rep(j, 10) {
            if(le[j] >= m - 1) le[j] = -1;
            else {
                le[j] = ma[le[j] + 1];
            } 
        }
        rep(j, 9990) {
            rep(k, 10) if(le[k] != -1) chmax(nx[j + k], dp[j] + le[k]); 
        }
        dp = move(nx);
    }
    
    rep(j, 10001) if(dp[j] >= 0) {
        chmax(ans, j * dp[j]);
    }
    cout << ans << endl;
}
