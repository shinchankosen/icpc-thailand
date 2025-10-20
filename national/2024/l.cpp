#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;

int main() {
    string T;cin>>T;
    int Q;
    cin>>Q;
    vector<int> answers;
    while (Q--) {
        string S;
        cin >> S;
        int ans = 1e9;
        rep(i,T.size()) {
            int cur = i;
            int idx = 0;
            int er = 0;
            while (cur < T.size() && idx < S.size()) {
                if (S[idx] == T[cur]) {
                    idx++;
                } else {
                    er++;
                }
                cur++;
            }
            if (idx == S.size()) {
                ans = min(ans, er);
            }
        }
        answers.push_back(ans);
    }
    for (auto x : answers)  {
        if (x == 1e9) cout << -1 << endl;
        else cout << x << endl; 
    }
}
