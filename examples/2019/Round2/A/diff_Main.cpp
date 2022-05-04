diff --git a/CodeJam/Main.cpp b/examples/2019/Round2/A/Main.cpp
index 05e1aa9..f1f8f2d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round2/A/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1540,11 +1540,36 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(cell) mols;
+s(ld) ratios;
+
 void readInput(){
+    cin >> N;
+    mols.cl;
+    ratios.cl;
+    forn(i, N){
+        ll s, t;
+        cin >> s >> t;
+        mols.emplace_back(s,t);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    forn(i, N){
+        fornn(j, i+1, N){
+            if(mols[i].x >= mols[j].x && mols[i].y >= mols[j].y) continue;
+            if(mols[i].x <= mols[j].x && mols[i].y <= mols[j].y) continue;
+            ll delx = abs(mols[i].x - mols[j].x);
+            ll dely = abs(mols[i].y - mols[j].y);
+            ll g = gcd(delx, dely);
+            delx /= g;
+            dely /= g;
+            ratios.insert(ld(delx) / dely);
+        }
+    }
+    result = 1 + ratios.sz;
 }
 
 } // namespace task
