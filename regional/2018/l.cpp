#include<bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < (n); i ++)
#define all(a) (a).begin(), (a).end()

// int a[1001][1001];
int sum[1001][1001];
int dp[1001][1001];
string s[1001];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t --) {
        int h, w; cin >> h >> w;
        getline(cin, s[0]);
        rep(i, h) getline(cin, s[i]);
        // rep(i, h) rep(j, w) cin >> a[i][j];
        rep(i, h) rep(j, w) sum[i + 1][j + 1] = (s[i][j * 2] - '0');
        rep(i, h + 1) rep(j, w) sum[i][j + 1] += sum[i][j];
        rep(i, h) rep(j, w + 1) sum[i + 1][j] += sum[i][j];
        int ans = 0;
        for(int i = h - 1; i >= 0; i --) {
            for(int j = w - 1; j >= 0; j --) {
                int num = 1;
                if(i < h - 1 and j < w - 1) num = dp[i + 1][j + 1] + 1;
                while(sum[i + num][j + num] - sum[i][j + num] - sum[i + num][j] + sum[i][j] >= 2) num --;
                dp[i][j] = num;
                if(ans < num) ans = num;
            }
        }
        cout << ans << '\n';
    }
}
