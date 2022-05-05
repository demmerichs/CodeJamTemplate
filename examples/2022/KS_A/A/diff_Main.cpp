diff --git a/CodeJam/Main.cpp b/examples/2022/KS_A/A/Main.cpp
index e05e235..48b2bcd 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/KS_A/A/Main.cpp
@@ -1,5 +1,5 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result == -1
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
@@ -1555,11 +1555,32 @@ void init(){
     cin >> T;
 }
 
+str I, P;
+
 void readInput(){
+    cin >> I >> P;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+
+    ll iptr=0, pptr=0;
+    while(iptr < I.sz){
+        if(I[iptr]==P[pptr]){
+            iptr++;
+            pptr++;
+        } else {
+            pptr++;
+            result++;
+            if(pptr>=P.sz){
+                result = -1;
+                break;
+            }
+        }
+    }
+    if(result >= 0)
+        result += P.sz - pptr;
 }
 
 } // namespace task
