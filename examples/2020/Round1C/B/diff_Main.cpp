diff --git a/CodeJam/Main.cpp b/examples/2020/Round1C/B/Main.cpp
index a548e30..74eace7 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1C/B/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -999,11 +999,46 @@ namespace task {
 void init(){
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
