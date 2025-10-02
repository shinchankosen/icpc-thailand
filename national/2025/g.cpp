#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(),(v).end()
#define pb emplace_back
#define rep(i, n) for(int i=0;i<(n);i++)
#define foa(e, v) for(auto& e : v)
#define dout(a) cout<<fixed<<setprecision(10)<<a<<'\n';
#define Cout(a) cout<<a<<'\n';

using ll = long long;
using ld = long double;
using Int = __int128;
template <class T> using pqr = priority_queue<T, vector<T>, greater<T>>;

template <typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
    bool compare = a < b;
    if(compare) a = b;
    return compare;
}
template <typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
    bool compare = a > b;
    if(compare) a = b;
    return compare;
}
template <typename T> inline T back(std::set<T> &s) {
    return *s.rbegin();
}
template <typename T> inline T back(std::multiset<T> &s) {
    return *s.rbegin();
}
template <typename T> inline T pop_back(std::set<T> &s) {
    auto it = prev(s.end());
    T val = *it;
    s.erase(it); 
    return val;
}
template <typename T> inline T pop_back(std::multiset<T> &s) {
    auto it = prev(s.end());
    T val = *it;
    s.erase(it); 
    return val;
}

const int dy[8] = {-1, 0, 0, 1, 1, -1, 1, -1};
const int dx[8] = {0, -1, 1, 0, -1, -1, 1, 1};

const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (3LL << 59);
const int inf = 1 << 30;
const char br = '\n';

const int l1 = 10001;
const int l2 = 20001;
void solve() {
    int n, m; cin >> n >> m;
    vector<int> div(1 << 17);
    rep(i, 1 << 17) div[i] = i / m;
    vector<tuple<int, int, int>> vec;
    vec.reserve(n);
    rep(i, n) {
        int a, b, c; cin >> a >> b >> c;
        vec.push_back({a, b, c});
    }
    sort(all(vec));
    int p = -1;
    vector<int> len(n + n + 1);

    vector<int> k(n + n + 1);
    int cc = 0;
    for(auto [a, b, c] : vec) {
        len[cc] = a - p - 1;
        len[cc + 1] = b - a + 1;
        k[cc + 1] = c;
        cc += 2;
        p = b;
    }
    len[cc] = 86400 - p - 1;
    int L = 20001;
    vector<int> dp(L, -inf);
    
    dp[0] = 0;
    rep(i, n + n + 1) {
        if(i & 1) {
            vector<int> nx(L, -inf);
            for(int j = k[i]; j < L; j ++) {
                if(dp[j - k[i]] >= 0) chmax(nx[j], div[dp[j - k[i]]] * m);
                chmax(nx[j - k[i]], dp[j] + len[i]);
            }
            dp = move(nx);
        } else {
            for(int j = 0; j < L; j ++) {
                dp[j] += len[i]; 
            }
        }
        // rep(j, 5) cout << dp[j] << " " ;
        // cout << endl;
    }

    // rep(i, n + n + 1) cout << len[i] << " " << k[i] << endl;
    cout << *max_element(all(dp)) / m << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int testcase = 1; 
    // cin >> testcase;
    while(testcase --) solve();

    return 0;
}
