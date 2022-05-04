diff --git a/CodeJam/Main.cpp b/examples/2020/Round1C/B/Main.cpp
index 05e1aa9..85aa27e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1C/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1540,11 +1540,46 @@ void init(){
     cin >> T;
 }
 
+ll U;
+v(ll) Mi;
+v(str) randres;
+s(char) used_letters;
+
 void readInput(){
+    cin >> U;
+    Mi.cl;
+    randres.cl;
+    used_letters.cl;
+
+    forn(i, 10000){
+        ll mi;
+        str res;
+        cin >> mi >> res;
+        Mi.pb(mi);
+        randres.pb(res);
+        foreach(let, res){
+            used_letters.insert(let);
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    d(char, ll) occ;
+    forn(i, randres.sz){
+        occ[randres[i][0]] += 1;
+    }
+    llog("occ", occ);
+    d(ll, char) neg_counts;
+    foreach(it, occ)
+        neg_counts[-it.nd] = it.st;
+    llog("neg_counts", neg_counts);
+    result = "";
+    foreach(it, neg_counts){
+        result += it.nd;
+        used_letters.erase(it.nd);
+    }
+    result = *used_letters.bn + result;
 }
 
 } // namespace task
