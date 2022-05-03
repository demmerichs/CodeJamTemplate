diff --git a/CodeJam/Main.cpp b/examples/2022/Qualification/B/Main.cpp
index 0f47b9d..7850a2f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Qualification/B/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1569,11 +1569,42 @@ void init(){
     cin >> T;
 }
 
+v(v(ll)) ink;
+
 void readInput(){
+    ink.cl;
+    ink.resize(3, v(ll)(4));
+    forn(i, 3){
+        forn(j, 4){
+            cin >> ink[i][j];
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    lg(ink);
+    result.cl;
+    v(ll) minis(4, 1e6L);
+    forn(i, 3){
+        forn(j, 4){
+            minis[j] = min(ink[i][j], minis[j]);
+        }
+    }
+    lg(minis);
+    ll total = 0;
+    forn(j, 4){
+        total += minis[j];
+    }
+    if(total < 1e6L)
+        return;
+    result.resize(4, 0);
+    ll rest = 1e6L;
+    forn(j, 4){
+        ll curink = min(rest, minis[j]);
+        result[j] = curink;
+        rest -= curink;
+    }
 }
 
 } // namespace task
