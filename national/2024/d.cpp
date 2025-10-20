#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;
#define pb emplace_back
int main() {
    ll n; cin >> n;
    vector<ll> x(n), y(n), a(n), b(n);
    vector<pair<ll, ll>> v1, v2;
    rep(i, n) {
        cin >> x[i] >> y[i];
        v1.pb(x[i], y[i]);
    }
    rep(i, n) {
        cin >> a[i] >> b[i];
        v2.pb(a[i], b[i]);
    }
    sort(all(v1));
    sort(all(v2));
    rep(i, n) {
        x[i] = v1[i].first;
        y[i] = v1[i].second;
    }
    rep(i, n) {
        a[i] = v2[i].first;
        b[i] = v2[i].second;
    }

    ll xrate = 0;
    rep(i, n) rep(j, n) if(x[i] != x[j]) {
        xrate = (a[j] - a[i]) / (x[j] - x[i]);
    }
    rep(i, n) rep(j, n) if(y[i] != y[j]) {
        xrate = (b[j] - b[i]) / (y[j] - y[i]);
    }
    ll X = a[0] - (x[0] * xrate);
    ll Y = b[0] - (y[0] * xrate);
    bool ng = 0;
    rep(i, n) {
        if(x[i] * xrate + X != a[i] or y[i] * xrate + Y != b[i]) {
            ng = 1;
        }
    }
    
    if(ng) {
        cout << -1 << endl;
    } else {
        cout << xrate << " " << X << " " << Y << endl;
    }
    
}
