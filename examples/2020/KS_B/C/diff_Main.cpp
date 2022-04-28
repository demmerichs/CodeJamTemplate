diff --git a/CodeJam/Main.cpp b/examples/2020/KS_B/C/Main.cpp
index fa1026d..05e6677 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_B/C/Main.cpp
@@ -4,8 +4,8 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define COMM_TYPE cell
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -67,10 +67,10 @@ typedef std::stringstream sstr;
 #define INF std::numeric_limits<long long>::max()
 #define EPS 1e-15L
 #define PI 3.14159265358979323846264338328L
-#define MOD 1000000007LL
-#define MOD_IS_PRIME    //add commment on this line, when MOD is changed to non-prime number
+#define MOD 1000000000LL
+// #define MOD_IS_PRIME    //add commment on this line, when MOD is changed to non-prime number
 #define DIR_NAMES "ENWS"
-v(cell) DIRECTIONS = {cell(1, 0), cell(0, 1), cell(-1, 0), cell(0, -1)};
+v(cell) DIRECTIONS = {cell(1, 0), cell(0, -1), cell(-1, 0), cell(0, 1)};
 d(char, ll) DIR_IDX = {{'E', 0}, {'N', 1}, {'W', 2}, {'S', 3}};
 #pragma endregion constants
 #pragma region small conveniance functions
@@ -1414,11 +1414,47 @@ void init(){
     cin >> T;
 }
 
+str prog;
+
 void readInput(){
+    cin >> prog;
+}
+
+cell recur(ll &prog_idx){
+    cell answer(0, 0);
+    while(prog_idx < prog.sz){
+        switch(prog[prog_idx]){
+            case ')':
+                return answer;
+            case 'E':
+            case 'W':
+            case 'N':
+            case 'S':
+                answer += DIRECTIONS[DIR_IDX[prog[prog_idx]]];
+                break;
+            default:
+                ll count = prog[prog_idx]-'0';
+                prog_idx+=2;
+                answer += recur(prog_idx) * count;
+                break;
+        }
+        prog_idx++;
+        lg(answer);
+        answer.real(mposOp(answer.x));
+        answer.imag(mposOp(answer.y));
+        lg(prog_idx);
+        lg(answer);
+    }
+    return answer;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = cell(1,1);
+    ll prog_idx = 0;
+    result += recur(prog_idx);
+    lg(prog_idx);
+    lg(prog.sz);
 }
 
 } // namespace task
