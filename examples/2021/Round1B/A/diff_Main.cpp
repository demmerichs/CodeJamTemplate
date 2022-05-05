diff --git a/CodeJam/Main.cpp b/examples/2021/Round1B/A/Main.cpp
index f8bdafd..4fdbefb 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1B/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -67,8 +67,8 @@ typedef std::stringstream sstr;
 #define INF std::numeric_limits<long long>::max()
 #define EPS 1e-15L
 #define PI 3.14159265358979323846264338328L
-#define MOD 1000000007LL
-#define MOD_IS_PRIME    //add commment on this line, when MOD is changed to non-prime number
+#define MOD 43200000000000LL
+// #define MOD_IS_PRIME    //add commment on this line, when MOD is changed to non-prime number
 #define DIR_NAMES "ENWS"
 v(cell) DIRECTIONS = {cell(1, 0), cell(0, 1), cell(-1, 0), cell(0, -1)};
 d(char, ll) DIR_IDX = {{'E', 0}, {'N', 1}, {'W', 2}, {'S', 3}};
@@ -1568,11 +1568,43 @@ void init(){
     cin >> T;
 }
 
+ll A, B, C;
+
 void readInput(){
+    cin >> A >> B >> C;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result.resize(4);
+    v(ll) HMS = {A, B, C};
+    sort(all(HMS));
+    do{
+        ll H=HMS[0];
+        mint M=HMS[1], S=HMS[2];
+        lg(H);
+        lg(M);
+        lg(S);
+        mint mminushmodT = M-H;
+        ll t = (mminushmodT / 11LL).value;
+        ll delta = H-t;
+        if(M != mint(12*t+delta)){
+            llog("minutes did not match");
+            continue;
+        }
+        if(S != mint(720*t+delta)){
+            llog("seconds did not match");
+            continue;
+        }
+        result[3] = t % 1000000000LL;
+        t /= 1000000000LL;
+        result[2] = t % 60LL;
+        t /= 60LL;
+        result[1] = t % 60LL;
+        t /= 60LL;
+        result[0] = t;
+        break;
+    }while(next_permutation(all(HMS)));
 }
 
 } // namespace task
