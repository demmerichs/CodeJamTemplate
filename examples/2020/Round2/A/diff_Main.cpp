diff --git a/CodeJam/Main.cpp b/examples/2020/Round2/A/Main.cpp
index fa1026d..52bad84 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round2/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1414,11 +1414,43 @@ void init(){
     cin >> T;
 }
 
+ll L, R;
+
 void readInput(){
+    cin >> L >> R;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll diff = abs(L - R);
+    llog("diff", diff);
+    ll n = lower_bound_function<ll,bool>(true, [&](ll c){return diff<c*(c+1)/2;}, sqrtl(INF))-1;
+    if(diff==0) n=0;
+    llog("initial n from one pile", n);
+    ll take = n*(n+1)/2;
+    if(R>L){
+        R-=take;
+    } else
+        L-=take;
+    bool left_first = L>=R;
+    llog("left first", left_first);
+    ll nL = lower_bound_function<ll,bool>(true, [&](ll c){return L<(n+2-left_first)*(c+1) + c*(c+1);}, sqrtl(INF))-1;
+    llog("nL", nL);
+    ll takeL = (n+2-left_first)*(nL+1)+nL*(nL+1);
+    nL = n+2-left_first + 2 * (nL);
+    llog("nL", nL);
+    ll nR = lower_bound_function<ll,bool>(true, [&](ll c){return R<(n+1+left_first)*(c+1) + c*(c+1);}, sqrtl(INF))-1;
+    llog("nR", nR);
+    ll takeR = (n+1+left_first)*(nR+1)+nR*(nR+1);
+    nR = n+1+left_first + 2 * (nR);
+    llog("nR", nR);
+    n = max(n, max(nR, nL));
+    R-=takeR;
+    L-=takeL;
+
+    sstr res;
+    res << n << " " << L << " " << R;
+    result = res.str();
 }
 
 } // namespace task
