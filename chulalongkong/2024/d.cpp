#include <bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define pb(a) push_back(a)
#define rep(i, n) for(int i=0;i<n;i++)
#define foa(e, v) for(auto&& e : v)
using ll = long long;
const ll MOD7 = 1000000007, MOD998 = 998244353, INF = (1LL << 60);
#define dout(a) cout<<fixed<<setprecision(10)<<a<<endl;

// https://lorent-kyopro.hatenablog.com/entry/2021/03/12/025644 
template <class S, S (*op)(S, S), S (*e)()> class dynamic_segtree {
public:
    dynamic_segtree(size_t n) : n(n), root(nullptr) {}

    void set(size_t p, S x) {
        assert(p < n);
        set(root, 0, n, p, x);
    }

    S get(size_t p) const {
        assert(p < n);
        return get(root, 0, n, p);
    }

    S prod(size_t l, size_t r) const {
        assert(l <= r && r <= n);
        return prod(root, 0, n, l, r);
    }

    S all_prod() const { return root ? root->product : e(); }

    void reset(size_t l, size_t r) {
        assert(l <= r && r <= n);
        return reset(root, 0, n, l, r);
    }

    template <bool (*f)(S)> size_t max_right(size_t l) const {
        return max_right(l, [](S x) { return f(x); });
    }

    template <class F> size_t max_right(size_t l, const F& f) const {
        assert(l <= n);
        S product = e();
        return max_right(root, 0, n, l, f, product);
    }

private:
    struct node;
    using node_ptr = std::unique_ptr<node>;

    struct node {
        size_t index;
        S value, product;
        node_ptr left, right;

        node(size_t index, S value)
            : index(index),
              value(value),
              product(value),
              left(nullptr),
              right(nullptr) {}

        void update() {
            product = op(op(left ? left->product : e(), value),
                         right ? right->product : e());
        }
    };

    const size_t n;
    node_ptr root;

    void set(node_ptr& t, size_t a, size_t b, size_t p, S x) const {
        if (!t) {
            t = std::make_unique<node>(p, x);
            return;
        }
        if (t->index == p) {
            t->value = x;
            t->update();
            return;
        }
        size_t c = (a + b) >> 1;
        if (p < c) {
            if (t->index < p) std::swap(t->index, p), std::swap(t->value, x);
            set(t->left, a, c, p, x);
        } else {
            if (p < t->index) std::swap(p, t->index), std::swap(x, t->value);
            set(t->right, c, b, p, x);
        }
        t->update();
    }

    S get(const node_ptr& t, size_t a, size_t b, size_t p) const {
        if (!t) return e();
        if (t->index == p) return t->value;
        size_t c = (a + b) >> 1;
        if (p < c) return get(t->left, a, c, p);
        else return get(t->right, c, b, p);
    }

    S prod(const node_ptr& t, size_t a, size_t b, size_t l, size_t r) const {
        if (!t || b <= l || r <= a) return e();
        if (l <= a && b <= r) return t->product;
        size_t c = (a + b) >> 1;
        S result = prod(t->left, a, c, l, r);
        if (l <= t->index && t->index < r) result = op(result, t->value);
        return op(result, prod(t->right, c, b, l, r));
    }

    void reset(node_ptr& t, size_t a, size_t b, size_t l, size_t r) const {
        if (!t || b <= l || r <= a) return;
        if (l <= a && b <= r) {
            t.reset();
            return;
        }
        size_t c = (a + b) >> 1;
        reset(t->left, a, c, l, r);
        reset(t->right, c, b, l, r);
        t->update();
    }

    template <class F>
    size_t max_right(const node_ptr& t, size_t a, size_t b,
                     size_t l, const F& f, S& product) const {
        if (!t || b <= l) return n;
        if (f(op(product, t->product))) {
            product = op(product, t->product);
            return n;
        }
        size_t c = (a + b) >> 1;
        size_t result = max_right(t->left, a, c, l, f, product);
        if (result != n) return result;
        if (l <= t->index) {
            product = op(product, t->value);
            if (!f(product)) return t->index;
        }
        return max_right(t->right, c, b, l, f, product);
    }
};

struct S {
    ll sum, cnt;
};
S op(S a, S b) {
    return S{a.sum + b.sum, a.cnt + b.cnt};
}
S e() {
    return S{0, 0};
}
ll n, k; 
// bool f(S v, ll i) { 
//     return (v.sum + (n - v.cnt) * mid) / k < mid;
// }

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    ll N = 1LL << 50;
    dynamic_segtree<S, op, e> seg(N);
    cin >> n >> k;
    vector<ll> a(n);
    rep(i, n) {
        cin >> a[i];
        auto [x, y] = seg.get(a[i]);
        seg.set(a[i], S{x + a[i], y + 1});
    }
    int q; cin >> q;
    ll ans = 0;
    rep(i, q) {
        ll x, y; cin >> x >> y;
        x = (ans ^ x) % n;
        {
            auto [sum, cnt] = seg.get(a[x]);
            seg.set(a[x], S{sum - a[x], cnt - 1});
        }{
            a[x] += y;
            auto [sum, cnt] = seg.get(a[x]);
            seg.set(a[x], S{sum + a[x], cnt + 1});
        }
        ll le = 0, ri = (1LL << 50);
        while(ri - le > 1) {
            ll mid = (ri + le) / 2;
            auto [sum, cnt] = (mid >= N ? seg.all_prod() : seg.prod(0, mid));
            if((sum + (n - cnt) * mid) / k >= mid) le = mid;
            else ri = mid;
        }
        ans = le;
        // ans = seg.max_right<f>(0);
        cout << ans << '\n';
    }
    return 0;
}
