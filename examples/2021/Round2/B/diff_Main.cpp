diff --git a/CodeJam/Main.cpp b/examples/2021/Round2/B/Main.cpp
index e05e235..26b9c49 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round2/B/Main.cpp
@@ -1555,11 +1555,49 @@ void init(){
     cin >> T;
 }
 
+ll N;
+
 void readInput(){
+    cin >> N;
+}
+
+v(ll) memory(1000001, -1);
+
+v(ll) getpf(ll n){
+    v(ll) res;
+    fornn(d, 2, sqrtl(n)+1){
+        if(n%d==0){
+            res.pb(d);
+            res.pb(n/d);
+        }
+    }
+    return res;
+}
+
+ll recur(ll n){
+    if(n<=1) return -1;
+    if(memory[n] != -1) return memory[n];
+    v(ll) pf = getpf(n);
+    memory[n] = 1;
+    foreach(p, pf){
+        ll curresult = recur(n/p - 1);
+        memory[n] = max(memory[n], curresult+1);
+    }
+    return memory[n];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) pf = getpf(N);
+    lg(pf);
+    result = 1;
+    foreach(p, pf){
+        if(p==2) continue;
+        ll curresult = recur(N/p - 1);
+        lg(p);
+        lg(curresult);
+        result = max(result, curresult+1);
+    }
 }
 
 } // namespace task
