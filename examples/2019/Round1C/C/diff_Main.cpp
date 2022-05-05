diff --git a/CodeJam/Main.cpp b/examples/2019/Round1C/C/Main.cpp
index f8bdafd..355fcbc 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1C/C/Main.cpp
@@ -1568,11 +1568,83 @@ void init(){
     cin >> T;
 }
 
+ll R, C;
+bool block[15][15];
+ll nimber[16][16][16][16];
+
 void readInput(){
+    cin >> R >> C;
+    char t;
+    forn(r, R) forn(c, C){
+        cin >> t;
+        block[r][c] = t=='#';
+    }
+    forn(i, 16) forn(j, 16) forn(k, 16) forn(l, 16) nimber[i][j][k][l] = -1;
+}
+
+ll mex(s(ll) vals){
+    ll c = 0;
+    foreach(v, vals){
+        if(v==c){
+            c++;
+            continue;
+        }
+        return c;
+    }
+    return c;
+}
+
+ll recur(ll rl, ll ru, ll clow, ll cu){
+    if(nimber[rl][ru][clow][cu] >= 0) return -1;
+    if(rl == ru || clow == cu){
+        nimber[rl][ru][clow][cu] = 0;
+        return 0;
+    }
+    lassert(rl<ru, "no valid row bounds");
+    lassert(0<=rl, "no valid row bounds");
+    lassert(ru<=R, "no valid row bounds");
+    lassert(clow<cu, "no valid col bounds");
+    lassert(0<=clow, "no valid col bounds");
+    lassert(cu<=C, "no valid col bounds");
+
+    s(ll) found_nimber_moves;
+    ll win_move_count = 0;
+
+    fornn(rmove, rl, ru){
+        bool move_valid=true;
+        fornn(c, clow, cu)
+            if(block[rmove][c]){
+                move_valid=false;
+                break;
+            }
+        if(!move_valid) continue;
+        recur(rl, rmove, clow, cu);
+        recur(rmove+1, ru, clow, cu);
+        ll cur_nimber = nimber[rl][rmove][clow][cu] ^ nimber[rmove+1][ru][clow][cu];
+        if(cur_nimber == 0) win_move_count+=cu-clow;
+        found_nimber_moves.insert(cur_nimber);
+    }
+    fornn(cmove, clow, cu){
+        bool move_valid=true;
+        fornn(r, rl, ru)
+            if(block[r][cmove]){
+                move_valid=false;
+                break;
+            }
+        if(!move_valid) continue;
+        recur(rl, ru, clow, cmove);
+        recur(rl, ru, cmove+1, cu);
+        ll cur_nimber = nimber[rl][ru][clow][cmove] ^ nimber[rl][ru][cmove+1][cu];
+        if(cur_nimber == 0) win_move_count+=ru-rl;
+        found_nimber_moves.insert(cur_nimber);
+    }
+    nimber[rl][ru][clow][cu] = mex(found_nimber_moves);
+    return win_move_count;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = recur(0, R, 0, C);
 }
 
 } // namespace task
