diff --git a/CodeJam/Main.cpp b/examples/2016/Round2/D/Main.cpp
index fad3e96..865e63c 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2016/Round2/D/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1025,11 +1025,93 @@ void init(){
     cin >> T;
 }
 
+ll N, initial;
+v(s(ll)) adjacency_list;
+
 void readInput(){
+    cin >> N;
+    initial = 0;
+    adjacency_list.assign(2*N, s(ll)());
+    forn(r, N){
+        str line;
+        cin >> line;
+        forn(c, N){
+            if(line[c]=='1'){
+                initial++;
+                adjacency_list[r].insert(c+N);
+                adjacency_list[c+N].insert(r);
+            }
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) ids = strongly_connected_components_tarjan(adjacency_list);
+    llog("scc ids", ids);
+    d(cell, ll) pair_counts;
+    forn(idx, 2*N){
+        cell cur_pair(0, 0);
+        forn(node, 2*N){
+            if(ids[node]==idx){
+                if(node<N){
+                    cur_pair += cell(1, 0);
+                } else
+                    cur_pair += cell(0, 1);
+            }
+        }
+        if(norm(cur_pair) > 0)
+            pair_counts[cur_pair]++;
+    }
+    llog("found pairs with counts");
+    ll nbr_combos=1;
+    v(ll) mults;
+    v(cell) pair_list;
+    foreach(pair_c, pair_counts){
+        llog("pair", pair_c.st, "count", pair_c.nd);
+        mults.pb(nbr_combos);
+        pair_list.pb(pair_c.st);
+        nbr_combos *= pair_c.nd + 1;
+    }
+    mults.pb(nbr_combos);
+
+    v(v(ll)) dp(nbr_combos, v(ll)(N+1, INF));
+    dp[nbr_combos-1][N] = N * N;
+    forn(i, nbr_combos) dp[i][0] = 0;
+
+    forn(cbi, nbr_combos){
+        v(ll) combo_pair_counts;
+        cell sum(0, 0);
+        forn(i, mults.sz - 1){
+            combo_pair_counts.pb((cbi%mults[i+1])/mults[i]);
+            sum += pair_list[i] * combo_pair_counts.bk;
+        }
+        llog("looking at current combo", combo_pair_counts);
+        fore(t, 0, N){
+            if(dp[cbi][t] == INF) continue;
+            llog("balanced sum t", t);
+            ll add_id=-1;
+            foreach(pair_c, pair_counts){
+                add_id++;
+                ll cur_combo_pair_count = (cbi % mults[add_id+1]) / mults[add_id];
+                lassert(cur_combo_pair_count == combo_pair_counts[add_id], "something terribly happened");
+                if(cur_combo_pair_count == pair_c.nd) continue;
+                ll ncbi = cbi + mults[add_id];
+
+                cell rest = sum - cell(t, t) + pair_c.st;
+                if(rest.x < 0 || rest.y < 0) continue;
+                llog("trying to add pair id", add_id);
+                llog("new rest of unbalanced is", rest);
+                dp[ncbi][t] = min(dp[cbi][t],dp[ncbi][t]);
+                llog("minimal squared pair sums found for new combo", ncbi, "and balanced t", t, "is", dp[ncbi][t]);
+                if(rest.x == rest.y){
+                    dp[ncbi][t+rest.x] = min(dp[ncbi][t+rest.x], dp[cbi][t] + rest.x * rest.x);
+                    llog("minimal squared pair sums found for new combo", ncbi, "and balanced t", t+rest.x, "is", dp[ncbi][t+rest.x]);
+                }
+            }
+        }
+    }
+    result = dp.bk.bk - initial;
 }
 
 } // namespace task
