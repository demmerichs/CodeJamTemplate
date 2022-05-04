diff --git a/CodeJam/Main.cpp b/examples/2020/KS_B/D/Main.cpp
index 05e1aa9..4f346c5 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_B/D/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1536,15 +1536,46 @@ using namespace std;
 
 namespace task {
 
+ld log2facs[200000];
 void init(){
     cin >> T;
+    log2facs[0] = 0;
+    fornn(i, 1, 200000){
+        log2facs[i] = log2facs[i-1] + log2(i+1);
+    }
 }
 
+ll W, H, L, U, R, D;
+
 void readInput(){
+    cin >> W >> H >> L >> U >> R >> D;
+}
+
+ld log2chooseld(ll n, ll k){
+    lassert(k<=n, "log not working for count 0");
+    if (k > n)
+        return 0.0;
+    if ( n-k < k)
+        return log2chooseld(n, n-k);
+    return log2facs[n-1] - log2facs[n-k-1] - log2facs[k-1];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0.0;
+    if(L==1 && R==W) return;
+    if(U==1 && D==H) return;
+
+    if(U > 1 && R < W){
+        fornn(r, 1, U){
+            result += pow(2.0l, log2chooseld(r-1+R-1, R-1) - (r-1+R)*log2facs[1]);
+        }
+    }
+    if(D < H && L > 1){
+        fornn(c, 1, L){
+            result += pow(2.0l, log2chooseld(c-1+D-1, D-1) - (c-1+D)*log2facs[1]);
+        }
+    }
 }
 
 } // namespace task
