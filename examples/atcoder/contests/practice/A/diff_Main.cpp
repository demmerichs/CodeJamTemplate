diff --git a/CodeJam/Main.cpp b/examples/atcoder/contests/practice/A/Main.cpp
index fa1026d..4613c13 100644
--- a/CodeJam/Main.cpp
+++ b/examples/atcoder/contests/practice/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1386,7 +1386,8 @@ int main() {
         llog();
 #ifndef IA_MODE
         //write output
-        std::cout << "Case #" << test << ": ";
+        if(task::T > 1)
+            std::cout << "Case #" << test << ": ";
 #ifndef DEFAULT_VAL_MODE
         std::cout << result << std::endl;
 #else
@@ -1411,14 +1412,20 @@ using namespace std;
 namespace task {
 
 void init(){
-    cin >> T;
+    // cin >> T;
+    T = 1;
 }
 
+ll a, b, c;
+str s;
+
 void readInput(){
+    cin >> a >> b >> c >> s;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = to_string(a+b+c) + " " + s;
 }
 
 } // namespace task
