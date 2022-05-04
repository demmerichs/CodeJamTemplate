diff --git a/CodeJam/Main.cpp b/examples/2021/Round1B/C/Main.cpp
index 00aa56c..6e577a5 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1B/C/Main.cpp
@@ -1,9 +1,9 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
-#define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
+// #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
@@ -1540,8 +1540,86 @@ using namespace std;
 
 namespace task {
 
+ll N, B, P;
+
+ld dp[21][21][21][14];
+
+void recur(ll n14, ll n13, ll n0aprog, ll nprog){
+    lassert(n14 >= 0, "n14 neg");
+    lassert(n14 <= 20, "n14 too large");
+    lassert(n0aprog >= 0, "n0aprog neg");
+    lassert(n0aprog <= 20, "n0aprog too large");
+    lassert(nprog >= 0, "nprog neg");
+    lassert(nprog <= 13, "nprog too large");
+    if(dp[n14][n13][n0aprog][nprog] >= 0.0) return;
+    lg(n14);
+    lg(n13);
+    lg(n0aprog);
+    lg(nprog);
+    ld cursum = 0;
+    forn(d, 10){
+        ld poss2finish = 0.0;
+        if(n14>0){
+            recur(n14-1, n13, n0aprog, nprog);
+            poss2finish = dp[n14-1][n13][n0aprog][nprog] + d * 1e14;
+        }
+        ld poss2prefinish = 0.0;
+        if(n13>0){
+            recur(n14+1, n13-1, n0aprog, nprog);
+            poss2prefinish = dp[n14+1][n13-1][n0aprog][nprog] + d * 1e13;
+        }
+        ld poss2prog = 0.0;
+        if(n0aprog > 0){
+            ll newn14 = n14;
+            ll newn13 = n13;
+            ll newn0aprog = n0aprog;
+            ll newnprog = nprog + 1;
+            if(nprog==12){
+                newn13++;
+                newn0aprog--;
+                newnprog=0;
+            }
+            recur(newn14, newn13, newn0aprog, newnprog);
+            poss2prog = dp[newn14][newn13][newn0aprog][newnprog] + d * pow(10, nprog);
+        }
+        cursum += max({poss2finish, poss2prefinish, poss2prog});
+    }
+    cursum /= 10.0;
+    dp[n14][n13][n0aprog][nprog] = cursum;
+}
+
+ll buildprog(ll n14, ll n13, ll n0aprog, ll nprog, ll d){
+    ld poss2finish = 0.0;
+    if(n14>0){
+        poss2finish = dp[n14-1][n13][n0aprog][nprog] + d * 1e14;
+    }
+    ld poss2prefinish = 0.0;
+    if(n13>0){
+        poss2prefinish = dp[n14+1][n13-1][n0aprog][nprog] + d * 1e13;
+    }
+    ld poss2prog = 0.0;
+    if(n0aprog > 0){
+        ll newn14 = n14;
+        ll newn13 = n13;
+        ll newn0aprog = n0aprog;
+        ll newnprog = nprog + 1;
+        if(nprog==12){
+            newn13++;
+            newn0aprog--;
+            newnprog=0;
+        }
+        poss2prog = dp[newn14][newn13][newn0aprog][newnprog] + d * pow(10, nprog);
+    }
+    ld maxresult = max({poss2finish, poss2prefinish, poss2prog});
+    return maxresult == poss2finish?0:(maxresult==poss2prefinish?1:2);
+}
+
 void init(){
-    cin >> T;
+    cin >> T >> N >> B >> P;
+    forn(i, 21) forn(j, 21) forn(k, 21) forn(m, 14) dp[i][j][k][m] = -1.0;
+    recur(0, 0, N, 0);
+    lg(dp[0][0][N][0]);
+    lg(T*dp[0][0][N][0]);
 }
 
 void readInput(){
@@ -1549,6 +1627,36 @@ void readInput(){
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll n14 = 0;
+    ll n13 = 0;
+    ll n0aprog = N;
+    ll nprog = 0;
+    forn(i, N*B){
+        ll D = in();
+        ll mode = buildprog(n14, n13, n0aprog, nprog, D);
+        switch(mode){
+        case 0:
+            lassert(n14>0, "there is no 14 tower");
+            out(N-n0aprog-n14-n13+1);
+            n14--;
+            break;
+        case 1:
+            lassert(n13>0, "there is no 13 tower");
+            out(N-n0aprog-n13+1);
+            n13--;
+            n14++;
+            break;
+        case 2:
+            out(N-n0aprog+1);
+            nprog++;
+            if(nprog == 13){
+                n13++;
+                n0aprog--;
+                nprog = 0;
+            }
+            break;
+        }
+    }
 }
 
 } // namespace task
