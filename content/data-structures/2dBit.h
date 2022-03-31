/**
 * Author: Bomba de tenedores
 * Description: 2d Bit data structure
*/

ll BIT[MAXR][MAXC];
void updBIT(int r, int c, ll val){
    r++, c++;
    for(; r < MAXR; r += r&-r)
        for(int cc = c; cc < MAXC; cc += cc&-cc)
            BIT[r][cc] += val;
}
ll sumBIT(int r, int c){
    r++, c++;
    ll ret = 0;
    for(; r; r -= r&-r)
        for(int cc = c; cc; cc -= cc&-cc)
            ret += BIT[r][cc];
    return ret;
}