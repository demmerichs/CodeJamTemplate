diff --git a/CodeJam/Main.cpp b/examples/2020/Round2/C/Main.cpp
index b62b2a6..44a82fe 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round2/C/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1020,11 +1020,63 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(cell) holes;
+
 void readInput(){
+    cin >> N;
+    holes.cl;
+    forn(i, N){
+        ll t1, t2;
+        cin >> t1 >> t2;
+        holes.pb(cell(t1, t2));
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = N<=2?N:2;
+    d(ll, ll) counts;
+    forn(i, N){
+        fornn(j, i+1, N){
+            counts.cl;
+
+            cell grad=holes[i] - holes[j];
+            if(grad.x < 0 && grad.y < 0){
+                grad *= -1;
+            }
+            if(grad.x * grad.y ==0){
+                grad /= (grad.x + grad.y);
+            } else{
+                ll g = gcd(grad.x, grad.y);
+                grad /= g;
+            }
+            cell ortho_grad(-grad.y, grad.x);
+            llog("cur grad", grad);
+            llog("ortho_grad", ortho_grad);
+            forn(ci, N){
+                ll sp = ortho_grad.x * holes[ci].x + ortho_grad.y * holes[ci].y;
+                // llog("scalar product between", ortho_grad, "and", holes[ci], "is", sp);
+                counts[sp]++;
+            }
+
+            llog("counts");
+            llog(counts);
+
+            ll singles=0;
+            ll odds=0;
+            foreach(c, counts){
+                if(c.nd==1) singles++;
+                else if(c.nd%2==1) odds++;
+            }
+
+            llog("singles", singles, "odds", odds);
+            if(odds %2 == 0)
+                result = max<ll>(result, holes.sz-max<ll>(0, singles-2));
+            else
+                result = max<ll>(result, holes.sz-max<ll>(0, singles-1));
+        }
+    }
 }
 
 } // namespace task
