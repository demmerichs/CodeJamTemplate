diff --git a/CodeJam/Main.cpp b/examples/template_tests/frac/div/Main.cpp
index 05e1aa9..b6d6265 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/frac/div/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE fracll
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1540,11 +1540,17 @@ void init(){
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
+    result = A / B;
 }
 
 } // namespace task
