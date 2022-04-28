diff --git a/CodeJam/Main.cpp b/examples/2022/Round1B/B/Main.cpp
index a7f0d62..7adc2b5 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1B/B/Main.cpp
@@ -1501,11 +1501,54 @@ void init(){
     cin >> T;
 }
 
+ll N, P;
+v(v(ll)) Xij;
+v(p(ll, ll)) Xminmax;
+
 void readInput(){
+    cin >> N >> P;
+    Xij.cl;
+    Xij.resize(N+1, v(ll)(P));
+    Xminmax.resize(N+1);
+    forn(j, P)
+        Xij[0][j] = 0;
+    fornn(i, 1, N+1)
+        forn(j, P)
+            cin >> Xij[i][j];
+    forn(i, N+1){
+        ll mini = Xij[i][0];
+        ll maxi = Xij[i][0];
+        forn(j, P){
+            mini = min(mini, Xij[i][j]);
+            maxi = max(maxi, Xij[i][j]);
+        }
+        Xminmax[i] = mp(mini, maxi);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+
+    v(ll) lastMinPresses(P, 0);
+
+    fornn(i, 1, N+1){
+        v(ll) curMinPresses(P, INF);
+        forn(j, P){
+            forn(k, P){
+                ll startX = Xij[i-1][j];
+                ll endX = Xij[i][k];
+                ll mini = min(Xminmax[i].st, startX);
+                ll maxi = max(Xminmax[i].nd, startX);
+                ll minPresses = 2*(maxi-mini) - abs(startX-endX);
+                curMinPresses[k] = min(curMinPresses[k], lastMinPresses[j] + minPresses);
+            }
+        }
+        lg(curMinPresses);
+        lastMinPresses = curMinPresses;
+    }
+
+    result = *min_element(all(lastMinPresses));
 }
 
 } // namespace task
