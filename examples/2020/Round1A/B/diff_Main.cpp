diff --git a/CodeJam/Main.cpp b/examples/2020/Round1A/B/Main.cpp
index 7b152f5..e6917ed 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1A/B/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -896,11 +896,53 @@ namespace task {
 void init(){
 }
 
+ll N;
+
 void readInput(){
+    cin >> N;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll r = log2ll(N)+1;
+    ll k = N-r;
+    lassert(k>=0, "ohnooo");
+    ll counter = 0;
+
+    result.clear();
+    result += "\n";
+    sstr res;
+    bool left = true;
+    ll level = 0;
+    while(counter < N){
+        if((k>>level)&1){
+            counter += (1<<level);
+            level++;
+            if(left){
+                fore(i, 1,level){
+                    res << level << " " << i << endl;
+                }
+                left = false;
+            } else {
+                forn(i, level){
+                    res << level << " " << level - i << endl;
+                }
+                left = true;
+            }
+        } else {
+            counter++;
+            level++;
+            if(left){
+                res << level << " " << 1;
+            } else {
+                res << level << " " << level;
+            }
+            if(counter < N) res << endl;
+        }
+    }
+    result += res.str();
+    llog("result", result);
+    lassert(counter==N, "something went wrong");
 }
 
 } // namespace task
