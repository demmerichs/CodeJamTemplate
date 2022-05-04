diff --git a/CodeJam/Main.cpp b/examples/2019/Qualification/B/Main.cpp
index 00aa56c..fe58a09 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Qualification/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1544,11 +1544,23 @@ void init(){
     cin >> T;
 }
 
+ll N;
+str p;
+
 void readInput(){
+    cin >> N;
+    cin >> p;
 }
 
-// write to COMM_TYPE result
+// write to OUT_TYPE result
 void calcFunction() {
+    result = p;
+    forn(i, result.sz){
+        if(result[i] == 'S')
+            result[i] = 'E';
+        else
+            result[i] = 'S';
+    }
 }
 
 } // namespace task
