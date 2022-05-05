diff --git a/CodeJam/Main.cpp b/examples/template_tests/binary_search/float/Main.cpp
index 2150379..fd23333 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/binary_search/float/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1570,11 +1570,18 @@ void init(){
     cin >> T;
 }
 
+ld thresh;
+
 void readInput(){
+    cin >> thresh;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    auto func = [](ld val){return exp(val);};
+    result = lower_bound_function<ld,ld>(thresh, func, 20.0, -10.0, 1e-10);
+    ld upper_result = upper_bound_function<ld,ld>(thresh, func, 20.0, -10.0, 1e-10);
+    assert(result == upper_result);
 }
 
 } // namespace task
