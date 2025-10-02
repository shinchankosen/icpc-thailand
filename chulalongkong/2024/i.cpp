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
    int t;
    cin >> t;
    rep(_, t) {
        int n;
        cin >> n;
        vector<ll> a(n + 1, -1);
        for(int i = 2; i <= n; i ++) {
            cout << "? " << 1 << " " << i << endl;
            ll x; cin >> x;
            a[i] = x;
        }
        reverse(all(a));
        rep(i, 2) a.pop_back();
        sort(all(a));
        ll ans = a[0];
        n -= 2;
        rep(i, n) {
            ans = min(ans, a[i] ^ a[i + 1]);
        }
        cout << "! " << ans << endl;
    }
    return 0;
}
