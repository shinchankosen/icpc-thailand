#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;

struct segtree{

    using S = pair<int, int>;
    S op(S a, S b) {
        return min(a, b);
    }
    S E = make_pair(1 << 30, -1);

    int n, size;
    vector<S> d;
    segtree(int n) : segtree(vector<S>(n, E)) {}
    segtree(const vector<S>& v) : n(v.size()) {
        size = 1;
        while (size < n) size *= 2;
        d = vector<S>(2 * size, E);
        for (int i=0;i<n;i++){
            d[size+i] = v[i];
        }
        for (int i=size-1;i>=1;i--) {d[i] = op(d[2*i], d[2*i+1]);}
    }

    void set(int p, S x) {
        p += size;
        d[p] = x;
        while (p > 1) {
            p /= 2;
            d[p] = op(d[2 * p], d[2 * p + 1]);
        }
    }

    S prod(int l, int r) {
        S sml = E;
        S smr = E;
        l += size;
        r += size;
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr); 
            l /= 2;
            r /= 2;
        }
        return op(sml, smr);
    }
};



template<class T> struct BIT {
    int n; 
    vector<T> a;
    BIT(int m) : n(m), a(m + 1, 0) {}
    void add(int x, T y) {
        x ++;
        while(x <= n) {
            a[x] += y;
            x += x & -x;
        }
    }
    T sum(int x) {
        T r = 0;
        while(x > 0) {
            r += a[x];
            x -= x & -x;
        }
        return r;
    }
    T sum(int x, int y) {
        return sum(y) - sum(x);
    }
};

void solve() {
    int n; cin >> n;
    vector<ll> a(n), b(n), c(n);
    vector<vector<pair<ll, ll>>> v(n);
    rep(i, n - 1) {
        cin >> a[i] >> b[i] >> c[i];
        a[i] --; b[i] --;
        v[a[i]].push_back({b[i], c[i]});
        v[b[i]].push_back({a[i], c[i]});
    }
    vector<int> le(n, -1), ri(n, -1);
    int id = 0;
    BIT<ll> bitcnt(n + n);
    vector<int> dis(n, -1);
    segtree seg(n + n);
    vector<vector<int>> vecp(100001), vecm(100001); 
    auto dfs = [&](auto dfs, int now, int p) -> void {
        seg.set(id, {dis[now], now});
        le[now] = id ++;
        for(auto [to, co] : v[now]) {
            if(p == to) continue;
            dis[to] = dis[now] + 1;
            vecp[co].push_back(id - 1);
            // bitsum.add(id - 1, co);
            bitcnt.add(id - 1, 1LL);
            
            dfs(dfs, to, now);
            vecm[co].push_back(id - 1);
            // bitsum.add(id - 1, -co);
            bitcnt.add(id - 1, -1LL);
            seg.set(id - 1, {dis[now], now});
        }
        ri[now] = id ++;
    };
    dis[0] = 0;
    dfs(dfs, 0, -1);

    // vector<pair<int, int>> base(n + n, make_pair(1 << 30, -1));
    // rep(i, n) {
    //     base[i] = make_pair(dis[i], i);
    // }
    
    // rep(i, n) {
    //     cout << le[i] << " " <<ri[i] << " " << bitsum.sum(le[i], ri[i]) << " " << bitcnt.sum(le[i], ri[i]) << endl;
    // }


    int q; cin >> q;
    vector<ll> ans0(q, -1), ans1(q, -1);
    vector<ll> cntq(q, -1), lc(q, -1);
    vector<vector<tuple<int, int, int, bool>>> task(100001); // id, le, ri
    vector<int> X(q), Y(q);
    rep(i, q) {
        int x, y; cin >> x >> y;
        x --; y --;
        X[i] = x;
        Y[i] = y;
        if(le[x] > le[y]) swap(x, y);
        ll cnt = 0;
        {
            int lca = seg.prod(le[x], le[y] + 1).second;
            // cout << lca << endl;
            lc[i] = lca;
            // sum -= bitsum.sum(le[x], le[lca]);
            // cout << le[x] << " " << le[lca] << endl;
            cnt -= bitcnt.sum(le[x], le[lca]);
            // cout << cnt << endl;
            // sum += bitsum.sum(le[lca], le[y]);
            cnt += bitcnt.sum(le[lca], le[y]);
            cntq[i] = cnt;
            // cout << cnt << endl;
            //
        }
        int mc = cnt / 2;
        if(cnt & 1) {
            task[50000].push_back({i, 0, 100000, 0}); // mid以下にcnt個以上あるか？
        } else {
            task[50000].push_back({i, 0, 100000, 0}); // mid以下にcnt個以上あるか？
            task[50000].push_back({i, 0, 100000, 1}); // mid以下にcnt個以上あるか？
        }
        
        // cout << cnt << " " << sum << endl;
    }
    bool con = 1;
    while(con) {
        con = 0;
        vector<vector<tuple<int, int, int, bool>>> nx(100001);
        BIT<int> bitsum(n + n); 
        rep(j, 100001) {
            for(int e : vecp[j]) {
                bitsum.add(e, 1);
            }
            for(int e : vecm[j]) {
                bitsum.add(e, -1);
            }
            for(auto [i, l, r, flag] : task[j]) {
                int x = X[i];
                int y = Y[i];
                if(flag) {
                    if(r - l == 1) {
                        ans1[i] = r;
                    } else {
                        con = 1;
                        int sum = 0;
                        int lca = lc[i];
                        sum -= bitsum.sum(le[x], le[lca]);
                        sum += bitsum.sum(le[lca], le[y]);
                        lc[i] = lca;
                        int cnt = cntq[i];
                        cnt /= 2;
                        cnt ++;
                        // cout << i << " " << j << " " << sum << " " << cnt << endl;
                        if(sum >= cnt) {
                            int nxmid = (l + j) / 2;
                            nx[nxmid].push_back({i, l, j, 1});
                        } else {
                            int nxmid = (j + r) / 2;
                            nx[nxmid].push_back({i, j, r, 1});
                        }
                    }
                } else {
                    if(r - l == 1) {
                        ans0[i] = r;
                    } else {
                        con = 1;
                        int sum = 0;
                        int lca = lc[i];
                        sum -= bitsum.sum(le[x], le[lca]);
                        sum += bitsum.sum(le[lca], le[y]);
                        lc[i] = lca;
                        int cnt = cntq[i];
                        cnt = (cnt + 1) / 2;
                        // cout << i << " " << j << " " << sum << " " << cnt << endl;
                        if(sum >= cnt) {
                            int nxmid = (l + j) / 2;
                            nx[nxmid].push_back({i, l, j, 0});
                        } else {
                            int nxmid = (j + r) / 2;
                            nx[nxmid].push_back({i, j, r, 0});
                        }
                    }
                }
            }
        }
        task = move(nx);
    }
    rep(i, q) {
        if(ans1[i] == -1) {
            cout << ans0[i] << ".0\n";
        } else {
            int x = ans0[i], y = ans1[i];
            int sum = x + y;
            if(sum & 1) {
                cout << sum / 2 << ".5\n"; 
            } else {
                cout << sum / 2 << ".0\n"; 
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t --) solve();
}
