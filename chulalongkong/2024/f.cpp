#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto&& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll n, c;
    cin >> n >> c;
    vector<vector<pair<ll, int>>> v(n);
    ll ans = 0;
    rep(i, n - 1) {
        ll a, b, d;
        cin >> a >> b >> d;
        a --; b --;
        ans += d;
        v[a].push_back({d, b});
        v[b].push_back({d, a});
    }
    
    vector<pair<int, int>> vec;
    int from = -1;
    bool f = 0;
    auto dfs = [&](auto dfs, int now, int p) -> void {
        bool fnow = f;
        for(auto [cost, to] : v[now]) {
            if(p == to) continue;
            dfs(dfs, to, now);
        }
        if(!now) {
            if(from == -1) {
                return ;
            }
            vec.push_back({from + 1, now + 1});
            return;
        }
        if(f != fnow) {
            return;
        }
        if(from == -1) {
            from = now;
            ans += c;
        } else {
            vec.push_back({from + 1, now + 1});
            from = -1;
        }
        f ^= 1;
    };
    dfs(dfs, 0, -1);
    if((int)vec.size() > n / 2) {
        cout << -1 << endl;
    } else {
        cout << ans << " " << vec.size() << endl;
        for(auto [x, y] : vec) {
            cout << x << " " << y << endl;
        }
    }
    return 0;
}
