diff --git a/CodeJam/Main.cpp b/examples/template_tests/binary_search/int_list_lower/Main.cpp
index 00aa56c..9b583ef 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/binary_search/int_list_lower/Main.cpp
@@ -1544,11 +1544,24 @@ void init(){
     cin >> T;
 }
 
+ll threshold;
+v(ll) values;
+
 void readInput(){
+    ll n;
+    cin >> n;
+    cin >> threshold;
+    values.cl;
+    forn(i, n){
+        ll t;
+        cin >> t;
+        values.pb(t);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = lower_bound_function<ll,ll>(threshold, [&](ll i){return values[i];}, values.sz);
 }
 
 } // namespace task
