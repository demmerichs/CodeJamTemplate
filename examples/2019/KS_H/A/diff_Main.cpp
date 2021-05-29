diff --git a/CodeJam/Main.cpp b/examples/2019/KS_H/A/Main.cpp
index 883b228..9c29827 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_H/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1065,11 +1065,30 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) cits;
+
 void readInput(){
+    cin >> N;
+    cits.cl;
+    forn(i, N){
+        ll t;
+        cin >> t;
+        cits.pb(t);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    multiset<ll> tops;
+    result.cl;
+    forn(i, N){
+        tops.insert(cits[i]);
+        if(*tops.begin() < tops.sz){
+            tops.erase(tops.begin());
+        }
+        result.pb(tops.sz);
+    }
 }
 
 } // namespace task
