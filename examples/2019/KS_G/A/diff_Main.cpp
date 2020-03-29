diff --git a/CodeJam/Main.cpp b/examples/2019/KS_G/A/Main.cpp
index fe07306..e02e56b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/KS_G/A/Main.cpp
@@ -799,14 +799,80 @@ using namespace std;
 
 namespace task {
 
+v(dict(ll, ll)) pfc;
+
 void init(){
+    forn(i, 100000){
+        dict(ll, ll) result;
+        ll startprime=2;
+        ll cur = i+1;
+        while(startprime*startprime<=cur){
+            if(cur % startprime == 0){
+                cur /= startprime;
+                result[startprime]++;
+            } else {
+                startprime++;
+            }
+        }
+        if(cur>1){
+
+            result[cur]++;
+        }
+        pfc.pb(result);
+    }
 }
 
+ll N, Q, M;
+v(ll) Ri, Pi;
+dict(ll, ll) Rc;
 void readInput(){
+    cin >> N >> M >> Q;
+    Ri.clear();
+    Pi.clear();
+    Rc.clear();
+    forn(i, M){
+        ll t;
+        cin >> t;
+        Pi.pb(t);
+    }
+    forn(i, Q){
+        ll t;
+        cin >> t;
+        Ri.pb(t);
+        Rc[t]++;
+    }
+}
+
+v(ll) listofdivisors(dict(ll, ll) pf){
+    v(ll) result;
+    result.pb(1);
+    foreach(it, pf){
+        ll curlen = result.sz;
+        ll fac = 1;
+        forn(i, it->nd){
+            fac *= it->st;
+            forn(j, curlen){
+                result.pb(result[j] * fac);
+            }
+        }
+    }
+    return result;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    forn(i, Q){
+        result += N / Ri[i];
+    }
+    forn(i, M){
+        dict(ll, ll) pf=pfc[Pi[i]-1];
+        v(ll) divs = listofdivisors(pf);
+        llog("Pi:", Pi[i], "divs:", divs);
+        forn(k, divs.sz){
+            result -= Rc[divs[k]];
+        }
+    }
 }
 
 } // namespace task
