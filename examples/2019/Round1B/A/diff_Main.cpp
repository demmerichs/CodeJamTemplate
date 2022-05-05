diff --git a/CodeJam/Main.cpp b/examples/2019/Round1B/A/Main.cpp
index e05e235..73cbe1b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1B/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1555,11 +1555,59 @@ void init(){
     cin >> T;
 }
 
+ll P, Q;
+v(cell) persons;
+v(cell) directions;
+v(char) dirnames;
+d(ll, ll) xcounts;
+d(ll, ll) ycounts;
+
 void readInput(){
+    cin >> P >> Q;
+    xcounts.cl;
+    ycounts.cl;
+    persons.cl;
+    directions.cl;
+    dirnames.cl;
+    forn(i, P){
+        ll xi, yi;
+        char dir;
+        cin >> xi >> yi >> dir;
+        persons.pb(cell(xi, yi));
+        directions.pb(DIRECTIONS[DIR_IDX[dir]]);
+        dirnames.pb(dir);
+        if(dir == 'N'){
+            ycounts[yi+1]++;
+        } else if(dir == 'S'){
+            ycounts[yi]--;
+        } else if(dir == 'E'){
+            xcounts[xi + 1]++;
+        } else if(dir == 'W'){
+            xcounts[xi]--;
+        } else {
+            lassert(false, "logic error");
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll bestx=0, besty=0, cx=0, cy=0, bestcx=0, bestcy=0;
+    foreach(xcount, xcounts){
+        cx += xcount.nd;
+        if(cx > bestcx){
+            bestx = xcount.st;
+            bestcx = cx;
+        }
+    }
+    foreach(ycount, ycounts){
+        cy += ycount.nd;
+        if(cy > bestcy){
+            besty = ycount.st;
+            bestcy = cy;
+        }
+    }
+    result = to_string(bestx) + " " + to_string(besty);
 }
 
 } // namespace task
