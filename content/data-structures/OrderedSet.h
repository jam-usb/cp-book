/**
 * Author: Marcos Lerones
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * Time: O(\log N)
 */
#pragma once

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

void example() {
	OrderedSet<int> t, t2;
	t.insert(x);
	t.erase(x);
	t.order_of_key(x); // number of elements y in s that y < x
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
