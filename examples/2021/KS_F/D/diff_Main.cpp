diff --git a/CodeJam/Main.cpp b/examples/2021/KS_F/D/Main.cpp
index 00aa56c..fb82813 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_F/D/Main.cpp
@@ -1544,11 +1544,67 @@ void init(){
     cin >> T;
 }
 
+ll N, M, K;
+ll Li[15], Ri[15], Ai[15];
+bool adj[15][15];
+
 void readInput(){
+    cin >> N >> M >> K;
+    forn(i, N){
+        cin >> Li[i] >> Ri[i] >> Ai[i];
+    }
+    fill_n(adj[0], 15*15, 0);
+    forn(i, M){
+        ll Xi, Yi;
+        cin >> Xi >> Yi;
+        adj[Xi][Yi] = true;
+        adj[Yi][Xi] = true;
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll states[1<<15] = {};
+    states[0] = 1;
+    ll pointsums[1<<15] = {};
+    fornn(nvis, 1, N+1){
+        v(bool) vis(N, false);
+        forn(i, nvis){
+            vis[i] = true;
+        }
+        sort(all(vis));
+        do {
+            ll id = 0;
+            forn(i, N){
+                if(vis[i]){
+                    id += (1<<i);
+                }
+            }
+            forn(i, N){
+                if(vis[i]) pointsums[id] += Ai[i];
+            }
+            forn(i, N){
+                if(!vis[i]) continue;
+                ll previd = id ^ (1<<i);
+                bool conn = false;
+                forn(j, N){
+                    if(adj[i][j] && vis[j]) {
+                        conn = true;
+                        break;
+                    }
+                }
+                if(previd == 0 || (conn && Li[i] <= pointsums[previd] && pointsums[previd] <= Ri[i])){
+                    states[id] += states[previd];
+                }
+            }
+        } while(next_permutation(all(vis)));
+
+    }
+
+    forn(i, 1<<N){
+        if(pointsums[i] == K) result += states[i];
+    }
 }
 
 } // namespace task
