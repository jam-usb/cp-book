/**
 * Author: Marcos Lerones (adapted from Benq)
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
*/

using Treap = struct TNode*; // int and pool of nodes for speed
struct TNode {
    int val, pri; Treap c[2]; // essential
    int sz; ll sum; // range queries
    bool flip = 0; // lazy update
    TNode(int _val) {
        val = sum = _val; pri = rng(); 
        sz = 1; c[0] = c[1] = nullptr;
    }
    ~TNode() { FOR(i,0,2) delete c[i]; }
};

int tsz(Treap t) { return t ? t->sz : 0; }
ll tsum(Treap t) { return t ? t->sum : 0; }

Treap prop(Treap t) { // lazy propagation
    if (!t || !t->flip) return t;
    swap(t->c[0], t->c[1]);
    t->flip = 0; FOR(i,0,2) if (t->c[i]) t->c[i]->flip ^= 1;
    return t;
}

Treap upd(Treap t) { // modify here for different queries
    if (!t) return t;
    Treap a = t->c[0], b = t->c[1];
    assert(!t->flip); prop(a), prop(b);
    t->sz = 1 + tsz(a) + tsz(b);
    t->sum = t->val + tsum(a) + tsum(b);
    return t;
}

void tour(Treap t, vi &v) {
    if (!t) return;
    prop(t); tour(t->c[0], v); v.pb(t->val); tour(t->c[1], v);
}

pair<Treap, Treap> split(Treap t, int v) { // >= v goes right
    if(!t) return {t, t};
    prop(t);
    if (t->val >= v) {
        auto [a, b] = split(t->c[0], v); t->c[0] = b;
        return {a, upd(t)};
    }
    else {
        auto [a, b] = split(t->c[1], v); t->c[1] = a;
        return {upd(t), b};
    }
}

pair<Treap, Treap> splitsz(Treap t, int k) { // k nodes go left
    if(!t) return {t, t};
    prop(t);
    if (tsz(t->c[0]) >= k) {
        auto [a, b] = splitsz(t->c[0], k); t->c[0] = b;
        return {a, upd(t)};
    }
    else {
        auto [a, b] = splitsz(t->c[1], k-tsz(t->c[0])-1); t->c[1] = a;
        return {upd(t), b};
    }
}

Treap merge(Treap l, Treap r) { // keys in l < keys in r 
    if (!l || !r) return l ? l : r;
    prop(l), prop(r); Treap t;
    if (l->pri > r->pri) l->c[1] = merge(l->c[1], r), t = l;
    else r->c[0] = merge(l, r->c[0]), t = r;
    return upd(t);
}

Treap ins(Treap t, int v) { // insert v (if not alredy present)
    auto [a, b] = split(t, v); auto [c, d] = split(b, v+1);
    return merge(a, merge(new TNode(v), d));
}

Treap del(Treap t, int v) { // delete v (deletes all  v)
    auto [a, b] = split(t, v); auto [c, d] = split(b, v+1);
    return merge(a, d);
}

// Treap del(Treap t, int v) { // delete v (faster, only one)
//     if (!t) return t;
//     if (t->val == v) return merge(t->c[0], t->c[1]);
//     if (v < t->val) t->c[0] = del(t->c[0], v);
//     else t->c[1] = del(t->c[1], v);
//     return upd(t);
// }
