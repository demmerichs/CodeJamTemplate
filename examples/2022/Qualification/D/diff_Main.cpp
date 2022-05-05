diff --git a/CodeJam/Main.cpp b/examples/2022/Qualification/D/Main.cpp
index e05e235..15fa137 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Qualification/D/Main.cpp
@@ -1555,11 +1555,61 @@ void init(){
     cin >> T;
 }
 
+d(ll, v(ll)) backwards;
+v(ll) Pi;
+v(ll) Fi;
+ll N;
+
 void readInput(){
+    backwards.cl;
+    Pi.cl;
+    Fi.cl;
+    cin >> N;
+    Fi.resize(N);
+    Pi.resize(N);
+    forn(i, N)
+        cin >> Fi[i];
+    forn(i, N){
+        cin >> Pi[i];
+        Pi[i]--;
+        backwards[Pi[i]].pb(i);
+    }
+
+}
+
+p(ll, ll) recursive_fun(ll node){
+    if(backwards[node].sz == 0){
+        lg(node);
+        llog("initiator");
+        return mp(Fi[node], Fi[node]);
+    }
+    ll sum = 0;
+    ll smallest_close_root = INF;
+    forn(i, backwards[node].sz){
+        ll par = backwards[node][i];
+        p(ll, ll) cur_recur = recursive_fun(par);
+        sum += cur_recur.st;
+        smallest_close_root = min(smallest_close_root, cur_recur.nd);
+    }
+    if(node>=0 && Fi[node] > smallest_close_root){
+        sum += Fi[node] - smallest_close_root;
+        lg(node);
+        llog("update");
+        lg(mp(sum, Fi[node]));
+        return mp(sum, Fi[node]);
+    }
+    lg(node);
+    llog("pass through");
+    lg(mp(sum, smallest_close_root));
+    return mp(sum, smallest_close_root);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    lg(Pi);
+    lg(backwards);
+    lg(Fi);
+    result = recursive_fun(-1).st;
 }
 
 } // namespace task
