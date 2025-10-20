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


struct UF {
    vector<int> par;
    vector<int> cnt;
    UF (int n) : par(n, -1), cnt(n, 0) {}
    int root(int x) {
        if(par[x] < 0) return x;
        return par[x] = root(par[x]);
    }
    bool connect(int x, int y) {
        x = root(x);
        y = root(y);
        if(x == y) return false;
        if(par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        cnt[x] += cnt[y];
        par[y] = x;
        return true;
    }
    int size(int x) {
        return -par[root(x)];
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, m; cin >> n >> m;
    UF uf(m);
    vector<pair<ll, int>> vec;
    vec.reserve(n);
    vector<ll> a(n, -1), b(n, -1);
    rep(i, n) {
        ll t; cin >> t;
        if(t == 1) {
            cin >> a[i];
            a[i] --;
        } else {
            cin >> a[i] >> b[i];
            a[i] --; 
            b[i] --;
        }
        ll v; cin >> v;
        vec.pb(v, i);
    }
    sort(all(vec));
    reverse(all(vec));
    ll ans = 0;
    vector<int> used;
    for(auto [x, i] : vec) {
        if(b[i] == -1) {
            int v = uf.root(a[i]);
            if(uf.cnt[v] + 1 > uf.size(v)) continue;
            used.pb(i);
            uf.cnt[v] ++;
            ans += x;
            continue;
        }
        int v1 = uf.root(a[i]);
        int v2 = uf.root(b[i]);
        if(v1 == v2) {
            int v = v1;
            if(uf.cnt[v] + 1 > uf.size(v)) continue;
            used.pb(i);
            uf.cnt[v] ++;
            ans += x;
            continue;
        }
        if(uf.cnt[v1] + uf.cnt[v2] + 1 > uf.size(v1) + uf.size(v2)) {
            continue;
        }
        uf.connect(a[i], b[i]);
        int v = uf.root(a[i]);
        used.pb(i);
        uf.cnt[v] ++;
        ans += x;
    }
    rep(i, m) {
        if(uf.size(i) > uf.cnt[uf.root(i)]) {
            cout << -1 << '\n';
            return 0;
        }
    }

    cout << ans << '\n';


    vector<vector<int>> v(n + m);
    vector<int> an(n + m, -1);
    for(int x : used) {
        // cout << x << " " << a[x] << " " << b[x] << " " << a[x] + n << " " << b[x] + n << endl;
        v[x].pb(a[x] + n);
        v[a[x] + n].pb(x);
        
        if(b[x] != -1) {
            v[x].pb(b[x] + n);
            v[b[x] + n].pb(x);
        }
    }
    set<int> st;
    rep(i, m) {
        st.insert(uf.root(i) + n);
    }

    vector<pair<int, int>> matchedge, evec;
    vector<int> seen(n + m, 0);
    
    vector<int> loop;
    int rr = -1;
    auto find_cycle = [&](auto &&f, int now, int p = -1) -> bool {
        // cout << now << " ";
        seen[now] = 1;
        for(int e : v[now]) {
            if(e == p) continue;
            if(seen[e]) {

                rr = e;
                return true;
            }
            if(f(f, e, now)) {
                loop.pb(now);
                if(rr == now) return false;
                return true;
            }
        }
        return false;
    };
    // rep(i, n + m) {
    //     cout << "i = " << i << " ";
    //     for(int x : v[i]) cout << x << " ";
    //     cout << endl;
    // }

    bool NG = 0;
    pair<int, int> ng;
    auto dfs = [&](auto &&dfs, int now, int p = -1) -> bool {
        vector<int> vv;
        for(int e : v[now]) {
            if(e == p) {
                continue;
            }
            if(make_pair(now, e) == ng or make_pair(e, now) == ng) continue;
            if(dfs(dfs, e, now)) {
                vv.pb(e);
            }
        }
        if((int)vv.size() >= 2) {
            NG = 1;
            return false;
        }
        if(vv.empty()) {
            return true;
        }
        evec.pb(vv[0], now);
        return false;
    };
    for(int s : st) {
        // cout << s << endl;
        loop.clear();
        evec.clear();
        find_cycle(find_cycle, s);
        // cout << endl;
        // for(int x : loop) cout << x << " ";
        // cout << endl;
        if(loop.empty()) {
            dfs(dfs, s, -1);
            for(auto e : evec) {
                matchedge.pb(e);
            }
            NG = 0;
            continue;
        }
        ng = make_pair(loop[0], loop[1]);
        dfs(dfs, s, -1);
        if(!NG) {
            for(auto e : evec) matchedge.pb(e);
            continue;
        }
        NG = 0;
        evec.clear();
        ng = make_pair(loop[1], loop[2]);
        dfs(dfs, s, -1);
        if(!NG) {
            for(auto e : evec) matchedge.pb(e);
        }
        NG = 0;
    }

    for(auto [x, y] : matchedge) {
        if(x < y) swap(x, y);
        an[x] = y;
    }

    
    for(int i = n; i < n + m; i ++) cout << an[i] + 1 << " ";
    cout << '\n';
}
