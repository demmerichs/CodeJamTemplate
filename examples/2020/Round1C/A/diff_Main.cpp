diff --git a/CodeJam/Main.cpp b/examples/2020/Round1C/A/Main.cpp
index fabbe5f..46f7abc 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1C/A/Main.cpp
@@ -1,9 +1,9 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result < 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1013,11 +1013,30 @@ namespace task {
 void init(){
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
