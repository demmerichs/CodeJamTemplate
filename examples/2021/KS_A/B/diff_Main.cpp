diff --git a/CodeJam/Main.cpp b/examples/2021/KS_A/B/Main.cpp
index 883b228..937693e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_A/B/Main.cpp
@@ -1065,11 +1065,72 @@ void init(){
     cin >> T;
 }
 
+ll R, C;
+
+bool grid[1000][1000];
+ll distrl[1000][1000], distru[1000][1000], distcl[1000][1000], distcu[1000][1000];
+
 void readInput(){
+    cin >> R >> C;
+    forn(r, R) forn(c, C) cin >> grid[r][c];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll counter = 0;
+    forn(r, R){
+        counter = 0;
+        forn(c, C){
+            if(grid[r][c]) counter++;
+            else counter=0;
+            distrl[r][c] = counter;
+        }
+        counter = 0;
+        forn(c, C){
+            ll invc = C-c-1;
+            if(grid[r][invc]) counter++;
+            else counter = 0;
+            distru[r][invc] = counter;
+        }
+    }
+    forn(c, C){
+        counter = 0;
+        forn(r, R){
+            if(grid[r][c]) counter++;
+            else counter=0;
+            distcl[r][c] = counter;
+        }
+        counter = 0;
+        forn(r, R){
+            ll invr = R-r-1;
+            if(grid[invr][c]) counter++;
+            else counter = 0;
+            distcu[invr][c] = counter;
+        }
+    }
+    result = 0;
+    forn(r, R)
+        forn(c, C){
+            lg(r);
+            lg(c);
+            ll curvals[5];
+            curvals[0] = distrl[r][c];
+            curvals[1] = distcl[r][c];
+            curvals[2] = distru[r][c];
+            curvals[3] = distcu[r][c];
+            curvals[4] = distrl[r][c];
+            forn(i, 4){
+                ll a = curvals[i];
+                ll b = curvals[i+1];
+                lg(i);
+                lg(a);
+                lg(b);
+                if(a<=1) continue;
+                if(b<=1) continue;
+                result += max(min(b/2,a)-1, 0LL);
+                result += max(min(b,a/2)-1, 0LL);
+            }
+        }
 }
 
 } // namespace task
