diff --git a/CodeJam/Main.cpp b/examples/template_tests/binary_search/float/Main.cpp
index 16602b7..8571125 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/binary_search/float/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1013,11 +1013,18 @@ namespace task {
 void init(){
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
