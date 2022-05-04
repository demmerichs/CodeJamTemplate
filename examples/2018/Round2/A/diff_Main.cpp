diff --git a/CodeJam/Main.cpp b/examples/2018/Round2/A/Main.cpp
index 05e1aa9..a27d627 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round2/A/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1540,11 +1540,54 @@ void init(){
     cin >> T;
 }
 
+ll C;
+v(ll) Bi;
+
 void readInput(){
+    cin >> C;
+    Bi.cl;
+    forn(i, C){
+        ll t;
+        cin >> t;
+        Bi.pb(t);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll max_delta = 0;
+    v(ll) deltas;
+    sstr res;
+    if(Bi[0] == 0 || Bi.bk == 0){
+        result = "";
+        return;
+    }
+
+    deltas.pb(0);
+    forn(i, C){
+        deltas.pb(deltas.bk+1-Bi[i]);
+        max_delta = max(abs(deltas.bk), max_delta);
+    }
+    llog("deltas", deltas);
+
+    res << max_delta+1 << endl;
+    forn(r, max_delta){
+        forn(c, C){
+            if(c==0) res << ".";
+            else if(c==C-1) res << ".";
+            else{
+                if(deltas[c]<0 && -deltas[c]>r)
+                    res << "/";
+                else if(deltas[c+1]>0 && deltas[c+1]>r)
+                    res << "\\";
+                else res << ".";
+            }
+        }
+        res << endl;
+    }
+    forn(i, C)
+        res << ".";
+    result = res.str();
 }
 
 } // namespace task
