diff --git a/CodeJam/Main.cpp b/examples/2021/KS_A/C/Main.cpp
index e05e235..5664347 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_A/C/Main.cpp
@@ -1555,11 +1555,47 @@ void init(){
     cin >> T;
 }
 
+ll R, C;
+ll height[300][300];
+
 void readInput(){
+    cin >> R >> C;
+    forn(r, R) forn(c, C) cin >> height[r][c];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll update = 0;
+    do{
+        result += update;
+        update = 0;
+        forn(r, R)
+            forn(c, C){
+                if(c+1<C && abs(height[r][c]-height[r][c+1])>1){
+                    ll delta = height[r][c] - height[r][c+1];
+                    if(delta < 0){
+                        height[r][c] += -delta-1;
+                        update += -delta-1;
+                    }
+                    else{
+                        height[r][c+1] += delta-1;
+                        update += delta-1;
+                    }
+                }
+                if(r+1<R && abs(height[r][c]-height[r+1][c])>1){
+                    ll delta = height[r][c] - height[r+1][c];
+                    if(delta < 0){
+                        height[r][c] += -delta-1;
+                        update += -delta-1;
+                    }
+                    else{
+                        height[r+1][c] += delta-1;
+                        update += delta-1;
+                    }
+                }
+            }
+    }while(update > 0);
 }
 
 } // namespace task
