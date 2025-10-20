#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;

int main() {
    int n = 3;
    vector<ll> x(n), y(n);
    rep(i, n) {
        cin >> x[i] >> y[i];
    }
    rep(i, n) {
        int i1 = (i + 1) % n;
        int i2 = (i + 2) % n;
        ll basex = x[i1];
        ll basey = y[i1];
        basex += x[i] - x[i1];
        basey += y[i] - y[i1];
        basex += x[i2] - x[i1];
        basey += y[i2] - y[i1];
        cout << basex << " " << basey << endl;
    }
}
