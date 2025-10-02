#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;

void solve(int t) {
    cout << "Case #" << t << ":" << endl;
    int n, q, r; cin >> n >> q >> r;
    vector<int> dis(n, 0), sz(n, 0);
    vector<vector<int>> v(n);
    rep(i, n - 1) {
        int a, b; cin >> a >> b;
        a --; b --;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    vector<vector<int>> par(18, vector(n, -1));
    auto dfs = [&](auto &&dfs, int now, int p) -> void {
        sz[now] = 1;
        par[0][now] = p;
        for(int e : v[now]) {
            if(e == p) continue;
            dis[e] = dis[now] + 1;
            dfs(dfs, e, now);
            sz[now] += sz[e];
        }
    };
    r --;
    dfs(dfs, 0, -1);
    rep(i, 17) rep(j, n) {
        if(par[i][j] == -1) continue;
        par[i + 1][j] = par[i][par[i][j]];
    }
    // rep(i, 2) {
    //     rep(j, n) cout << par[i][j] << " ";
    //     cout << endl;
    // }
    // rep(i, n) cout << sz[i] << endl;
    rep(i, q) {
        int x, y; cin >> x >> y;
        y --;
        if(x == 0) {
            r = y;
            continue;
        } 
        if(y == r) {
            cout << n << endl;
        } else if(dis[y] >= dis[r]) {
            cout << sz[y] << endl;
        } else {
            x = r;
            int d = dis[r] - dis[y] - 1;
            // cout << "dis = " << d << endl;
            rep(j, 18) {
                if(d >> j & 1) x = par[j][x];
            }
            // cout << x << " " << par[0][x] << endl;
            if(par[0][x] == y) {
                cout << n - sz[x] << endl;
                // cout << y << " " << r << " " << x << " " << n - sz[x] << endl;
            } else {
                cout << sz[y] << endl;
            }
            
        }
    }
}
int main() {
    int t; cin >> t;
    rep(i, t) solve(i + 1);
}
