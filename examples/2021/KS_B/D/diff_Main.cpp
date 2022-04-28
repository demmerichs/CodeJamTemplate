diff --git a/CodeJam/Main.cpp b/examples/2021/KS_B/D/Main.cpp
index a7f0d62..c07621d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_B/D/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1501,11 +1501,71 @@ void init(){
     cin >> T;
 }
 
+const ll LOG2MAXL = 20;
+ll N, Q;
+v(d(ll, p(ll, ll))) edges;
+v(ll) Cj, Wj;
+d(ll, d(ll, s(ll))) queries;
+
 void readInput(){
+    cin >> N >> Q;
+    ll X,Y,Li, Ai;
+    edges.cl;
+    edges.resize(N);
+    forn(i, N-1){
+        cin >> X >> Y >> Li >> Ai;
+        X--;
+        Y--;
+        edges[X][Y] = mp(Li, Ai);
+        edges[Y][X] = mp(Li, Ai);
+    }
+    Cj.resize(Q);
+    Wj.resize(Q);
+    queries.cl;
+    forn(i, Q){
+        cin >> Cj[i] >> Wj[i];
+        Cj[i]--;
+        queries[Cj[i]][Wj[i]].insert(i);
+    }
+}
+
+void dfs(ll node, d(ll, v(ll)) &Li_gcd_Ai){
+    foreach(q, queries[node]){
+        ll curanswer = 0;
+        forn(i, LOG2MAXL){
+            ll curw = ((q.st+1)>>i)-1;
+            ll tree_idx = curw + (1<<LOG2MAXL) - (1<<(LOG2MAXL-i));
+            if(Li_gcd_Ai.count(tree_idx))
+                curanswer = gcd(curanswer, Li_gcd_Ai[tree_idx].bk);
+        }
+        foreach(idx, q.nd)
+            result[idx] = curanswer;
+    }
+    foreach(edge, edges[node]){
+        edges[edge.st].erase(node);
+        ll curLi = edge.nd.st;
+        ll Ai = edge.nd.nd;
+        forn(i, LOG2MAXL){
+            ll curcurLi = curLi>>i;
+            ll tree_idx = curcurLi + (1<<LOG2MAXL) - (1<<(LOG2MAXL-i));
+            ll prev_val = dget<ll, v(ll)>(Li_gcd_Ai, tree_idx, {0}).bk;
+            Li_gcd_Ai[tree_idx].pb(gcd(Ai, prev_val));
+        }
+        dfs(edge.st, Li_gcd_Ai);
+        forn(i, LOG2MAXL){
+            ll curcurLi = curLi>>i;
+            ll tree_idx = curcurLi + (1<<LOG2MAXL) - (1<<(LOG2MAXL-i));
+            Li_gcd_Ai[tree_idx].popb;
+            if(Li_gcd_Ai[tree_idx].sz == 0) Li_gcd_Ai.erase(tree_idx);
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result.resize(Q);
+    d(ll,v(ll)) dummyLi_gcd_Ai;
+    dfs(0, dummyLi_gcd_Ai);
 }
 
 } // namespace task
