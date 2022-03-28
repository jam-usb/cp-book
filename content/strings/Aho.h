/**
 * Author: benq
 * Description: Aho-Corasick for fixed alphabet. For each prefix, 
    * stores link to max length suffix which is also a prefix.
 * Time: O(N\sum)
 */
struct ACfixed { // fixed alphabet
    static const int ASZ = 52;
    struct node { array<int, ASZ> to; int link; int out; bool leaf = false; vi inds;};
    vector<node> d = {{}};
    int add(string s, int ind) { // add word
        int v = 0;
        for (auto C : s) {
            if ((int)C >= 97) C -= 6; // por si es [A..Z] + [a..z]
            int c = C - 'A';
            if (!d[v].to[c]) d[v].to[c] = sz(d), d.emplace_back();
            v = d[v].to[c];
        }
        d[v].inds.pb(ind);
        d[v].leaf = true;
        return v;
    }
    void init() { // generate links
        d[0].link = -1;
        d[0].out = -1;
        queue<int> q; q.push(0);
        while (sz(q)) {
            int v = q.front(); q.pop();
            FOR(c, 0, ASZ) {
                int u = d[v].to[c]; if (!u) continue;
                d[u].link = d[v].link == -1 ? 0 : d[d[v].link].to[c];
                q.push(u);
            }
            if (v) FOR(c, 0, ASZ) if (!d[v].to[c])
                    d[v].to[c] = d[d[v].link].to[c];
            if (v) {
                if (d[d[v].link].leaf) d[v].out = d[v].link;
                else d[v].out = d[d[v].link].out;
            }
        }
    }
};