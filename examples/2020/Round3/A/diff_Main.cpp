diff --git a/CodeJam/Main.cpp b/examples/2020/Round3/A/Main.cpp
index 42da9e7..34f2b90 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round3/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1024,11 +1024,72 @@ void init(){
     cin >> T;
 }
 
+str C, J;
+
 void readInput(){
+    cin >> C >> J;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(v(ll)) lsm(C.sz+1, v(ll)(J.sz+1, 0));
+    forn(i, C.sz+1) lsm[i][0] = i;
+    forn(i, J.sz+1) lsm[0][i] = i;
+
+    fornn(i, 1, C.sz+1){
+        fornn(j, 1, J.sz+1){
+            lsm[i][j] = min({
+                    lsm[i][j-1] + 1,
+                    lsm[i-1][j] + 1,
+                    lsm[i-1][j-1] + (C[i-1]!=J[j-1])
+                }
+            );
+        }
+    }
+    forn(i, C.sz+1)
+        lg(lsm[i]);
+
+    // result stores tail result as we need to compute backwards
+    result = "";
+    ll totallsm = lsm[C.sz][J.sz];
+    ll Jdist = totallsm / 2;
+    ll cpref = C.sz, jpref = J.sz;
+    while(Jdist>0){
+        lg(C.substr(0, cpref));
+        lg(J.substr(0, jpref));
+        lg(result);
+        lg(Jdist);
+        if(lsm[cpref-1][jpref] + 1 == lsm[cpref][jpref]){
+            result = C[cpref-1] + result;
+            Jdist--;
+            cpref--;
+            llog("delete from C");
+            continue;
+        }
+        if(lsm[cpref][jpref-1] + 1 == lsm[cpref][jpref]){
+            Jdist--;
+            jpref--;
+            llog("delete from J");
+            continue;
+        }
+        if(lsm[cpref-1][jpref-1] + 1 == lsm[cpref][jpref]){
+            result = C[cpref-1] + result;
+            Jdist--;
+            cpref--;
+            jpref--;
+            llog("replace");
+            continue;
+        }
+        if(lsm[cpref-1][jpref-1] == lsm[cpref][jpref]){
+            result = C[cpref-1] + result;
+            cpref--;
+            jpref--;
+            llog("match");
+            continue;
+        }
+        lassert(false, "computation of lsm was faulty it seems");
+    }
+    result = J.substr(0, jpref) + result;
 }
 
 } // namespace task
