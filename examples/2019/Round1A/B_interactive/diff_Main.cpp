diff --git a/CodeJam/Main.cpp b/examples/2019/Round1A/B_interactive/Main.cpp
index 5a22041..38edaba 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1A/B_interactive/Main.cpp
@@ -1,8 +1,8 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result<0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE "ERROR"
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE -1
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
@@ -905,14 +905,36 @@ using namespace std;
 
 namespace task {
 
+ll N, m;
+
 void init(){
+    N = in();
+    m = in();
 }
 
 void readInput(){
 }
 
+ll ask(ll p){
+    v(ll) ps(18, p);
+    out(ps);
+    ll sum = 0;
+    forn(i, 18){
+        sum += in();
+    }
+    return sum % p;
+}
+
 // write to COMM_TYPE result
 void calcFunction() {
+    lassert(N>=7, "N was smaller than 7");
+    v(ll) p = {17, 16, 13, 11, 9, 7, 5};
+    v(ll) ans;
+    forn(i, 7){
+        ans.pb(ask(p[i]));
+    }
+    out(crt(ans, p));
+    in();
 }
 
 } // namespace task
