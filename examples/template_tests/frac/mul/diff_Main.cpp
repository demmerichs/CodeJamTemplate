diff --git a/CodeJam/Main.cpp b/examples/template_tests/frac/mul/Main.cpp
index e05e235..5ec4fd7 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/frac/mul/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE fracll
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1555,11 +1555,17 @@ void init(){
     cin >> T;
 }
 
+ll Ap, Aq, Bp, Bq;
+
 void readInput(){
+    cin >> Ap >> Aq >> Bp >> Bq;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    fracll A(Ap, Aq);
+    fracll B(Bp, Bq);
+    result = A * B;
 }
 
 } // namespace task
