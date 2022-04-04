diff --git a/CodeJam/Main.cpp b/examples/2020/Round1C/A/Main.cpp
index 6e1211d..7f6a121 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1C/A/Main.cpp
@@ -1,10 +1,10 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result < 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1065,11 +1065,30 @@ void init(){
     cin >> T;
 }
 
+cell cur;
+str path;
+
 void readInput(){
+    ll a, b;
+    cin >> a >> b;
+    cur = cell(a,b);
+    cin >> path;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    if(cur.x == 0 && cur.y == 0){
+        result = 0;
+        return;
+    }
+    forn(i, path.sz){
+        cur += DIRECTIONS[DIR_IDX[path[i]]];
+        if(abs(cur.x)+abs(cur.y)<=i+1){
+            result = i+1;
+            return;
+        }
+    }
+    result = -1;
 }
 
 } // namespace task
