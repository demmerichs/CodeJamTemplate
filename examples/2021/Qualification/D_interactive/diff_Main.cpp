diff --git a/CodeJam/Main.cpp b/examples/2021/Qualification/D_interactive/Main.cpp
index 6e1211d..6c7d487 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Qualification/D_interactive/Main.cpp
@@ -1,7 +1,7 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
@@ -1061,8 +1061,61 @@ using namespace std;
 
 namespace task {
 
+ll N, Q;
+v(ll) start_values;
+
 void init(){
-    cin >> T;
+    cin >> T >> N >> Q;
+    start_values.resize(N);
+    forn(i, N) start_values[i] = i+1;
+}
+
+ll ask(ll a, ll b, ll c){
+    v(ll) values = {a, b, c};
+    out(values);
+    return in();
+}
+
+v(ll) median_sort(v(ll) values){
+    if(values.sz < 2) return values;
+    ll x1 = values[0];
+    ll x2 = values[1];
+    v(ll) bin0, bin1, bin2;
+    fornn(i, 2, values.sz){
+        ll med = ask(x1, x2, values[i]);
+        if(med == x1){
+            bin0.pb(values[i]);
+        } else if(med == x2){
+            bin2.pb(values[i]);
+        } else {
+            bin1.pb(values[i]);
+        }
+    }
+    v(ll) bin0s = median_sort(bin0);
+    v(ll) bin1s = median_sort(bin1);
+    v(ll) bin2s = median_sort(bin2);
+
+    if(bin0s.sz > 1){
+        ll bin0o = ask(bin0s[0], bin0s[1], x1);
+        if(bin0o == bin0s[0]) reverse(all(bin0s));
+    }
+    if(bin1s.sz > 1){
+        ll bin1o = ask(bin1s[0], bin1s[1], x2);
+        if(bin1o == bin1s[0]) reverse(all(bin1s));
+    }
+    if(bin2s.sz > 1){
+        ll bin2o = ask(x2, bin2s[0], bin2s[1]);
+        if(bin2o == bin2s[1]) reverse(all(bin2s));
+    }
+
+    v(ll) sorted_values;
+    sorted_values.insert(sorted_values.ed, all(bin0s));
+    sorted_values.pb(x1);
+    sorted_values.insert(sorted_values.ed, all(bin1s));
+    sorted_values.pb(x2);
+    sorted_values.insert(sorted_values.ed, all(bin2s));
+
+    return sorted_values;
 }
 
 void readInput(){
@@ -1070,6 +1123,9 @@ void readInput(){
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) result_order = median_sort(start_values);
+    out(result_order);
+    in();
 }
 
 } // namespace task
