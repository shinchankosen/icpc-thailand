# translate https://codeforces.com/gym/102091/submission/340272957 to python

# #include <bits/stdc++.h>
# using namespace std;

# #define all(v) (v).begin(),(v).end()
# #define pb emplace_back
# #define rep(i, n) for(int i=0;i<(n);i++)
# #define foa(e, v) for(auto& e : v)
# #define dout(a) cout<<fixed<<setprecision(10)<<a<<'\n';
# #define Cout(a) cout<<a<<'\n';

# using ll = long long;
# using ld = long double;
# using Int = __int128;
# template <class T> using pqr = priority_queue<T, vector<T>, greater<T>>;

# template <typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
#     bool compare = a < b;
#     if(compare) a = b;
#     return compare;
# }
# template <typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
#     bool compare = a > b;
#     if(compare) a = b;
#     return compare;
# }
# template <typename T> inline T back(std::set<T> &s) {
#     return *s.rbegin();
# }
# template <typename T> inline T back(std::multiset<T> &s) {
#     return *s.rbegin();
# }
# template <typename T> inline T pop_back(std::set<T> &s) {
#     auto it = prev(s.end());
#     T val = *it;
#     s.erase(it); 
#     return val;
# }
# template <typename T> inline T pop_back(std::multiset<T> &s) {
#     auto it = prev(s.end());
#     T val = *it;
#     s.erase(it); 
#     return val;
# }

# const int dy[8] = {-1, 0, 0, 1, 1, -1, 1, -1};
# const int dx[8] = {0, -1, 1, 0, -1, -1, 1, 1};

# const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (3LL << 59);
# const int inf = 1 << 30;
# const char br = '\n';

# void solve(int t) {
#     int n; cin >> n;
#     vector<int> a(n);
#     rep(i, n) cin >> a[i];
#     sort(all(a));
#     // 指定したところの両端の内側も動かさなきゃ
#     vector<vector<int>> v;
#     vector<int> b;
#     rep(i, n) {
#         if(b.empty()) b.pb(a[i]);
#         else {
#             if(b.back() + 2 >= a[i]) {
#                 b.pb(a[i]);
#             } else {
#                 v.pb(b);
#                 b.clear();
#                 b.pb(a[i]);
#             }
#         }
#     }
#     v.pb(b);
#     b.clear();

#     int ans = 0;
#     foa(e, v) chmax(ans, ssize(e));

#     int sz = v.size();
#     rep(i, sz - 1) {
#         int sz1 = v[i].size();
#         int sz2 = v[i + 1].size();
#         { // 1
#             if(v[i].back() + 3 >= v[i + 1][0]) {
#                 chmax(ans, sz2 + 1);
#                 chmax(ans, sz1 + 1);
#                 if(sz2 >= 2 and v[i + 1][0] + 1 >= v[i + 1][1]) chmax(ans, sz1 + sz2);
#                 if(sz1 >= 2 and v[i][sz1 - 2] + 1 >= v[i][sz1 - 1]) chmax(ans, sz1 + sz2);
#             }
#         }{ // 2
#             if(v[i].back() + 3 >= v[i + 1][0]) {
#                 if(sz1 >= 2) {
#                     chmax(ans, sz2 + 2);
#                     if(sz1 >= 3 and v[i][sz1 - 3] + 1 >= v[i][sz1 - 2]) chmax(ans, sz1 + sz2);
#                 }
#                 if(sz2 >= 2) {
#                     chmax(ans, sz1 + 2);
#                     if(sz2 >= 3 and v[i + 1][1] + 1 >= v[i + 1][2]) chmax(ans, sz1 + sz2);
#                 }
#             }
#             if(v[i].back() + 4 >= v[i + 1][0]) {
#                 chmax(ans, 2);
#                 bool flag1 = (sz1 >= 2 and v[i][sz1 - 2] + 1 >= v[i][sz1 - 1]);
#                 bool flag2 = (sz2 >= 2 and v[i + 1][0] + 1 >= v[i + 1][1]);
#                 if(flag1) {
#                     if(flag2) {
#                         chmax(ans, sz1 + sz2);
#                     } else {
#                         chmax(ans, sz1 + 1);
#                     }
#                 } else {
#                     if(flag2) {
#                         chmax(ans, sz2 + 1);
#                     }
#                 }
#             }
#         }
#     }
#     for(int i = 1; i < sz - 1; i ++) {
#         // +1 or -1   and   +1 or -1
#         int sz1 = v[i - 1].size();
#         int sz2 = v[i].size();
#         int sz3 = v[i + 1].size();
#         if(v[i - 1].back() + 3 >= v[i][0] and v[i].back() + 3 >= v[i + 1][0]) {
#             // sz2 == 1, 2, or more 2
#             rep(k1, 2) {
#                 rep(k2, 2) {
#                     if(sz2 == 1 and (!k1 or k2)) {
#                         continue;
#                     }
                    
#                     if(!k1 and k2 and sz2 == 2) {
#                         if(v[i][0] != v[i][1]) continue;
#                     }
#                     bool conk1 = 0;
#                     bool conk2 = 0;
#                     if(k1) {
#                         conk1 = (sz1 >= 2 and v[i - 1][sz1 - 2] + 1 >= v[i - 1][sz1 - 1]);
#                     } else {
#                         conk1 = (sz2 >= 2 and v[i][0] + 1 >= v[i][1]);
#                     }
#                     if(k2) {
#                         conk2 = (sz2 >= 2 and v[i][sz2 - 2] + 1 >= v[i][sz2 - 1]);
#                     } else {
#                         conk2 = (sz3 >= 2 and v[i + 1][0] + 1 >= v[i + 1][1]);
#                     }
#                     if(conk1) {
#                         if(conk2) {
#                             chmax(ans, sz1 + sz2 + sz3);
#                         } else {
#                             chmax(ans, sz1 + sz2 + 1);
#                         }
#                     } else {
#                         if(conk2) {
#                             chmax(ans, 1 + sz2 + sz3);
#                         } else {
#                             chmax(ans, sz2 + 2);
#                         }
#                     }
#                 }
#             }
#         }
#     }
#     cout << "Case " << t << ": " << ans << endl;
# }

# int main() {
#     cin.tie(0);
#     ios::sync_with_stdio(false);

#     int testcase = 1; 
#     cin >> testcase;
#     rep(i, testcase) solve(i + 1);

#     return 0;
# }


import sys
input = sys.stdin.readline

def solve(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()

    v = []
    b = []

    for x in a:
        if not b:
            b.append(x)
        else:
            if b[-1] + 2 >= x:
                b.append(x)
            else:
                v.append(b)
                b = [x]
    v.append(b)

    ans = 0
    for e in v:
        ans = max(ans, len(e))

    sz = len(v)

    for i in range(sz - 1):
        sz1 = len(v[i])
        sz2 = len(v[i + 1])

        # 1
        if v[i][-1] + 3 >= v[i + 1][0]:
            ans = max(ans, sz2 + 1)
            ans = max(ans, sz1 + 1)
            if sz2 >= 2 and v[i + 1][0] + 1 >= v[i + 1][1]:
                ans = max(ans, sz1 + sz2)
            if sz1 >= 2 and v[i][sz1 - 2] + 1 >= v[i][sz1 - 1]:
                ans = max(ans, sz1 + sz2)

        # 2
        if v[i][-1] + 3 >= v[i + 1][0]:
            if sz1 >= 2:
                ans = max(ans, sz2 + 2)
                if sz1 >= 3 and v[i][sz1 - 3] + 1 >= v[i][sz1 - 2]:
                    ans = max(ans, sz1 + sz2)
            if sz2 >= 2:
                ans = max(ans, sz1 + 2)
                if sz2 >= 3 and v[i + 1][1] + 1 >= v[i + 1][2]:
                    ans = max(ans, sz1 + sz2)

        if v[i][-1] + 4 >= v[i + 1][0]:
            ans = max(ans, 2)
            flag1 = (sz1 >= 2 and v[i][sz1 - 2] + 1 >= v[i][sz1 - 1])
            flag2 = (sz2 >= 2 and v[i + 1][0] + 1 >= v[i + 1][1])
            if flag1:
                if flag2:
                    ans = max(ans, sz1 + sz2)
                else:
                    ans = max(ans, sz1 + 1)
            else:
                if flag2:
                    ans = max(ans, sz2 + 1)

    for i in range(1, sz - 1):
        sz1 = len(v[i - 1])
        sz2 = len(v[i])
        sz3 = len(v[i + 1])
        if v[i - 1][-1] + 3 >= v[i][0] and v[i][-1] + 3 >= v[i + 1][0]:
            for k1 in range(2):
                for k2 in range(2):
                    if sz2 == 1 and (not k1 or k2):
                        continue
                    if not k1 and k2 and sz2 == 2:
                        if v[i][0] != v[i][1]:
                            continue

                    if k1:
                        conk1 = (sz1 >= 2 and v[i - 1][sz1 - 2] + 1 >= v[i - 1][sz1 - 1])
                    else:
                        conk1 = (sz2 >= 2 and v[i][0] + 1 >= v[i][1])

                    if k2:
                        conk2 = (sz2 >= 2 and v[i][sz2 - 2] + 1 >= v[i][sz2 - 1])
                    else:
                        conk2 = (sz3 >= 2 and v[i + 1][0] + 1 >= v[i + 1][1])

                    if conk1:
                        if conk2:
                            ans = max(ans, sz1 + sz2 + sz3)
                        else:
                            ans = max(ans, sz1 + sz2 + 1)
                    else:
                        if conk2:
                            ans = max(ans, 1 + sz2 + sz3)
                        else:
                            ans = max(ans, sz2 + 2)

    print(f"Case {t}: {ans}")


def main():
    testcase = int(input())
    for i in range(testcase):
        solve(i + 1)


if __name__ == "__main__":
    main()
