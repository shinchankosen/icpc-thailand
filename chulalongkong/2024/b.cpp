#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto&& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

const int N = 5000001;
const int M = 5000000;
void chmin(int &a, int b) { a = min(a, b); }
int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int m, n, k;
    cin >> m >> n >> k;
    
    vector<int> ps;
    {
        vector<bool> isp(N, 1);
        isp[0] = isp[1] = 0;
        for(int i = 2; i < N; i ++) {
            if(!isp[i]) continue;
            for(int j = i + i; j < N; j += i) {
                isp[j] = 0;
            }
        }
        rep(i, N) if(isp[i]) ps.pb(i);
    }
    vector<int> vec;
    {
        vector<bool> ex(N);
        rep(i, m) {
            int x; cin >> x;
            ex[x] = 1;
        }
        rep(i, N) if(ex[i]) vec.pb(i);
    }

    reverse(all(vec));
    int inf = 1 << 30;
    ll sum = 0, Min = INF;
    vector<int> dpb(N, inf), dps(N, 0);
    rep(i, n - k) {
        dpb[vec[i]] = vec[i];
        sum += (ll)vec[i];
        Min = min(Min, (ll)vec[i]);
    }
    for(int i = n - k; i < m; i ++) {
        dps[vec[i]] ++;
    }
    // foa(e, vec) {
    //     if(e > 20) break;
    //     cout << e << " ";
    // }
    // cout << endl;
    
    foa(e, ps) {
        for(int i = M / e; i >= 1; i --) {
            chmin(dpb[i], dpb[i * e]);
            dps[i] += dps[i * e];
        }
    }
    ll ans = 0;
    // for(int i = 1; i <= 13; i ++) {
    //     cout << dpb[i] << " ";
    // }
    // cout << endl;
    // for(int i = 1; i <= 13; i ++) {
    //     cout << dps[i] << " ";
    // }
    // cout << endl;
    
    for(ll i = 1; i < N; i ++) {
        if(dps[i] >= k + 1) {
            ans = max(ans, sum - Min + i);
        } else if(dps[i] == k and dpb[i] != inf) {
            ans = max(ans, sum + i - (ll)dpb[i]);
        }
    }
    cout << ans << endl;
    
    
    return 0;
}
