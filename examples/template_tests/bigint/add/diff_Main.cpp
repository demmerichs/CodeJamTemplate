diff --git a/CodeJam/Main.cpp b/examples/template_tests/bigint/add/Main.cpp
index 9a2018d..f422bfd 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/bigint/add/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE bint
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1411,11 +1411,15 @@ void init(){
     cin >> T;
 }
 
+bint a, b;
+
 void readInput(){
+    cin >> a >> b;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = a + b;
 }
 
 } // namespace task