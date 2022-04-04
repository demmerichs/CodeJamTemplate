#pragma region algoTools
/* TODO write doc
 */
namespace algoTools{

// does an argsort (increasing values) over the provided vector
template <typename T>
v(long long int) argsort(const v(T) &v) {
    // initialize original index locations
    v(long long int) idxs(v.size());
    std::iota(idxs.begin(), idxs.end(), 0);

    // sort indexes based on comparing values in v
    std::sort(idxs.begin(), idxs.end(),
              [&v](long long int i1, long long int i2) {return v[i1] < v[i2];});

    return idxs;
}

// returns the average of 2 values without generating overflow and always rounding down
template <typename T>
T middle(T l, T u){
    T mid = (l/2)+(u/2);
    T r = ((l-mid) + (u-mid))/2;
    return mid + r;
}

template <typename Tidx, typename Tval>
Tidx lower_bound_function(const Tval &val, const std::function<Tval (Tidx)> &f, const Tidx &length, const Tidx &start = 0, const Tidx &resolution = 1){
    Tidx l = start - resolution;
    Tidx u = start + length;
    while(u>l+resolution){
        Tidx mid = middle(l, u);
        if(f(mid) >= val) u=mid;
        else l=mid;
    }
    return u;
}

template <typename Tidx, typename Tval>
Tidx upper_bound_function(const Tval &val, const std::function<Tval (Tidx)> &f, const Tidx &length, const Tidx &start = 0, const Tidx &resolution = 1){
    Tidx l = start - resolution;
    Tidx u = start + length;
    while(u>l+resolution){
        Tidx mid = middle(l, u);
        if(f(mid) > val) u=mid;
        else l=mid;
    }
    return u;
}


template <typename T>
class BalancedRangeTree{
private:
    const v(v(T)) &values;
    ll dimension;
    v(ll) argsorted;
    unsigned short max_depth;
    v(BalancedRangeTree<T>) subtrees;

    T get_sort(ll idx){
        return values[dimension][argsorted[idx]];
    }

    ll get_nbr_values_smaller_thresh(T thresh){
        return lower_bound_function<ll,T>(thresh, [&](ll idx){ return this->get_sort(idx); }, argsorted.size());
    }

    v(ll) get_tree_path_idxs(ll leaf_idx){
        if(leaf_idx == -1){
            return v(ll)(max_depth, -1);
        }
        lassert(0 <= leaf_idx, "leaf idx has invalid negative value");
        lassert(leaf_idx <= 1<<(max_depth-1), "leaf idx has too large value");
        v(ll) result;
        forn(d, max_depth){
            result.pb(leaf_idx >> (max_depth-d-1));
        }
        return result;
    }

    static ll tree_to_vec_idx(unsigned int level, ll idx_in_level){
        lassert(idx_in_level < 1<<level, "invalid tree idx");
        return (1<<level) - 1 + idx_in_level;
    }

    v(ll) get_idxs_of_subtrees_in_idx_range(ll low_idx, ll up_idx){
        v(ll) low_tree_path = get_tree_path_idxs(low_idx);
        v(ll) up_tree_path = get_tree_path_idxs(up_idx);
        v(ll) subtree_idxs;
        forn(d, max_depth){
            if(low_tree_path[d] % 2 == 0){ // went left in tree so right is possible
                if(low_tree_path[d] + 1 < up_tree_path[d]){
                    ll st_idx = tree_to_vec_idx(d, low_tree_path[d] + 1);
                    subtree_idxs.pb(st_idx);
                }
            }
            if(up_tree_path[d] % 2 == 1){ // went right in tree so left is possible
                if(up_tree_path[d] - 1 > low_tree_path[d]){
                    ll st_idx = tree_to_vec_idx(d, up_tree_path[d] - 1);
                    subtree_idxs.pb(st_idx);
                }
            }
        }
        return subtree_idxs;
    }

    void create_subtrees(){
        max_depth = argsorted.size() >= 4 ? 2 + log2ll(argsorted.size() -1) : argsorted.size();

        if(values.size()-1 > dimension){
            forn(d, max_depth){
                forn(i, 1<<d){
                    v(ll) subtree_idxs;
                    fornn(j, i*(1<<(max_depth-d-1)), std::min<ll>(argsorted.size(), (i+1)*(1<<(max_depth-d-1)))){
                        subtree_idxs.pb(argsorted[j]);
                    }
                    subtrees.pb(BalancedRangeTree(values, dimension+1, subtree_idxs));
                }
            }
        }

        lassert((subtrees.size()>=1) == (dimension+1 != values.size()), "last dimension has subtrees or non_last_dimension has no subtrees");
    }

public:
    BalancedRangeTree<T>(const v(v(T)) &values, ll dimension, v(ll) idxs): values(values), dimension(dimension){
        v(T) cur_values;
        foreach(idx, idxs){
            cur_values.pb(values[dimension][idx]);
        }
        v(ll) cur_argsorted = argsort(cur_values);
        foreach(cur_arg_idx, cur_argsorted){
            argsorted.pb(idxs[cur_arg_idx]);
        }

        create_subtrees();
    }

    BalancedRangeTree<T>(const v(v(T)) &values): values(values), dimension(0){
        argsorted = argsort(values[0]);

        create_subtrees();
    }

    v(ll) get_range(v(T) l, v(T) u){
        if(argsorted.size() == 0)
            return v(ll)();
        ll low_idx = get_nbr_values_smaller_thresh(l[0]);
        ll up_idx = get_nbr_values_smaller_thresh(u[0]);
        v(ll) result;
        if(dimension + 1 < values.size()){
            v(T) rest_range_l(msel(l, 1, l.size()));
            v(T) rest_range_u(msel(u, 1, u.size()));
            v(ll) idxs_of_subtrees_in_range = get_idxs_of_subtrees_in_idx_range(low_idx-1, up_idx == argsorted.size() ? 1<<(max_depth-1):up_idx);
            foreach(subtree_idx, idxs_of_subtrees_in_range){
                v(ll) cur_result_idxs = subtrees[subtree_idx].get_range(rest_range_l, rest_range_u);
                result.insert(result.ed, all(cur_result_idxs));
            }
        } else {
            result.insert(result.ed, msel(argsorted, low_idx, up_idx));
        }
        return result;
    }

    ll get_range_count(v(T) l, v(T) u){
        if(argsorted.size() == 0)
            return 0;
        ll low_idx = get_nbr_values_smaller_thresh(l[0]);
        ll up_idx = get_nbr_values_smaller_thresh(u[0]);
        ll result = 0;
        if(dimension + 1 < values.size()){
            v(T) rest_range_l(msel(l, 1, l.size()));
            v(T) rest_range_u(msel(u, 1, u.size()));
            v(ll) idxs_of_subtrees_in_range = get_idxs_of_subtrees_in_idx_range(low_idx-1, up_idx == argsorted.size() ? 1<<(max_depth-1):up_idx);
            foreach(subtree_idx, idxs_of_subtrees_in_range){
                ll cur_result = subtrees[subtree_idx].get_range_count(rest_range_l, rest_range_u);
                result += cur_result;
            }
        } else {
            result += up_idx - low_idx;
        }
        return result;
    }
};

bool find_match(unsigned long long r, const std::vector<std::vector<bool> > &connected, std::vector<long long> &matched_rows, std::vector<long long> &matched_cols, std::vector<bool> &seen) {
    for(unsigned long long c = 0; c < connected[r].size(); c++){
        if(connected[r][c] && !seen[c]){
            seen[c] = true;
            if(matched_cols[c] < 0 || find_match(matched_cols[c], connected, matched_rows, matched_cols, seen)){
                matched_rows[r] = c;
                matched_cols[c] = r;
                return true;
            }
        }
    }
    return false;
}

unsigned long long maximal_bipartite_matching(const std::vector<std::vector<bool> > &connected, std::vector<long long> &matched_rows, std::vector<long long> &matched_cols) {
    matched_rows = std::vector<long long>(connected.size(), -1);
    matched_cols = std::vector<long long>(connected[0].size(), -1);

    unsigned long long num_matches = 0;
    for(unsigned long long r = 0; r < connected.size(); r++){
        std::vector<bool> seen(connected[0].size(), false);
        if(find_match(r, connected, matched_rows, matched_cols, seen)) num_matches++;
    }
    return num_matches;
}

template <typename T>
class RangeMinMaxTable{
private:
    const bool query_min;
    const v(T) &values;
    v(v(ll)) lookup_idxs;

    bool comp(const T& lhs, const T& rhs){
        if(query_min) return lhs <= rhs;
        else return lhs >= rhs;
    }

    void create_lookup_table(){
        ll n = values.size();
        ll logn = log2ll(n);
        lookup_idxs.clear();
        lookup_idxs.resize(n);
        forn(i, n){
            lookup_idxs[i].push_back(i);
        }
        fornn(j, 1, logn+1){
            forn(i, n + 1 - (1<<j)){
                if(comp(values[lookup_idxs[i][j-1]], values[lookup_idxs[i+(1<<(j-1))][j-1]]))
                    lookup_idxs[i].push_back(lookup_idxs[i][j-1]);
                else
                    lookup_idxs[i].push_back(lookup_idxs[i + (1<<(j-1))][j-1]);
            }
        }
    }

public:
    RangeMinMaxTable<T>(const v(T) &values, const bool &query_min=true): values(values), query_min(query_min){
        create_lookup_table();
    }

    ll query(ll lower, ll upper){
        ll n = upper - lower;
        lassert(n>0, "invalid range max query");
        ll logn = log2ll(n);
        ll first = lookup_idxs[lower][logn];
        ll second = lookup_idxs[upper - (1<<logn)][logn];
        if(comp(values[first], values[second]))
            return first;
        return second;
    }
};

void strongly_connected_components_tarjan_recursive(
    const v(s(ll))& adjacency_list,
    v(ll) &discovered,
    v(ll) &lowest,
    v(bool) &on_stack,
    v(ll) &stack,
    ll &discover_counter,
    v(ll) &scc,
    ll next_to_discover
){
    discovered[next_to_discover] = discover_counter;
    lowest[next_to_discover] = discover_counter;
    on_stack[next_to_discover] = true;
    stack.pb(next_to_discover);
    discover_counter++;
    foreach(neigh, adjacency_list[next_to_discover]){
        if(discovered[neigh]==-1){
            strongly_connected_components_tarjan_recursive(
                adjacency_list, discovered, lowest, on_stack, stack, discover_counter, scc, neigh
            );
        }
        if(on_stack[neigh]){
            lowest[next_to_discover] = std::min(lowest[next_to_discover], lowest[neigh]);
        }
    }
    if(discovered[next_to_discover] == lowest[next_to_discover]){
        while(stack.bk != next_to_discover){
            scc[stack.bk] = discovered[next_to_discover];
            on_stack[stack.bk] = false;
            stack.popb;
        }
        scc[next_to_discover] = discovered[next_to_discover];
        on_stack[next_to_discover] = false;
        stack.popb;
    }
}

v(ll) strongly_connected_components_tarjan(v(s(ll)) adjacency_list){
    ll n = adjacency_list.sz;
    v(ll) discovered(n, -1), lowest(n, -1), stack;
    v(bool) on_stack(n, false);
    ll discover_counter = 0;
    v(ll) scc(n, -1);
    forn(i, n){
        if(discovered[i] >= 0) continue;
        strongly_connected_components_tarjan_recursive(
            adjacency_list, discovered, lowest, on_stack, stack, discover_counter, scc, i
        );
    }
    return scc;
}

} // namespace algoTools
using namespace algoTools;
#pragma endregion algoTools
