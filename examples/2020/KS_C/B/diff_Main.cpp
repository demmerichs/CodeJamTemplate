diff --git a/CodeJam/Main.cpp b/examples/2020/KS_C/B/Main.cpp
index 0f47b9d..00813ed 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_C/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1569,11 +1569,55 @@ void init(){
     cin >> T;
 }
 
+ll R, C;
+v(str) grid;
+
 void readInput(){
+    cin >> R >> C;
+    grid.resize(R);
+    forn(i, R) cin >> grid[i];
 }
 
+d(char, s(char)) required;
+
 // write to COMM_TYPE result
 void calcFunction() {
+    required.cl;
+    s(char) lets;
+    forn(r, R) forn(c, C) lets.insert(grid[r][c]);
+    foreach(let, lets){
+        required[let];
+        forn(r, R-1){
+            forn(c, C){
+                if(grid[r][c] == let){
+                    if(grid[r+1][c] != let){
+                        required[let].insert(grid[r+1][c]);
+                    }
+                }
+            }
+        }
+    }
+
+    result = "";
+    ll lastsize = required.sz;
+    while(required.sz){
+        lg(required);
+        foreach(req, required){
+            if(req.nd.sz) continue;
+            char nextlet = req.st;
+            result += nextlet;
+            required.erase(nextlet);
+            foreach(r, required){
+                r.nd.erase(nextlet);
+            }
+            break;
+        }
+        if(lastsize == required.sz){
+            result = "-1";
+            break;
+        }
+        lastsize = required.sz;
+    }
 }
 
 } // namespace task
