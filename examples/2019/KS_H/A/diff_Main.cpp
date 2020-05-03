diff --git a/CodeJam/Main.cpp b/examples/2019/KS_H/A/Main.cpp
index 57063df..da6beb9 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_H/A/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1009,11 +1009,30 @@ namespace task {
 void init(){
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
