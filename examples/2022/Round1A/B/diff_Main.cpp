diff --git a/CodeJam/Main.cpp b/examples/2022/Round1A/B/Main.cpp
index 6e1211d..931b96b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1A/B/Main.cpp
@@ -1,7 +1,7 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
@@ -1061,15 +1061,59 @@ using namespace std;
 
 namespace task {
 
+s(ll) Ai;
 void init(){
     cin >> T;
+    ll last = 1<<29;
+    while(!Ai.count(last)){
+        Ai.insert(last);
+        last = last / 2 + 1;
+    }
+    ll c = 1;
+    while(Ai.sz < 100){
+        if(Ai.count(c)){
+            c++;
+            continue;
+        } else {
+            Ai.insert(c);
+            c++;
+        }
+    }
 }
 
+ll N;
+
 void readInput(){
+    cin >> N;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    out(Ai);
+    s(ll) all_vals;
+    forn(i, N){
+        ll t = in();
+        all_vals.insert(t);
+    }
+    foreach(ai, Ai)
+        all_vals.insert(ai);
+
+    ll s = accumulate(all(all_vals), 0LL);
+    lg(s);
+    lassert(s%2==0, "logic error");
+    ll t = s/2;
+
+    ll left = 0, right = 0;
+    v(ll) returns;
+    for(auto it=all_vals.rbegin(); it!=all_vals.rend(); ++it){
+        if(left < right){
+            left += *it;
+            returns.pb(*it);
+        } else {
+            right += *it;
+        }
+    }
+    out(returns);
 }
 
 } // namespace task
