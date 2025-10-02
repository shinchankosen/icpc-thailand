#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;
#define pb emplace_back
#define all(a) (a).begin(), (a).end() 

void solve(ll t) {
    int sz = 1;
    vector<array<int, 27>> tr;
    using ar = array<int, 27>;
    cout << "Case " << t << ":" << endl;
    ar base;
    rep(i, 26) base[i] = -1;
    int g = 26;
    base[g] = 0;
    tr.pb(base);
    int n; cin >> n;
    rep(i, n) {
        string s; cin >> s;
        int now = 0;
        vector<int> vec;
        for(char e : s) {
            int num = e - 'a';
            vec.pb(now);
            if(tr[now][num] == -1) {
                tr[now][num] = sz;
                tr.pb(base);
                sz ++;
            }
            now = tr[now][num];
        }
        vec.pb(now);
        reverse(all(vec));
        for(int x : vec) {
            int sum = 0;
            rep(j, 26) {
                if(tr[x][j] != -1) {
                    sum ^= tr[tr[x][j]][g];
                }
            }
            sum ++;
            tr[x][g] = sum;
        }
    }
    int q; cin >> q;
    rep(_, q) {
        string s; cin >> s;
        int now = 0;
        vector<int> vec;
        for(char e : s) {
            int num = e - 'a';
            vec.pb(now);
            if(tr[now][num] == -1) {
                tr[now][num] = sz;
                tr.pb(base);
                sz ++;
            }
            now = tr[now][num];
        }
        vec.pb(now);
        reverse(all(vec));
        for(int x : vec) {
            int sum = 0;
            rep(j, 26) {
                if(tr[x][j] != -1) {
                    sum ^= tr[tr[x][j]][g];
                }
            }
            sum ++;
            tr[x][g] = sum;
        }
        
        int sum = 0;
        rep(i, 26) {
            if(tr[0][i] != -1) sum ^= tr[tr[0][i]][g];
        }
        cout << (sum ? 1 : 2) << endl;
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll t; cin >> t;
    rep(i, t) solve(i + 1);
    return 0;
}
