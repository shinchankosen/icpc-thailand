#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;

template <class T> struct BIT {
    int n;
    vector<T> a;
    int h;
    BIT(int m) : n(m), a(m + 1, 0), h( (1 << __lg(m))) {}
    void add(int x, T y) {
        x ++ ;
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
    int lower_bound(T w) {
        int x = 0;
        for(int i = h; i; i >>= 1) {
            if(x + i <= n) {
                ll num = a[x + i];
                if(num <= w) {
                    x += i;
                    w -= num;
                }
            }
        }
        return x;
    }
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n; cin >> n;
    vector<ll> a(n);
    BIT<ll> bit(n), bitb(n);
    rep(i, n) bit.add(i, 1);
    rep(i, n) bitb.add(i, 1);
    rep(i, n) {
        cin >> a[i];
        a[i] --;
    }
    if(n % 2 == 0) {
        vector<int> b(n, 0);
        int x = a[0];
        if(x >= n / 2) {
            b[0] = x - n / 2;
        } else {
            b[0] = x + n / 2;
        }
        bit.add(a[0], -1);
        bitb.add(b[0], -1);
        for(int i = 1; i < n; i ++) {
            int cnt = bit.sum(a[i] + 1);
            int id = bitb.lower_bound(cnt - 1);
            bit.add(a[i], -1);
            bitb.add(id, -1);
            b[i] = id;
        }
        rep(i, n) cout << b[i] + 1 << " ";
        cout << '\n';
    } else {
        bit.add(a[0], -1);
        ll val = bit.sum(a[1] + 1);
        ll num = a[0] * (n - 1) + val - 1;
        vector<ll> b(n, 0);
        num += (n - 1) * n / 2;
        num %= (n - 1) * n;
        b[0] = num / (n - 1);
        bitb.add(b[0], -1);
        {
            num = num % (n - 1);
            int id = bitb.lower_bound(num);
            b[1] = id;
        }
        bit.add(a[1], -1);
        
        bitb.add(b[1], -1);
        for(int i = 2; i < n; i ++) {
            int cnt = bit.sum(a[i] + 1);
            int id = bitb.lower_bound(cnt - 1);
            bit.add(a[i], -1);
            bitb.add(id, -1);
            b[i] = id;
        }
        rep(i, n) cout << b[i] + 1 << " ";
        cout <<'\n';
    }
}
