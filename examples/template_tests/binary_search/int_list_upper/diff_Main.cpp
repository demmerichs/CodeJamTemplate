diff --git a/CodeJam/Main.cpp b/examples/template_tests/binary_search/int_list_upper/Main.cpp
index 883b228..6ef9f3b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/binary_search/int_list_upper/Main.cpp
@@ -1065,11 +1065,24 @@ void init(){
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
