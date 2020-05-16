diff --git a/CodeJam/Main.cpp b/examples/2020/Round1C/C/Main.cpp
index e858c1d..43cccb7 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1C/C/Main.cpp
@@ -3,7 +3,7 @@
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1012,11 +1012,58 @@ namespace task {
 void init(){
 }
 
+ll N, D;
+d(ll,ll) Ai;
+d(cell, cell) num_saves_per_fraction;
+
 void readInput(){
+    cin >> N >> D;
+    Ai.cl;
+    num_saves_per_fraction.cl;
+    forn(i, N){
+        ll t;
+        cin >> t;
+        Ai[t]++;
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll max_cut_saves = 1;
+    foreach(ai, Ai){
+        fore(d, 1, D){
+            cell frac(ai.st, d);
+            frac_reduce(frac);
+            llog("cur slice", frac);
+            llog("can produce ", ai.nd,"*", d,"=", ai.nd*d, "slices");
+            llog("and save", ai.nd, "cuts");
+            cell cur_num_saves = dget(num_saves_per_fraction, frac, cell(0, 0));
+            llog("cur num saves before", cur_num_saves);
+            forn(i, ai.nd){
+                cur_num_saves += cell(d, 1);
+                if(cur_num_saves.x <= D){
+                    if(cur_num_saves.y > max_cut_saves){
+                        llog("poss candidate slice size", frac);
+                        ll nbr_counts_possible=0;
+                        foreach(cai, Ai){
+                            nbr_counts_possible += floorll(cai.st * frac.y,frac.x) * cai.nd;
+                            llog(cai);
+                            llog(nbr_counts_possible);
+                            if(nbr_counts_possible>=D) break;
+                        }
+                        if(nbr_counts_possible>=D){
+                            llog("there were enough slices available of that size", nbr_counts_possible);
+                            max_cut_saves = cur_num_saves.y;
+                        }
+                    } else
+                        llog("this candidate did not save enough cuts");
+                }
+            }
+            llog("cur num saves after", cur_num_saves);
+            num_saves_per_fraction[frac] = cur_num_saves;
+        }
+    }
+    result = D - max_cut_saves;
 }
 
 } // namespace task
