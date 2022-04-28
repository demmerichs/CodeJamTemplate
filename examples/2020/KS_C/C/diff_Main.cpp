diff --git a/CodeJam/Main.cpp b/examples/2020/KS_C/C/Main.cpp
index fa1026d..863860b 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_C/C/Main.cpp
@@ -1410,15 +1410,48 @@ using namespace std;
 
 namespace task {
 
+const ll offset = 10000000;
+v(ll) sqrs;
+v(ll) cumsumc;
+
 void init(){
     cin >> T;
+    ll c = 0;
+    while(true){
+        sqrs.pb(c*c);
+        if(sqrs.bk>=offset) break;
+        c++;
+    }
 }
 
+int N;
+v(int) Ai;
+
 void readInput(){
+    cin >> N;
+    Ai.resize(N);
+    forn(i, N) cin >> Ai[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+
+    cumsumc.assign(2*offset+1, 0);
+    cumsumc[0+offset]=1;
+    lg(cumsumc[0]);
+    lg(cumsumc[2*offset]);
+    int sum = 0;
+    forn(i, N){
+        sum += Ai[i];
+        lg(sum);
+        foreach(sq, sqrs){
+            if(offset+sum-sq <0)break;
+            if(offset+sum-sq>=2*offset+1) continue;
+            result += cumsumc[offset+sum-sq];
+        }
+        cumsumc[offset+sum]++;
+    }
 }
 
 } // namespace task
