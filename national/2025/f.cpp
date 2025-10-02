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
static const int th = 330;
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> task(m + 1);
    vector<int> ans(n, -1);
    using pq = priority_queue<int, vector<int>, greater<int>>;
    vector small(th, vector(th, pq()));
    vector<int> a(n), b(n), c(n);
    rep(i, n) {
        cin >> a[i] >> b[i] >> c[i];
        task[b[i]].pb(i);
    }
    int nx = 1;
    for(int i = 1; i <= m; i ++) {
        int id1 = inf, id2 = inf;
        for(int j = 1; j < th; j ++) {
            if(!small[j][i % j].empty()) {
                chmin(id1, small[j][i % j].top());
            }
        }
        foa(j, task[i]) {
            chmin(id2, j);
        }
        if(nx <= i and id1 != id2) {
            if(id1 < id2) {
                ans[id1] = i;
                nx = i + c[id1];
                small[a[id1]][b[id1] % a[id1]].pop();
            } else {
                ans[id2] = i;
                nx = i + c[id2];
                vector<int> tmp = task[i];
                task[i].clear();
                foa(e, tmp) if(e != id2) task[i].pb(e);
            }
        }
        foa(j, task[i]) {
            if(a[j] < th) {
                small[a[j]][i % a[j]].push(j);
            } else {
                if(i + a[j] <= m) {
                    task[i + a[j]].pb(j);
                }
            }
        }
    }
    foa(e, ans) cout << e << " ";
    cout << endl;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int testcase = 1; 
    // cin >> testcase;
    while(testcase --) solve();

    return 0;
}
