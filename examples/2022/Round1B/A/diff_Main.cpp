diff --git a/CodeJam/Main.cpp b/examples/2022/Round1B/A/Main.cpp
index 05e1aa9..f54e012 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1B/A/Main.cpp
@@ -1540,11 +1540,31 @@ void init(){
     cin >> T;
 }
 
+ll N;
+dq(ll) Di;
+
 void readInput(){
+    cin >> N;
+    Di.resize(N);
+    forn(i, N)
+        cin >> Di[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll dmin = 0;
+    while(Di.sz){
+        if(Di.ft < Di.bk){
+            result += Di.ft >= dmin;
+            dmin = max(Di.ft, dmin);
+            Di.popf;
+        } else {
+            result += Di.bk >= dmin;
+            dmin = max(Di.bk, dmin);
+            Di.popb;
+        }
+    }
 }
 
 } // namespace task
