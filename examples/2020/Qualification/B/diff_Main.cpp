diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/B/Main.cpp
index aed7a25..b693492 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/B/Main.cpp
@@ -2,7 +2,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define ERROR_WORD "IMPOSSIBLE"
-#define COMM_TYPE ll
+#define COMM_TYPE str
 #define IA_ERROR_CODE "ERROR"
 
 // The maintained and empty code template can be found at:
@@ -828,11 +828,37 @@ namespace task {
 void init(){
 }
 
+str S;
+
 void readInput(){
+    cin >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    sstr outr;
+    ll d = 0;
+    forn(i, S.sz){
+        ll n = S[i] - '0';
+        if(d<n){
+            forn(k, n-d){
+                outr << "(";
+            }
+        }
+        if(d>n){
+            forn(k, d-n){
+                outr << ")";
+            }
+        }
+        d=n;
+        outr << S[i];
+    }
+
+    forn(k, d){
+        outr << ")";
+    }
+    result = outr.str();
+
 }
 
 } // namespace task
