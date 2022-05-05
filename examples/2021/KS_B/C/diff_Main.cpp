diff --git a/CodeJam/Main.cpp b/examples/2021/KS_B/C/Main.cpp
index 2150379..9a16068 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_B/C/Main.cpp
@@ -1570,11 +1570,32 @@ void init(){
     cin >> T;
 }
 
+ll Z;
+
 void readInput(){
+    cin >> Z;
+}
+
+bool isprime(ll p){
+    ll sq = sqrtl(p);
+    fore(i, 2, sq){
+        if(p%i==0) return false;
+    }
+    return true;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll sq = sqrtl(Z);
+    ll p1 = sq;
+    while(!isprime(p1)) p1--;
+    ll p2 = sq+1;
+    while(!isprime(p2)) p2++;
+    result = p1*p2;
+    if(result <= Z) return;
+    p2 = p1-1;
+    while(!isprime(p2)) p2--;
+    result = p1 * p2;
 }
 
 } // namespace task
