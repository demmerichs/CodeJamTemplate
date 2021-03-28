diff --git a/CodeJam/Main.cpp b/examples/2021/Qualification/A/Main.cpp
index 16602b7..ae739ba 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Qualification/A/Main.cpp
@@ -1013,11 +1013,26 @@ namespace task {
 void init(){
 }
 
+v(ll) values;
+ll N;
+
 void readInput(){
+    cin >> N;
+    values.resize(N);
+    forn(i, N)
+        cin >> values[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    forn(i, N-1){
+        lg(values);
+        ll j = std::min_element(msel(values, i, N)) - values.begin();
+        lg(j);
+        result += j-i+1;
+        std::reverse(msel(values, i, j+1));
+    }
 }
 
 } // namespace task
