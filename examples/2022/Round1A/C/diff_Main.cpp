diff --git a/CodeJam/Main.cpp b/examples/2022/Round1A/C/Main.cpp
index 05e1aa9..0e57cf8 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Round1A/C/Main.cpp
@@ -1540,11 +1540,54 @@ void init(){
     cin >> T;
 }
 
+ll E, W;
+v(v(ll)) Xew;
+d(p(ll, ll), ll) dp;
+
 void readInput(){
+    cin >> E >> W;
+    Xew.cl;
+    Xew.resize(E, v(ll)(W));
+    forn(e, E){
+        forn(w, W)
+            cin >> Xew[e][w];
+    }
+    lg(Xew);
+    dp.cl;
+    forn(e, E)
+        dp[mp(e, e)] = 0;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    fornn(l, 1, E){
+        forn(s, E-l){
+            p(ll, ll) key = mp(s, s+l);
+            v(ll) mins = Xew[s];
+            forn(i, l){
+                forn(w, W){
+                    mins[w] = min(mins[w], Xew[s+i+1][w]);
+                }
+            }
+            lg(s);
+            lg(l);
+            lg(mins);
+            ll total_mins = accumulate(all(mins), 0);
+            ll best = total_mins * l;
+            forn(i, l){
+                ll leftk = dp[mp(s, s+i)];
+                ll rightk = dp[mp(s+i+1, s+l)];
+                ll cur_best = leftk + rightk + total_mins;
+                best = max(best, cur_best);
+            }
+            dp[key] = best;
+            lg(best);
+        }
+    }
+    ll sum_X = 0;
+    forn(e, E)
+        sum_X += accumulate(all(Xew[e]), 0);
+    result = sum_X * 2 - 2 * dp[mp(0, E-1)];
 }
 
 } // namespace task
