#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < (n); i ++)
#define all(a) (a).begin(), (a).end()

ll modinv(ll a, ll MOD) {
    ll b = MOD, u = 1, v = 0;
    while(b) 
    {
        ll t = a / b;
        a -= t * b;
        swap(a, b);
        u -=  t * v;
        swap(u, v);
    }
    u %= MOD;
    if (u < 0) u += MOD;
    return u;
}

ll garner(vector<ll> b, vector<ll> m, ll MOD) {
    m.push_back(MOD);
    vector<ll> coefs(size(m), 1);
    vector<ll> constants(size(m), 0);
    for(int k=0;k<size(b);++k){
        ll t = ((b[k] - constants[k]) * modinv(coefs[k], m[k])) % m[k];
        if (t < 0) t = m[k];
        for (int i=k+1;i<size(m);++i) {
            (constants[i] += t * coefs[i]) %= m[i];
            (coefs[i] *= m[k]) %= m[i];
        }
    }
    return constants.back();
}

int main(void) {
    int q;
    cin>>q;
    vector<int> answers;
    while (q--) {
        int n1, n2, n3;
        cin>>n1>>n2>>n3;
        int x3n1,x3n2,x3n3;
        cin>>x3n1>>x3n2>>x3n3;
        // ll a = garner({x3n1,x3n2, x3n3}, {n1,n2,n3}, 1<<22);
        // cout << a << endl;

        for (int x=1;x<1<<21;++x) {
            long long x3 = (ll)x*x*x;
            if (x3 % n1 == x3n1 && x3 % n2 == x3n2 && x3 % n3 == x3n3) {
                answers.push_back(x);
                break;
            } 
        }
    }
    for (auto x : answers) cout << x << endl;
}
