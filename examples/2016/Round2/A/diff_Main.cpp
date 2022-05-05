diff --git a/CodeJam/Main.cpp b/examples/2016/Round2/A/Main.cpp
index f8bdafd..f5b7f5a 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2016/Round2/A/Main.cpp
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
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1568,11 +1568,63 @@ void init(){
     cin >> T;
 }
 
+bool winner(ll &r, ll &p, ll &s){
+    ll n = r+p+s;
+    if(n==1) return true;
+    ll nr = (n>>1)-p;
+    ll np = (n>>1)-s;
+    ll ns = (n>>1)-r;
+    if(nr<0) return false;
+    if(np<0) return false;
+    if(ns<0) return false;
+    r=nr;
+    p=np;
+    s=ns;
+    return winner(r,p,s);
+}
+
+void backtrack(str &s){
+    str ans="";
+    forn(i, s.sz){
+        if(s[i] == 'R')
+            ans += "RS";
+        if(s[i] == 'P')
+            ans += "PR";
+        if(s[i] == 'S')
+            ans += "PS";
+    }
+    s = ans;
+}
+
+void put_in_lexi_order(str &s, ll i){
+    ll len = 1<<i;
+    str ans = "";
+    forn(k, s.sz/len/2){
+        str p1 = s.substr(k*len*2, len);
+        str p2 = s.substr(k*len*2+len, len);
+        if(p2 < p1){
+            ans += p2 + p1;
+        } else
+            ans += p1 + p2;
+    }
+    s = ans;
+}
+
+ll N, R, P, S;
 void readInput(){
+    cin >> N >> R >> P >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "";
+    ll r=R, p=P, s=S;
+    if(!winner(r,p,s)) return;
+    result = 'R'*r + 'P'*p + 'S'*s;
+    forn(i, N)
+        backtrack(result);
+    forn(i, N)
+        put_in_lexi_order(result, i);
 }
 
 } // namespace task
