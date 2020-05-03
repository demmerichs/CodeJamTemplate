diff --git a/CodeJam/Main.cpp b/examples/2020/Round1B/A/Main.cpp
index a548e30..6c3225d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1B/A/Main.cpp
@@ -1,10 +1,10 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result<0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result.sz==0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -999,11 +999,65 @@ namespace task {
 void init(){
 }
 
+ll X, Y;
+
 void readInput(){
+    cin >> X >> Y;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "";
+    str dirx = "WE";
+    str diry = "SN";
+    while(X!=0 || Y!= 0){
+        if(X<0){
+            X*=-1;
+            reverse(all(dirx));
+        }
+        if(Y<0){
+            Y*=-1;
+            reverse(all(diry));
+        }
+        if(X%2 == Y%2){
+            result = "";
+            return;
+        }
+        ll val = Y;
+        str dir=diry;
+        if(X%2){
+            dir=dirx;
+            val = X;
+        }
+        bool go_higher;
+        if((X>>1)%2 == (Y>>1)%2){
+            go_higher = false;
+        } else {
+            go_higher = true;
+        }
+        if(val == 1 && (X==0 || Y==0)){
+            go_higher = true;
+        }
+        if(go_higher){
+            result += dir[1];
+            if(dir==dirx){
+                X -= 1;
+            } else {
+                Y-= 1;
+            }
+        } else {
+            result += dir[0];
+            if(dir==dirx){
+                X += 1;
+            } else {
+                Y+= 1;
+            }
+        }
+        lassert(X%2 == 0, "ohno");
+        lassert(Y%2 == 0, "ohno");
+        X /= 2;
+        Y /= 2;
+    }
 }
 
 } // namespace task
