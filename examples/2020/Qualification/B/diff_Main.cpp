diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/B/Main.cpp
index 2150379..4284a01 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1570,11 +1570,37 @@ void init(){
     cin >> T;
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
