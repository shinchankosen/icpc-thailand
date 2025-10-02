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
    ll n, m, h, q;
    cin >> n >> m >> h >> q;
    vector<ll> x(n), y(n);
    rep(i, n) cin >> x[i] >> y[i];
    multiset<ll> ms;
    rep(i, m) {
        ll a; cin >> a;
        ms.insert(a);
    }
    vector<ll> v;
    rep(i, n) {
        auto itr = ms.lower_bound(abs(y[i] - h));
        if(itr == ms.end()) continue;
        v.pb(x[i]);
        ms.erase(itr);
    }

    rep(_, q) {
        int a; cin >> a;
        if(a > (int)v.size()) {
            cout << -1 << endl;
        } else {
            cout << v[a - 1] << endl;
        }
    }
    return 0;
}
