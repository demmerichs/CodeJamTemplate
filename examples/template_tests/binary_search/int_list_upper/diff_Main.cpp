diff --git a/CodeJam/Main.cpp b/examples/template_tests/binary_search/int_list_upper/Main.cpp
index 05e1aa9..365271e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/binary_search/int_list_upper/Main.cpp
@@ -1540,11 +1540,24 @@ void init(){
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
+    result = upper_bound_function<ll,ll>(threshold, [&](ll i){return values[i];}, values.sz);
 }
 
 } // namespace task
