diff --git a/CodeJam/Main.cpp b/examples/2022/Round1C/A/Main.cpp
index 2150379..a308a45 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1C/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1570,11 +1570,83 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(str) Si;
+
 void readInput(){
+    cin >> N;
+    Si.resize(N);
+    forn(i, N)
+        cin >> Si[i];
+}
+
+v(str) reduce_letter(char let, v(str) reductions){
+    v(str) rest, left, center, right;
+    str allsameconcat = "";
+    foreach(s, reductions){
+        if(s.find(let) == str::npos){
+            rest.pb(s);
+            continue;
+        }
+        ll l=s.sz, r=0, count=0;
+        forn(i, s.sz){
+            if(s[i]==let){
+                l = min(l, i);
+                r = max(r, i);
+                count++;
+            }
+        }
+        if(count < r - l + 1){
+            return v(str)();
+        }
+        if(l == 0 && r == s.sz-1){
+            allsameconcat += s;
+            continue;
+        }
+        if(l == 0){
+            left.pb(s);
+            continue;
+        }
+        if(r==s.sz-1){
+            right.pb(s);
+            continue;
+        }
+        center.pb(s);
+    }
+    str contigious = "";
+    if(right.sz>=2)
+        return v(str)();
+    if(right.sz == 1)
+        contigious += right[0];
+    contigious += allsameconcat;
+    if(left.sz >= 2)
+        return v(str)();
+    if(left.sz == 1)
+        contigious += left[0];
+    if(center.sz >= 2)
+        return v(str)();
+    if(center.sz == 1 && contigious.sz > 0)
+        return v(str)();
+    if(center.sz == 1)
+        contigious += center[0];
+    if(contigious.sz > 0)
+        rest.pb(contigious);
+    return rest;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(str) reductions = Si;
+    forn(i, 26){
+        reductions = reduce_letter('A'+i, reductions);
+        if(reductions.sz == 0){
+            result = "IMPOSSIBLE";
+            return;
+        }
+    }
+    result = "";
+    foreach(s, reductions)
+        result += s;
 }
 
 } // namespace task
