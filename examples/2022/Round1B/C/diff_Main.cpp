diff --git a/CodeJam/Main.cpp b/examples/2022/Round1B/C/Main.cpp
index e05e235..fc6ee9f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1B/C/Main.cpp
@@ -1,7 +1,7 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
@@ -1558,8 +1558,33 @@ void init(){
 void readInput(){
 }
 
+v(str) Pk(ll k){
+    if(k==0){
+        v(str) ans;
+        ans.pb("1");
+        return ans;
+    }
+    v(str) Pkm1 = Pk(k-1);
+    v(str) dbl;
+    foreach(pk, Pkm1)
+        dbl.pb(pk+pk);
+    v(str) ans = dbl;
+    foreach(pk, Pkm1){
+        ans.pb(pk + str("00000000").substr(0, pk.sz));
+        ans.insert(ans.ed, all(dbl));
+    }
+    return ans;
+}
+
 // write to COMM_TYPE result
 void calcFunction() {
+    v(str) p3 = Pk(3);
+    foreach(p, p3){
+        out(p);
+        ll ans = in();
+        if(ans==0)
+            break;
+    }
 }
 
 } // namespace task
