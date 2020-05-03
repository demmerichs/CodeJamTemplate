diff --git a/CodeJam/Main.cpp b/examples/2019/Qualification/B/Main.cpp
index a548e30..efe12d9 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Qualification/B/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -999,11 +999,23 @@ namespace task {
 void init(){
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
