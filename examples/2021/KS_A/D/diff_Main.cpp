diff --git a/CodeJam/Main.cpp b/examples/2021/KS_A/D/Main.cpp
index e05e235..e8d5d45 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_A/D/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1555,11 +1555,46 @@ void init(){
     cin >> T;
 }
 
+ll N;
+ll Bi[500][500];
+
 void readInput(){
+    cin >> N;
+    ll t;
+    forn(r, N) forn(c, N) cin >> t;
+    forn(r, N) forn(c, N) cin >> Bi[r][c];
+    forn(r, N) cin >> t;
+    forn(c, N) cin >> t;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    forn(r, N) forn(c, N) result += Bi[r][c];
+
+    v(bool) visitedR(N, false);
+    v(bool) visitedC(N, false);
+    priority_queue<p(ll, cell)> pq;
+    visitedR[0] = true;
+    forn(c, N) pq.push(mp(Bi[0][c], cell(0, c)));
+
+    ll visit_count = 1;
+    while(visit_count < 2*N){
+        p(ll, cell) curp = pq.top();
+        cell cur = curp.nd;
+        pq.pop();
+        if(visitedR[cur.x] && visitedC[cur.y]) continue;
+        result-= curp.st;
+        visit_count++;
+        if(visitedR[cur.x]){
+            visitedC[cur.y] = true;
+            forn(r, N) pq.push(mp(Bi[r][cur.y], cell(r, cur.y)));
+        } else {
+            lassert(visitedC[cur.y], "at least one should have been visited before");
+            visitedR[cur.x] = true;
+            forn(c, N) pq.push(mp(Bi[cur.x][c], cell(cur.x, c)));
+        }
+    }
 }
 
 } // namespace task
