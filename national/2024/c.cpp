#include <bits/stdc++.h>

using namespace std;
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")


#define rep(i,n) for(int i=0;i<(n);i++)
#define all(a) (a).begin(),(a).end()
using ll = long long;


template<class Cap> struct mf_graph {

    struct edge{
        int from, to;
        Cap cap, flow;
    };
    struct _edge{
        int to, rev;
        Cap cap;
    };

    int n;
    vector<pair<int, int>> pos;
    vector<vector<_edge>> g;

    mf_graph(int n) : n(n), g(n) {}

    int add_edge(int from, int to, Cap cap) {
        int m = size(pos);
        pos.push_back({from,size(g[from])});
        int from_id = size(g[from]);
        int to_id = size(g[to]);
        if (from == to) {
            to_id++;
        }
        g[from].push_back(_edge{to, to_id, cap});
        g[to].push_back(_edge{from, from_id, 0});
        return m;
    }

    Cap flow(int s, int t, Cap flow_limit = numeric_limits<Cap>::max()) {
        vector<int> level(n), iter(n);
        queue<int> que;
        auto bfs = [&] {
            fill(all(level), -1);
            level[s] = 0;
            while (!que.empty()) que.pop();
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.push(e.to);
                }
            }
        };
        auto dfs = [&](auto self, int v, Cap up) {
            if (v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for (int& i = iter[v]; i<size(g[v]);++i) {
                _edge& e = g[v][i];
                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d = self(self, e.to, min(up - res, g[e.to][e.rev].cap));
                if (d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap-= d;
                res +=d;
                if (res == up) break; 
            }
            return res;
        };
        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            fill(all(iter), 0);
            while (flow< flow_limit) {
                Cap f = dfs(dfs, t, flow_limit - flow);
                if (!f) break;
                flow += f;
            }
        }
        return flow;
    }
    edge get_edge(int i) {
        int m = size(pos);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }

    vector<edge> edges() {
        int m = (size(pos));
        vector<edge> result;
        for (int i=0;i<m;++i) {
            result.push_back(get_edge(i));
        }
        return result;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N,M;
    cin>>N>>M;
    vector<vector<int>> A(N, vector<int>(M));
    for (auto & v : A) for (auto &x : v) cin>>x;

    vector<int> vec;
    for (auto & v : A) for (auto &x : v) vec.push_back(x);
    sort(vec.begin(), vec.end());
    

    // x 以上のやつのみをつかう
    auto f = [&](int x) {
        mf_graph<ll> mf(N+M+2);
        for (int i=0;i<N;++i) {
            for (int j = 0; j<M;++j) {
                if (A[i][j]>=x) {
                    mf.add_edge(i, N+j, 1);
                }
            }
        }
        for (int i=0;i<N;++i) {
            mf.add_edge(N+M, i, 1);
        }
        for (int j=0;j<M;++j) {
            mf.add_edge(j+N,N+M+1,1);
        }
        int flow = mf.flow(N+M, N+M+1);
        return flow == N;
    };

    int ok = -1, ng = N * M;
    while (abs(ok-ng) > 1) {
        int mid = (ok + ng) / 2;
        if (f(vec[mid])) ok = mid;
        else ng = mid;
    }
    cout << vec[ok] << endl;


    mf_graph<ll> mf(N+M+2);
    for (int i=0;i<N;++i) {
        for (int j = 0; j<M;++j) {
            if (A[i][j]>=vec[ok]) {
                mf.add_edge(i, N+j, 1);
            }
        }
    }
    for (int i=0;i<N;++i) {
        mf.add_edge(N+M, i, 1);
    }
    for (int j=0;j<M;++j) {
        mf.add_edge(j+N,N+M+1,1);
    }
    int flow = mf.flow(N+M, N+M+1);
    
    vector<int> ans(N);
    for (auto e : mf.edges()) {
        if (e.flow == 1 && e.from < N) {
            ans[e.from] = e.to - N + 1;
        }
    }
    for (auto x : ans) cout << x << " ";
    cout << endl;

}
