//#region algoTools
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
    T r = l%2 + u%2 + 2;
    return mid + r/2 - 1;
}

// for list structures use as function list.operator[] and start = 0
// returns the number of elements which are strict smaller/larger than val
// otherwise returns the smallest index for which f(idx) >=/<= val and start+length if this index does not exist
template <typename T>
long long binSearchDisc(const T &val, const std::function<T (long long)> &f, const unsigned long long &length, const long long &start = 0, bool increasing = true){
    long long l = start - 1;
    long long u = start + length;
    if(increasing){
        while(u>l+1){
            long long mid = middle(l,u);
            if(f(mid)<val)
                l=mid;
            else
                u=mid;
        }
    } else {
        while(u>l+1){
            long long mid = middle(l,u);
            if(f(mid)>val)
                l=mid;
            else
                u=mid;
        }
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
        return binSearchDisc<T>(thresh, [&](ll idx){ return this->get_sort(idx); }, argsorted.size());
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
        foreach(idx_iter, idxs){
            cur_values.pb(values[dimension][*idx_iter]);
        }
        v(ll) cur_argsorted = argsort(cur_values);
        foreach(cur_arg_idx_it, cur_argsorted){
            argsorted.pb(idxs[*cur_arg_idx_it]);
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
                v(ll) cur_result_idxs = subtrees[*subtree_idx].get_range(rest_range_l, rest_range_u);
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
                ll cur_result = subtrees[*subtree_idx].get_range_count(rest_range_l, rest_range_u);
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

} // namespace algoTools
using namespace algoTools;
//#endregion algoTools
