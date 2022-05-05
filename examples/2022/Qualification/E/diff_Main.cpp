diff --git a/CodeJam/Main.cpp b/examples/2022/Qualification/E/Main.cpp
index 2150379..11b6dbd 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Qualification/E/Main.cpp
@@ -1,9 +1,9 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
-#define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
+// #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
@@ -1570,11 +1570,49 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
+v(ll) Pi;
+
 void readInput(){
+    N = in();
+    K = in();
+    Pi.cl;
+    Pi.resize(N, -1);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll r = in();
+    ll p = in();
+
+    random_device rd;
+    mt19937 rng(rd());
+    uniform_int_distribution<int> uni(0, N-1);
+    ll avg_estimate = 0;
+    forn(i, K/2){
+        ll cur_room = uni(rng);
+        out("T " + to_string(cur_room+1));
+        r = in();
+        p = in();
+        Pi[r-1] = p;
+        avg_estimate += p;
+
+        out("W");
+        r = in();
+        p = in();
+        Pi[r-1] = p;
+    }
+
+    ll counts_observed = 0;
+    ll sum_observed = 0;
+    forn(i, Pi.sz){
+        if(Pi[i]>0){
+            counts_observed++;
+            sum_observed += Pi[i];
+        }
+    }
+    ll estimate = (sum_observed + avg_estimate * 2 * (N-counts_observed) / K)/2;
+    out("E " + to_string(estimate));
 }
 
 } // namespace task
