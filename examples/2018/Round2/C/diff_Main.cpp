diff --git a/CodeJam/Main.cpp b/examples/2018/Round2/C/Main.cpp
index d8e2c23..b26b94b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round2/C/Main.cpp
@@ -3,7 +3,7 @@
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1010,11 +1010,39 @@ namespace task {
 void init(){
 }
 
+ll N;
+v(s(cell)) pos;
+
 void readInput(){
+    cin >> N;
+    pos.cl;
+    pos.resize(2*N);
+    forn(r, N){
+        forn(c, N){
+            ll t;
+            cin >> t;
+            if(t>0) t--;
+            else t+=2*N;
+            pos[t].insert(cell(r,c));
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    v(v(bool)) connected(N, v(bool)(N, false));
+    forn(i, 2*N){
+        foreach(p, pos[i]){
+            connected[p.x][p.y] = true;
+        }
+        v(ll) matched_rows, matched_cols;
+        ull count = maximal_bipartite_matching(connected, matched_rows, matched_cols);
+        foreach(p, pos[i]){
+            connected[p.x][p.y] = false;
+        }
+        result += pos[i].sz - count;
+    }
 }
 
 } // namespace task
