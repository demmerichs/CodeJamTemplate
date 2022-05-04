diff --git a/CodeJam/Main.cpp b/examples/2022/Round1C/B/Main.cpp
index 6f10f99..7727056 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1C/B/Main.cpp
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
@@ -1551,11 +1551,47 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
+v(ll) Ei;
+
 void readInput(){
+    cin >> N >> K;
+    Ei.resize(N);
+    forn(i, N){
+        cin >> Ei[i];
+        lg(Ei);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll A = 0, S=0;
+    forn(i, N){
+        A += Ei[i]*Ei[i];
+        S += Ei[i];
+    }
+    lg(A);
+    lg(S);
+    ll delta = (A-S*S)/2;
+    lg(delta);
+    result.cl;
+    if(delta == 0){
+        result.pb(0);
+        return;
+    }
+    if(K==1){
+        if(S == 0)
+            return;
+        if(delta % S == 0){
+            result.pb(delta/S);
+        }
+        return;
+    }
+    lg(result);
+    result.pb(1-S);
+    lg(result);
+    result.pb(delta + S*S - S);
+    lg(result);
 }
 
 } // namespace task
