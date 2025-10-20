#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")


#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;
#define pb emplace_back
void chmin(int &a, int b) { if(a > b) a = b; }
void chmax(int &a, int b) { if(a < b) a = b; }

const int N = 2000001;
int a[N], le[N], ri[N], add[N] = {0};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, t;
    cin >> n >> t;
    vector<int> st;
    st.reserve(t);
    vector<int> p(t, -1);
    rep(i, t) {
        cin >> a[i];
        int pos = -1;
        while(!st.empty() and a[i] > a[st.back()]) {
            pos = st.back();
            st.pop_back();
        }
        if(pos != -1) p[pos] = i;
        if(!st.empty()) p[i] = st.back();
        st.pb(i);
    }
    vector<int> R(t, -1), L(t, -1);
    int root = -1;
    rep(i, t) {
        if(p[i] != -1) {
            if(L[p[i]] == -1) L[p[i]] = i;
            else R[p[i]] = i;
        }
        else root = i;
    }
    
    auto dfs = [&](auto &&dfs, int now) -> void {
        le[now] = now;
        ri[now] = now + 1;
        if(L[now] != -1) {
            dfs(dfs, L[now]);
            chmin(le[now], le[L[now]]);
            chmax(ri[now], ri[L[now]]);
        }
        if(R[now] != -1) {
            dfs(dfs, R[now]);
            chmin(le[now], le[R[now]]);
            chmax(ri[now], ri[R[now]]);
        }
    };
    dfs(dfs, root);
    int now = n;
    ll ans = 0;
    ll val = t;
    vector<ll> cnt(t + 1, 0);
    rep(i, t) {
        int l = le[i] - 1;
        int r = ri[i];
        l = (l == -1 ? n : a[l]);
        r = (r == t ? n : a[r]);
        cnt[ri[i] - le[i]] += min(l, r) - a[i];
    }
    while(now and val) {
        while(val > 0 and cnt[val] == 0) val --;
        if(val == 0) break;
        if(now <= cnt[val]) {
            ans += val * now;
            break;
        }
        ans += val * cnt[val];
        now -= cnt[val];
        val --;        
    }
    cout << ans << endl;
    return 0;
}
