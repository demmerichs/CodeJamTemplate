diff --git a/CodeJam/Main.cpp b/examples/2018/Round2/B/Main.cpp
index b6f94e8..3747fae 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round2/B/Main.cpp
@@ -3,7 +3,7 @@
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1013,11 +1013,54 @@ namespace task {
 void init(){
 }
 
+ll R, B;
+cell cb;
+
 void readInput(){
+    cin >> R >> B;
+    if(R<B){
+        ll t = R;
+        R=B;
+        B=t;
+    }
+    cb = cell(R, B);
+    llog(R, B, cb);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(cell) ps;
+    forn(r, R+1){
+        forn(b, B+1){
+            ll bound_r = (b+1) * r * (r+1) /2 ;
+            ll bound_b = (r+1) * b * (b+1) / 2;
+            if(bound_r > R || bound_b > B){
+                break;
+            }
+            ps.pb(cell(b,r));
+        }
+    }
+    llog(ps);
+    v(v(v(ll))) dp(ps.sz+1, v(v(ll))(B+1, v(ll)(R+1, 0)));
+    dp[0][0][0] = 0;
+    result = 0;
+    fore(i, 1, ps.sz){
+        llog("i", i);
+        cell &cur = ps[i-1];
+        llog(cur);
+        forn(b, B+1){
+            // llog("b", b);
+            forn(r, R+1){
+                // llog("r", r);
+                if(b<cur.x || r < cur.y){
+                    dp[i][b][r] = dp[i-1][b][r];
+                    continue;
+                }
+                dp[i][b][r] = max(dp[i-1][b][r], 1+dp[i-1][b-cur.x][r-cur.y]);
+            }
+        }
+    }
+    result = dp[ps.sz][B][R]-1;
 }
 
 } // namespace task
