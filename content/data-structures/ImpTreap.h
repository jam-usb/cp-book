/**
 * Author: Bomba de tenedores
 * Description: Implicit treap
*/

struct node{
    int prior, sz;
    ll val, sum, lzy;
    node *l, *r;
    node(int v) : prior(rand()), sz(1), val(v), 
                    sum(v), lzy(0), l(0), r(0) {}
};
typedef node* pnode;
int sz(pnode t) { return t ? t->sz : 0; }
ll sum(pnode t) { return t ? t->sum : 0; }
void push(pnode t){
    if(!t || !t->lzy) return;
    t->val += t->lzy;
    t->sum += t->lzy*sz(t);
    if(t->l) t->l->lzy += t->lzy;
    if(t->r) t->r->lzy += t->lzy;
    t->lzy = 0;
}
void upd(pnode t){
    if(!t) return;
    t->sz = 1 + sz(t->l) + sz(t->r);
    push(t->l); push(t->r);
    t->sum = t->val + sum(t->l) + sum(t->r);
}
// Element in position pos goes in r
void split(pnode t, pnode &l, pnode &r, int pos, int add = 0){
    if(!t) return void(l = r = 0);
    push(t);
    int cur = add + sz(t->l);
    if(cur < pos) split(t->r, t->r, r, pos, cur+1), l = t;
    else split(t->l, l, t->l, pos, add), r = t;
    upd(t);
}
void merge(pnode &t, pnode l, pnode r){
    push(l); push(r);
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    upd(t);
}
ll queryRange(pnode t, int l, int r){
    pnode L, M, R;
    split(t, M, R, r);
    split(M, L, M, l);
    ll ans = M->sum;
    merge(t, L, M);
    merge(t, t, R);
    return ans;
}
void updateRange(pnode t, int l, int r, ll val){
    pnode L, M, R;
    split(t, M, R, r);
    split(M, L, M, l);
    M->lzy += val;
    merge(t, L, M);
    merge(t, t, R);
}
void eraseTree(pnode &t){
    if(!t) return;
    eraseTree(t->l);
    eraseTree(t->r);
    delete t;
    t = 0;
}