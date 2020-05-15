diff --git a/CodeJam/Main.cpp b/examples/template_tests/binary_search/int_list_upper/Main.cpp
index d8e2c23..cc15992 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/binary_search/int_list_upper/Main.cpp
@@ -1010,11 +1010,24 @@ namespace task {
 void init(){
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
+    result = upper_bound_function<ll,ll>(threshold, [&](ll i){return values[i];}, values.sz);
 }
 
 } // namespace task
