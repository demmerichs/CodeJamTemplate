diff --git a/CodeJam/Main.cpp b/examples/2022/Round1A/A/Main.cpp
index 00aa56c..8799af4 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1A/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1544,11 +1544,32 @@ void init(){
     cin >> T;
 }
 
+str S;
+
 void readInput(){
+    cin >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "";
+    forn(i, S.sz){
+        if(i==S.sz-1){
+            result += S[i];
+            continue;
+        }
+        ll next_differ = i;
+        while(S[next_differ] == S[i]){
+            ++next_differ;
+            if(next_differ==S.sz) break;
+        }
+        if(next_differ == S.sz || S[next_differ] <= S[i]){
+            result += S[i];
+            continue;
+        }
+        result += S[i];
+        result += S[i];
+    }
 }
 
 } // namespace task
