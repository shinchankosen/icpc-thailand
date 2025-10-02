#include<bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < (n); i ++)
#define all(a) (a).begin(), (a).end()

template <class T> struct BIT {
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
    T get(int x) {
        return a[x];
    }
};

const int lim = 1e6 + 10;

using pa = pair<int, int>;
int inv[1000001];
int main(void) {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    rep(_, t) {
        cout << "Case " <<_+1<<":" << '\n';
        int q; cin >> q;
        vector<int> type(q), s(q), val(q), until(q);
        int ma = -1;
        priority_queue<pa, vector<pa>, greater<pa>> pq;
        rep(i, q) {
            cin >> type[i];
            if(type[i] == 1) {
                cin >> s[i] >> val[i] >> until[i];
                until[i] ++;
                ma = max(ma, val[i]);
            } else {
                cin >> s[i] >> val[i];
            }
        }
        int sz = 0;
        rep(i, ma + 1) inv[i] = 0;
        rep(i, q) {
            if(type[i] == 1) inv[val[i]] ++;
        }
        vector<int> Val;
        rep(i, ma + 1) if(inv[i]) {
            inv[i] = sz ++;
            Val.push_back(i);
        }
        // for(int x : Val) cout << x << " ";
        // cout << '\n';
        BIT<int> bit(sz);
        rep(i, q) {
            while(!pq.empty() and pq.top().first <= s[i]) {
                bit.add(pq.top().second, -1);
                pq.pop();
            }
            if(type[i] == 1) {
                bit.add(inv[val[i]], 1);
                pq.push({until[i], inv[val[i]]});
            } else {
                if(bit.sum(0, sz) < val[i]) {
                    cout << -1 << '\n';
                    continue;
                }
                int base = 0;
                int add = 1, sum = 0;
                while(add * 2 < sz) add <<= 1;
                while(add > 0) {
                    int num = bit.get(base + add) + sum;
                    if(num < val[i]) {
                        base += add;
                        sum = num;
                    } 
                    add >>= 1;
                    assert(base < sz);
                    while(base + add >= sz) add >>= 1;
                } 
                
                cout << Val[base] << '\n';
            }
        }
    }


}

