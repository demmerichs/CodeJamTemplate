diff --git a/CodeJam/Main.cpp b/examples/2019/Round1C/B_interactive/Main.cpp
index 6e1211d..d026413 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1C/B_interactive/Main.cpp
@@ -1,11 +1,11 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE -1
-#define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE "N"
+// #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1061,8 +1061,10 @@ using namespace std;
 
 namespace task {
 
+ll F;
+
 void init(){
-    cin >> T;
+    cin >> T >> F;
 }
 
 void readInput(){
@@ -1070,6 +1072,43 @@ void readInput(){
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "";
+    s(char) lets;
+    forn(i, 5) lets.insert("ABCDE"[i]);
+    v(str) explored(119, "Y");
+    forn(i, 5){
+        d(char, ll) counts;
+        foreach(let, lets) counts[let] = 0;
+        forn(k, 119){
+            if(explored[k][i] == 'X'){
+                explored[k] += 'X';
+                continue;
+            }
+            out(1+i+k*5);
+            explored[k] += in();
+            counts[explored[k][i+1]]++;
+        }
+        lg(counts);
+        char minchar = counts.bn->st;
+        ll mincount = counts[minchar];
+        foreach(let, lets){
+            if(counts[let] < mincount){
+                minchar = let;
+                mincount = counts[minchar];
+                break;
+            }
+        }
+        result += minchar;
+        lets.erase(minchar);
+        forn(k, 119){
+            if(explored[k][i+1] != minchar){
+                explored[k][i+1] = 'X';
+            }
+        }
+    }
+    lg(result);
+    out(result);
+    in();
 }
 
 } // namespace task
