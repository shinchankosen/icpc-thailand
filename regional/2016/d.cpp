#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i ++)
using ll = long long;

 ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) return x = 1, y = 0, a;
    ll d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
 }

int main(){
    int T;
    cin>>T;

    while (T--) {

        ll ax, ay, bx, by, K;
        cin>>ax>>ay>>bx>>by>>K;
        ll dx = bx - ax;
        ll dy = by - ay;
        ll g = gcd(dx, dy);
        dx /= g, dy /= g;

        ll x, y;
        extgcd(-dy, dx, x, y);
        for (int k = 0; k < K; ++k) {
            cout << x + k * dx + ax << " " << y + k * dy + ay << endl;
        }

    }



}
