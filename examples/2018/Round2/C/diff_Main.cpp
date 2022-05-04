diff --git a/CodeJam/Main.cpp b/examples/2018/Round2/C/Main.cpp
index 00aa56c..1cf43a6 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round2/C/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1544,11 +1544,39 @@ void init(){
     cin >> T;
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
