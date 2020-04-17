diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/A/Main.cpp
index 97f9cae..0c1e0a4 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/A/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -851,11 +851,44 @@ namespace task {
 void init(){
 }
 
+ll k, N;
+v(v(ll)) Mij;
+v(s(ll)) rc, cc;
+
 void readInput(){
+    cin >> N;
+    Mij.clear();
+    rc.clear();
+    cc.clear();
+    rc = v(s(ll))(N);
+    cc = v(s(ll))(N);
+    ll t;
+    k = 0;
+    forn(i,N){
+        Mij.pb(v(ll)());
+        forn(j,N){
+            cin >> t;
+            Mij.bk.pb(t);
+            rc[i].insert(t-1);
+            cc[j].insert(t-1);
+            if(i==j){
+                k+=t;
+            }
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result.clear();
+    result.pb(k);
+    ll r=0, c=0;
+    forn(i, N){
+        r+= rc[i].sz < N;
+        c += cc[i].sz < N;
+    }
+    result.pb(r);
+    result.pb(c);
 }
 
 } // namespace task
