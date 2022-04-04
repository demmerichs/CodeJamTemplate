diff --git a/CodeJam/Main.cpp b/examples/2019/Round2/D/Main.cpp
index 6e1211d..778e285 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round2/D/Main.cpp
@@ -1,6 +1,6 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
-#define DEFAULT_VAL "IMPOSSIBLE"
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result == INF
+#define DEFAULT_VAL "UNBOUNDED"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
@@ -1065,11 +1065,169 @@ void init(){
     cin >> T;
 }
 
+ll infmodplus(ll a, ll b){
+    if(a==-1 && b == -1) return -1;
+    if(a==INF || b == INF) return INF;
+    if(a==-1 || b==-1) return max(a,b);
+    return mplusOp(a, b);
+}
+
+ll infmodmul(ll a, ll b){
+    if(a==-1 || b == -1) return -1;
+    if(a==INF || b == INF) return INF;
+    return mmulOp(a,b);
+}
+
+
+ll M;
+v(ll) Gi;
+v(d(ll, ll)) formula;
+v(d(ll, ll)) transpose_formula;
+v(ll) scc;
+v(ll) metals_alive;
+
+void transpose_reachable(ll start, v(bool) &reached){
+    foreach(produced_by, transpose_formula[start]){
+        if(reached[produced_by.st]) continue;
+        reached[produced_by.st] = true;
+        transpose_reachable(produced_by.st, reached);
+    }
+}
+
+void metal_alive(ll m){
+    if(metals_alive[m] != 0) return;
+    if(Gi[m] > 0){
+        metals_alive[m] = 1;
+        return;
+    }
+    metals_alive[m] = -2;
+    bool any_unknown = false;
+    foreach(producer, transpose_formula[m]){
+        metal_alive(producer.st);
+        if(metals_alive[producer.st] == 1){
+            metals_alive[m] = 1;
+            return;
+        } else if(metals_alive[producer.st] == -2 || metals_alive[producer.st] == 0){
+            any_unknown = true;
+        }
+    }
+    if(any_unknown)
+        metals_alive[m] = 0;
+    else
+        metals_alive[m] = -1;
+}
+
+void clean_graph_from_dead_metals(){
+    forn(m, M){
+        if(metals_alive[m] <= 0){
+            foreach(produced, formula[m]){
+                transpose_formula[produced.st].erase(m);
+            }
+            formula[m].cl;
+        }
+    }
+}
+
 void readInput(){
+    cin >> M;
+    Gi.cl;
+    formula.cl;
+    formula.resize(M);
+    transpose_formula.cl;
+    transpose_formula.resize(M);
+    v(s(ll)) adjacency_list(M);
+    forn(i, M){
+        ll s, t;
+        cin >> s >> t;
+        s--; t--;
+        formula[i][s] = 1;
+        formula[i][t] = 1;
+        adjacency_list[i].insert(s);
+        adjacency_list[i].insert(t);
+        transpose_formula[s][i] = 1;
+        transpose_formula[t][i] = 1;
+    }
+    forn(i, M){
+        ll t;
+        cin >> t;
+        Gi.pb(t);
+        if(t==0) Gi.bk--;
+    }
+    metals_alive.cl;
+    metals_alive.resize(M, 0);
+    forn(i, M){
+        metal_alive(i);
+    }
+    clean_graph_from_dead_metals();
+    scc = strongly_connected_components_tarjan(adjacency_list);
+    llog("scc", scc);
+}
+
+void dfs_stack_on_subgraph(ll start, const v(bool)& subgraph, v(ll) &stack, v(bool) &on_stack){
+    if(on_stack[start]) return;
+    foreach(produced, formula[start]){
+        if(!subgraph[produced.st]) continue;
+        dfs_stack_on_subgraph(produced.st, subgraph, stack, on_stack);
+    }
+    stack.pb(start);
+    on_stack[start] = true;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    if(metals_alive[0] <= 0){
+        llog("lead seems to be a dead metal");
+        result = 0;
+        return;
+    }
+    v(bool) can_produce_lead(M, false);
+    can_produce_lead[0] = true;
+    transpose_reachable(0, can_produce_lead);
+    llog("metals that can produce lead");
+    llog(can_produce_lead);
+
+    forn(i, M){
+        if(metals_alive[i] <= 0) continue;
+        lassert(formula[i].sz == 2, "formula[i].sz == 2");
+        ll v1 = formula[i].bn->st;
+        ll v2 = formula[i].rbegin()->st;
+        if(can_produce_lead[v1] && scc[v2] == scc[i]){
+            llog("a metal was found that can produce itself through scc and also produce lead", i);
+            result = INF;
+            return;
+        }
+        if(can_produce_lead[v2] && scc[v1] == scc[i]){
+            llog("a metal was found that can produce itself through scc and also produce lead", i);
+            result = INF;
+            return;
+        }
+    }
+    llog("no metal was found that can produce itself through scc and also lead");
+    llog("computing now finite amount of lead");
+    v(ll) order_of_compute_nbr_paths;
+    order_of_compute_nbr_paths.pb(0);
+    v(bool) already_in_order(M, false);
+    already_in_order[0] = true;
+    forn(i, M){
+        if(metals_alive[i] <= 0) continue;
+        if(!can_produce_lead[i]) continue;
+        if(already_in_order[i]) continue;
+        dfs_stack_on_subgraph(i, can_produce_lead, order_of_compute_nbr_paths, already_in_order);
+    }
+    llog("finished computing order");
+    llog(order_of_compute_nbr_paths);
+    llog(already_in_order);
+    lassert(order_of_compute_nbr_paths[0] == 0,"order_of_compute_nbr_paths[0] == 0");
+    v(ll) nbr_paths(M, -1);
+    nbr_paths[0] = 1;
+    order_of_compute_nbr_paths.erase(order_of_compute_nbr_paths.bn);
+    result = Gi[0];
+    foreach(i, order_of_compute_nbr_paths){
+        foreach(produced, formula[i]){
+            nbr_paths[i] = infmodplus(nbr_paths[i], nbr_paths[produced.st]);
+        }
+        result = infmodplus(result, infmodmul(nbr_paths[i], Gi[i]));
+    }
 }
 
 } // namespace task
