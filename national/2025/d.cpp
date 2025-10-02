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

void solve() {
    // 頂点数がわかる　(N=P+1)
    // P, Qから各頂点の次数がわかる
    // 3だけのパスを考え、その間に2をできるかぎり交互に挟む
    // +2の処理(2が2つの場合に注意), +1の処理が2種類ある(2が1つの場合に注意), +0の処理も必要
    int p, q, r; cin >> p >> q >> r;
    int n = p + 1;
    int X = q * 2 + p * 2;
    int c1 = 0, c2 = 0, c3 = 0;
    c1 += 2;
    X -= 2;
    int m = n - 2;
    if(n & 1) {
        c2 ++;
        X -= 4;
        m --;
    }
    if(n == 2) {
        if(q == 0 and r == 0) {
            cout << 2 << endl;
            cout << 1 << " " << 2 << endl;
        } else cout << -1 << endl;
        
        return;
    }
    // cout << n << " " << X << endl;
    if(m * 4 <= X and X <= m * 5 and m >= 0 and X % 2 == 0) {
        assert(m % 2 == 0);
        while(m) {
            if(X == m * 5) {
                X -= 10;
                m -= 2;
                c3 ++;
                c1 ++;
            } else {
                X -= 8;
                m -= 2;
                c2 += 2;
            }
        }
    } else {
        cout << -1 << endl;
        return;
    }
    if(c3 == 0) {
        if(r == c2 - 1) {
            cout << n << endl;
            for(int i = 1; i < n; i ++) {
                cout << i << " " << i + 1 << endl;
            }
        } else {
            cout << -1 << endl;
        }
        return ;
    }
    if(c3 == 1) {
        if(c2 == 0) {
            if(r == 0) {
                cout << 4 << endl;
                for(int i = 1; i <= 3; i ++) {
                    cout << 4 << " " << i << endl;
                }
            } else {
                cout << -1 << endl;
            }
        } else if(c2 == 1) {
            if(r == 2) {
                cout << 5 << endl;
                cout << 1 << " " << 2 << endl;
                cout << 2 << " " << 3 << endl;
                cout << 3 << " " << 4 << endl;
                cout << 3 << " " << 5 << endl;
            } else {
                cout << -1 << endl;
            }
        } else if(c2 == 2) {
            if(r == 3) {
                cout << 6 << endl;
                cout << 6 << " " << 1 << endl;
                cout << 1 << " " << 2 << endl;
                cout << 2 << " " << 3 << endl;
                cout << 3 << " " << 4 << endl;
                cout << 3 << " " << 5 << endl;
            } else if(r == 4) {
                cout << 6 << endl;
                cout << 1 << " " << 2 << endl;
                cout << 2 << " " << 3 << endl;
                cout << 3 << " " << 4 << endl;
                cout << 3 << " " << 5 << endl;
                cout << 5 << " " << 6 << endl;
            } else {
                cout << -1 << endl;
            }
        } else {
            if(1 + c2 <= r and r <= 3 + c2) {
                cout << n << endl;
                int i = 2;
                int cnt = r - c2;
                vector<int> vec;
                int cc = 0;
                while(cnt --) {
                    cc ++;
                    cout << 1 << " " << i << endl;
                    vec.pb(i);
                    c2 --;
                    r --;
                    i ++;
                }
                int j = i - 1;
                for(int k = j + 1; k <= 4; k ++) {
                    cout << 1 << " " << k << endl;
                    cc ++;
                }
                i = 5;
                for(int k = 3; k <= j; k ++) {
                    cout << i << " " << k << endl;
                    cc ++;
                    i ++;
                }
                j = 2;
                while(i <= n) {
                    cc ++;
                    cout << j << " " << i << endl;
                    j = i;
                    i ++;
                }
                // assert(cc == n);
            } else {
                cout << -1 << endl;
            }
        }
        return;
    }

    // c3 >= 2
    
    int bitween = min(c3 - 1, c2);
    int lim = min(c3 + 2, c2);
    r -= 4 * (c3 - 1);
    int b0 = bitween, b1 = c2 - bitween, b2 = 0;
    r -= b1;
    if(r < 0) {
        cout << -1 << endl;
        return;
    }
    while(r > 0) {
        // 1 to 2
        // 0 to 2
        // 0 to 1
        // 1 to 1
        
         {
            if(b0) {
                if(r >= 2 and b2 < lim) {
                    b2 ++;
                    b0 --;
                    r --;
                } else if(b2) {
                    b0 --;
                    b1 ++;
                } else if(b1 and b2 < lim) {
                    b1 --;
                    b2 ++;
                } else if(b0 >= 2) {
                    b0 --;
                    b1 ++;
                } else {
                    cout << -1 << endl;
                    return;
                } 
            } else {
                if(!b1) {
                    cout << -1 << endl;
                    return;
                }
                if(b2 < lim) {
                    b2 ++;
                    b1 --;
                } else {
                    cout << -1 << endl;
                    return;
                }
            }
            r --;
        } 
    }
    cout << n << endl;
    if(!b2) {
        // 間にいれる
        vector<int> deg;
        while(c3 --) {
            deg.pb(3);
            while(b1) {
                deg.pb(2);
                b1 --;
            }
            if(b0) {
                deg.pb(2);
                b0 --; 
            }
        }
        int sz = deg.size();
        for(int i = 1; i < sz; i ++) {
            cout << i << " " << i + 1 << endl;
        }
        vector<int> vec;
        vec.pb(1);
        rep(i, sz) {
            if(deg[i] == 3) vec.pb(i + 1);
        }
        vec.pb(sz);
        assert((int)vec.size() == n - sz);
        for(int i = sz + 1; i <= n; i ++) {
            cout << vec.back() << " " << i << endl;
            vec.pop_back();
        }
    } else {
        // 0のやつがあれば間に
        // それ以外は葉につなげる
        vector<int> deg;
        while(c3 --) {
            deg.pb(3);
            if(b0) {
                deg.pb(2);
                b0 --; 
            }
        }
        int sz = deg.size();
        for(int i = 1; i < sz; i ++) {
            cout << i << " " << i + 1 << endl;
        }
        vector<int> vec;
        vec.pb(1);
        rep(i, sz) {
            if(deg[i] == 3) vec.pb(i + 1);
        }
        // vec.pb(sz);
        b2 --;
        cout << sz << " " << sz + 1 << endl;
        vector<int> vv;
        int i = sz + 1;
        while(b1 --) {
            cout << i << " " << i + 1 << endl;
            i ++;
        }
        vv.pb(i);
        while(b2 --) {
            int now = vec.back();
            i ++;
            vec.pop_back();
            cout << i << " " << now << endl;
            vv.pb(i);
        }
        
        for(int j = i + 1; j <= n; j ++) {
            if(vec.empty()) {
                int now = vv.back();
                vv.pop_back();
                cout << j << " " << now << endl;
            } else {
                int now = vec.back();
                vec.pop_back();
                cout << j << " " << now << endl;
            }
        }
        assert(vec.empty() and vv.empty());
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    int testcase = 1; 
    cin >> testcase;
    while(testcase --) solve();

    return 0;
}
