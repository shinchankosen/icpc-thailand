#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<ll> x(n, 0), y(n, 0);
    vector<vector<tuple<ll, ll, ll>>> v(n);
    rep(i, m) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a --; b --;
        v[a].push_back({b, c, d});
        v[b].push_back({a, -c, -d});
    }
    vector<bool> seen(n, 0);
    vector<int> vec;
    auto dfs = [&](auto dfs, int now) -> void {
        seen[now] = 1;
        vec.push_back(now);
        for(auto [to, xd, yd] : v[now]) {
            if(!seen[to]) {
                x[to] = x[now] + xd;
                y[to] = y[now] + yd;
                dfs(dfs, to);
            }
        }
    };
    ll base = -1000000000;
    rep(i, n) {
        if(!seen[i]) {
            dfs(dfs, i);
            ll mx = (1LL << 60), my = (1LL << 60);
            for(int e : vec) {
                mx = min(mx, x[e]);
                my = min(my, y[e]);
            } 
            for(int e : vec) {
                x[e] -= mx;
                y[e] -= my;
                x[e] += base;
                y[e] += base;
            }
            vec.clear();
        }
    }
    rep(i, n) cout << x[i] << " " << y[i] << '\n';
    
}
