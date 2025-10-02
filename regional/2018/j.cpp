#include<bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("fast-math")
using namespace std;
using ll = long long;
#define rep(i, n) for(int i = 0; i < (n); i ++)
#define all(a) (a).begin(), (a).end()

int main(void) {
    // ll l, h;
    int l, h;
    while (cin>>l>>h, l!=0&&h!=0) {
        double sum = 0;
        int cnt = h - l + 1;
        double i = l;
        rep(_, cnt) {
            sum += pow(i, -2./3);
            i += 1.0;
        }
        // for (ll i=l;i<=h;++i) {
            // sum += pow((double)i, -2./3);
        // }
        // printf("%5E\n", sum * 1.0e-15 / 3);
        stringstream os;
        os << setprecision(6) << sum * 1.0e-15 / 3;
        string str = os.str();
        // cout << str << endl;
        int id = -1;
        int sz = str.size();
        rep(j, sz) if(str[j] == '-') id = j;
        str[id - 1] = 'E';
        string ans = str.substr(0, id + 1) + "0" + str.substr(id + 1, sz - id - 1);

        id = -1;
        sz = ans.size();
        rep(j, sz) if(ans[j] == 'E') id = j;
        cout << ans.substr(0, id) + string(7 - id, '0') + ans.substr(id, sz - id) << '\n';
        // cout << ans << '\n';
    }
}
