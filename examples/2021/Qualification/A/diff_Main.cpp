diff --git a/CodeJam/Main.cpp b/examples/2021/Qualification/A/Main.cpp
index 9a2018d..f839497 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Qualification/A/Main.cpp
@@ -1411,11 +1411,26 @@ void init(){
     cin >> T;
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
