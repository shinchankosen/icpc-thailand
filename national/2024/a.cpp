#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;

ll s(ll n){
    return (n + 1) * n / 2;
}
int main() {
    ll n; cin >> n;
    ll sum = 0;
     {
        for(ll i = 1; i <= n - 2; i += 2) {
            sum += s(n - i - 1) + 1;
        }
    }
    cout << sum << endl;
}
