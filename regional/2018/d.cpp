#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(a) (a).begin(), (a).end()
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while(t --) {
        int n; cin >> n;
        if(n == 0) {
            cout << 0 << '\n';
            continue;
        }
        vector<ll> a(n);
        for(int i = 0; i < n; i ++) {
            cin >> a[i];
        }
        // sort(all(a));
        ll ans = 1;
        ll p = a[0];

        for(int i = 0; i < n; i ++) {
            if(p + 20 < a[i]) {
                p = a[i];
                ans ++;
            }
        }
        cout << ans << '\n';
    }
}
