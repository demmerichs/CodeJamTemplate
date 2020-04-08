diff --git a/CodeJam/Main.cpp b/examples/2019/Round1A/B_interactive/Main.cpp
index aed7a25..893a4fb 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1A/B_interactive/Main.cpp
@@ -1,9 +1,9 @@
 // #define DEFAULT_VAL    //remove comment on this line, to activate default value trigger
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define ERROR_WORD "IMPOSSIBLE"
 #define COMM_TYPE ll
-#define IA_ERROR_CODE "ERROR"
+#define IA_ERROR_CODE -1
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -825,14 +825,36 @@ using namespace std;
 
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
