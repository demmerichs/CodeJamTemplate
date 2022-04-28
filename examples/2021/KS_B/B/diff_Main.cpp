diff --git a/CodeJam/Main.cpp b/examples/2021/KS_B/B/Main.cpp
index fa1026d..b67991c 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_B/B/Main.cpp
@@ -1414,11 +1414,49 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) Ai;
+
 void readInput(){
+    cin >> N;
+    Ai.resize(N+1);
+    Ai[0] = 0;
+    forn(i, N) cin >> Ai[i+1];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    forn(mode, 2){
+        Ai.pb(0);
+        reverse(all(Ai));
+        Ai.popb;
+        lg(Ai);
+
+        ll nextnum0 = 0, nextnum1 = 0, count0 = 0, count1 = 0, del1= 0;
+        forn(i, N){
+            ll del = Ai[i+1]-Ai[i];
+            lg(del);
+            if(nextnum1 == Ai[i+1]){
+                nextnum1 += del1;
+                count1++;
+            } else {
+                count1 = count0 + 1;
+                del1 = nextnum0 - Ai[i];
+                nextnum1 = nextnum0 + del1;
+            }
+            if(nextnum0 == Ai[i+1]){
+                nextnum0 += del;
+                count0++;
+            } else {
+                count0 = min(i+1, 2LL);
+                nextnum0 = 2*Ai[i+1]-Ai[i];
+            }
+            result = max(result, count0);
+            result = max(result, count1);
+            lg(result);
+        }
+    }
 }
 
 } // namespace task
