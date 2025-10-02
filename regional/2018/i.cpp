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


int bit[1001][1001];

void add(int x, int y, int val) {
    
    x ++; y ++;
    while(x <= 1000) {
        int yy = y;
        while(yy <= 1000) {
            bit[x][yy] += val;
            yy += yy & -yy;
        }
        x += x & -x;
    }
}

int bbsum(int x, int y) {
    int r = 0;
    while(x > 0) {
        int yy = y;
        while(yy > 0) {
            r += bit[x][yy];
            yy -= yy & -yy;
        }
        x -= x & -x;
    }
    return r;
}
int bsum(int x1, int x2, int y1, int y2) {
    return bbsum(x2, y2) - bbsum(x2, y1) - bbsum(x1, y2) + bbsum(x1, y1);
}
const ll mod = 3428977;
const ll base = 184903;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    int t; cin >> t;
    rep(i, t) {
        rep(i, 1001) rep(j, 1001) bit[i][j] = 0;
        int h, w; cin >> h >> w;
        vector<int> y(h * w), x(h * w);
        vector a(h, vector(w, 0));
        rep(i, h) rep(j, w) {
            cin >> a[i][j];
            a[i][j] --;
            y[a[i][j]] = i;
            x[a[i][j]] = j;
        }
        vector ymin(1000, 1000), xmin(1000, 1000), ymax(1000, -1), xmax(1000, -1);
        ll ans = 0, d = 1, sum = 0;
        rep(id, h * w) {
            int i = y[id], j = x[id];
            add(j, i, 1);
            chmin(xmin[i], j);
            chmin(ymin[j], i);
            chmax(xmax[i], j);
            chmax(ymax[j], i);
            sum += bsum(xmin[i], xmax[i] + 1, ymin[j], ymax[j] + 1);
            if(sum >= mod) sum -= mod;
            d *= base;
            d %= mod;
            ans += sum * d;
            ans %= mod;
        }

        cout << "Case " << i + 1 << ": " << ans << '\n';
    
    }

    return 0;
}
