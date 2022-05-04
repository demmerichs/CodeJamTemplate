diff --git a/CodeJam/Main.cpp b/examples/2019/Qualification/A/Main.cpp
index 05e1aa9..f4ddc43 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Qualification/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(str)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1540,11 +1540,26 @@ void init(){
     cin >> T;
 }
 
+str N;
+
 void readInput(){
+    cin >> N;
+    result.cl;
 }
 
-// write to COMM_TYPE result
+// write to OUT_TYPE result
 void calcFunction() {
+    str a = N;
+    forn(i, a.sz){
+        if(a[i]=='4'){
+            a[i] = '1';
+            N[i] = '3';
+        } else
+            a[i] = '0';
+    }
+    a = a.substr(a.find('1'));
+    result.pb(a);
+    result.pb(N);
 }
 
 } // namespace task
