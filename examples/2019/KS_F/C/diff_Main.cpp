diff --git a/CodeJam/Main.cpp b/examples/2019/KS_F/C/Main.cpp
index 6e1211d..14b9029 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_F/C/Main.cpp
@@ -1065,11 +1065,108 @@ void init(){
     cin >> T;
 }
 
+ll V;
+v(ll) Bi;
+v(unordered_set<ll>) neighbors;
+v(v(ll)) childs;
+v(ll) parent;
+
+void traverse_tree(ll cur_par, ll cur_node){
+    if(cur_par >= 0){
+        lassert(neighbors[cur_node].count(cur_par), "neighbors of cur has not parent");
+        parent[cur_node] = cur_par;
+        neighbors[cur_node].erase(cur_par);
+        childs[cur_node] = v(ll)(all(neighbors[cur_node]));
+    } else{
+        childs[cur_node] = v(ll)(all(neighbors[cur_node]));
+    }
+    foreach(child_node, childs[cur_node]){
+        traverse_tree(cur_node, child_node);
+    }
+}
+
+v(ll) maxBeautyHash;
+
 void readInput(){
+    cin >> V;
+    maxBeautyHash.cl;
+    maxBeautyHash.resize(4 * V, -INF);
+    Bi.cl;
+    forn(i, V){
+        ll t;
+        cin >> t;
+        Bi.pb(t);
+    }
+    childs.cl;
+    parent.cl;
+    neighbors.cl;
+    childs.resize(V);
+    neighbors.resize(V);
+    parent.resize(V, -1);
+    forn(i, V-1){
+        ll s, e;
+        cin >> s >> e;
+        s--;
+        e--;
+        neighbors[s].insert(e);
+        neighbors[e].insert(s);
+    }
+    foreach(neigh, neighbors)
+        llog(neigh);
+    llog();
+    traverse_tree(-1, 0);
+}
+
+ll hashargs(ll cur_node, bool one, bool two){
+    ll boolnbr = one * 2 + two;
+    return cur_node + boolnbr * V;
+}
+
+ll maxBeauty(ll cur_node, bool par_has_lh, bool cur_has_lh){
+    lassert(cur_node >= 0, "too small cur node id");
+    lassert(cur_node < V, "too large cur node id");
+    ll hashargnum = hashargs(cur_node, par_has_lh, cur_has_lh);
+    if(maxBeautyHash[hashargnum] != -INF){
+        return maxBeautyHash[hashargnum];
+    }
+    if(cur_has_lh){
+        ll r = Bi[cur_node];
+        foreach(child_node, childs[cur_node]){
+            r += max(maxBeauty(child_node, true, true), maxBeauty(child_node, true, false));
+        }
+        maxBeautyHash[hashargnum] = r;
+        return maxBeautyHash[hashargnum];
+    }
+    if(par_has_lh){
+        ll r = Bi[cur_node];
+        foreach(child_node, childs[cur_node]){
+            r += max(maxBeauty(child_node, false, true), maxBeauty(child_node, false, false));
+        }
+        maxBeautyHash[hashargnum] = r;
+        return maxBeautyHash[hashargnum];
+    }
+    // neither par nor cur has lighthouse
+    // compute two cases: cur is lit by child, or cur is not lit
+    ll r_notlit = 0;
+    ll best_addable_at_least_one_lh_child = -INF;
+    foreach(child_node, childs[cur_node]){
+        ll curval_child_lh = maxBeauty(child_node, false, true);
+        ll curval_child_nolh = maxBeauty(child_node, false, false);
+        best_addable_at_least_one_lh_child = max(
+            best_addable_at_least_one_lh_child + max(curval_child_lh, curval_child_nolh),
+            r_notlit + curval_child_lh
+        );
+        r_notlit += curval_child_nolh;
+    }
+    ll r_lit = Bi[cur_node] + best_addable_at_least_one_lh_child;
+    r_lit *= (childs[cur_node].sz > 0);
+    maxBeautyHash[hashargnum] = max(r_lit, r_notlit);
+    return maxBeautyHash[hashargnum];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = max(maxBeauty(0, false, true), maxBeauty(0, false, false));
 }
 
 } // namespace task
