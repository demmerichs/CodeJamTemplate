diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/A/Main.cpp
index 6e1211d..5a11f11 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1065,11 +1065,44 @@ void init(){
     cin >> T;
 }
 
+ll k, N;
+v(v(ll)) Mij;
+v(s(ll)) rc, cc;
+
 void readInput(){
+    cin >> N;
+    Mij.cl;
+    rc.cl;
+    cc.cl;
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
+    result.cl;
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
