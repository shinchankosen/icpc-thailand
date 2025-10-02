#include<bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(a) (a).begin(), (a).end()

struct scc_graph {
    public:
    explicit scc_graph(int _n=0) : n(_n), G(_n), rG(_n), comp(_n, -1), visited(_n, 0) {}
    void addedge(int from, int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    vector<vector<int>> scc() {
        fill(all(visited), 0);
        fill(all(comp), -1);
        order.clear();
        for(int i=0;i<n;++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        comp_size=0;
        for(int i=size(order) - 1; i >= 0; --i) {
            if (comp[order[i]] < 0) rdfs(order[i], comp_size++);
        }
        vector<vector<int>> v(comp_size);
        for(int i=0;i<n;++i) v[comp[i]].push_back(i);
        return v;
    }

    void dfs(int v) {
        visited[v]=true;
        for (auto to : G[v]) if (!visited[to]) dfs(to);
        order.push_back(v);
    }

    void rdfs(int v, int k) {
        comp[v]=k;
        for(auto to :rG[v]) {
            if (comp[to]<0) rdfs(to, k);
        }
    }

    private:
    vector<vector<int>> G, rG;
    vector<int> order, comp;
    vector<bool> visited;
    int n, comp_size;
};

int main() {

    int t;cin>>t;
    vector<int> ans;
    while (t--) {
        int n, m;
        cin>>n>>m;
        scc_graph g(n);
        for (int i=0;i<m;++i) {
            int a,b;
            cin>>a>>b;
            g.addedge(a,b);
        }
        auto scc = g.scc();
        ans.push_back(scc.size());

    }
    for (auto x : ans) cout << x << '\n';

}
