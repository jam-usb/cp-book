/**
 * Author: bomba de tenedores + jesuswr
 * Description: 
 * Cada camino representa un substring.
 * Para calcular cuantas veces sale cada substring, inicalmente marcamos cnt = 1 en todos los nodos (no clonados)
 * y finalmente hacemos d[ d[v].link ].cnt += d[v]. cnt, en orden desde los caminos mas largos.
 * Para ver la cantidad de palabras diferentes seria un dp de cuantos caminos hay.
 * Si quieres la posicion en la que sale solo la guardas en el nodo a la hora de crearlo y clonarlo.
 * Time: O(n*ASZ)
 */
struct SUF_AUT {
    static const int ASZ = 26;
    struct node { int len, link; array<int, ASZ> to;};
    vector<node> d = {{}};
    int last;
    void init(string S) {
        last = d[0].len = 0;
        d[0].link = -1;
        d[0].to.fill(0);
        for (auto C : S) {
            int c = C - 'a', v = sz(d), p = last; // Be careful with mapping char to int
            d.emplace_back();
            d[v].len = d[last].len + 1;
            for (; p > -1 && !d[p].to[c]; p = d[p].link)
                d[p].to[c] = v;
            if (p == -1) {
                d[v].link = 0;
            }
            else {
                int q = d[p].to[c];
                if (d[p].len + 1 == d[q].len) {
                    d[v].link = q;
                }
                else {
                    int qq = sz(d);
                    d.emplace_back();
                    d[qq].len = d[p].len + 1;
                    d[qq].to = d[q].to;
                    d[qq].link = d[q].link;
                    d[v].link = d[q].link = qq;
                    for (; p > -1 && d[p].to[c] == q; p = d[p].link)
                        d[p].to[c] = qq;
                }
            }
            last = v;
        }
    }
};