diff --git a/CodeJam/Main.cpp b/examples/2021/KS_F/A/Main.cpp
index 0f47b9d..4953ac2 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_F/A/Main.cpp
@@ -1569,11 +1569,41 @@ void init(){
     cin >> T;
 }
 
+ll N;
+str S;
+
 void readInput(){
+    cin >> N;
+    cin >> S;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    v(ll) walkleft, walkright;
+
+    ll cur = INF/2;
+    forn(i, N){
+        if(S[i] == '0')
+            walkleft.pb(cur+1);
+        else
+            walkleft.pb(0);
+        cur = walkleft.bk;
+    }
+    cur = INF/2;
+    forn(i, N){
+        ll j = N-1-i;
+        if(S[j] == '0')
+            walkright.pb(cur + 1);
+        else
+            walkright.pb(0);
+        cur = walkright.bk;
+    }
+
+    forn(i, N){
+        ll j = N-1-i;
+        result += min(walkleft[i], walkright[j]);
+    }
 }
 
 } // namespace task
