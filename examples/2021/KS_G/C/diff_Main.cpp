diff --git a/CodeJam/Main.cpp b/examples/2021/KS_G/C/Main.cpp
index 883b228..873a15e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_G/C/Main.cpp
@@ -1065,11 +1065,47 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
+v(ll) Bi, csBi;
+
 void readInput(){
+    cin >> N >> K;
+    Bi.resize(N);
+    csBi.resize(N+1);
+    forn(i, N) cin >> Bi[i];
+    csBi[0] = 0;
+    forn(i, N) csBi[i+1] = csBi[i] + Bi[i];
+}
+
+ll intsum(ll a, ll b){
+    return csBi[b]-csBi[a];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = INF/2;
+
+    // smallestIntUpToA[s] denotes the length of the smallest interval from
+    // 0 to a (see following loop parameter) with sum s
+    v(ll) smallestIntUpToA(K+1, INF/2);
+    smallestIntUpToA[0] = 0;
+
+    forn(a, N+1){
+        fornn(b, a, N+1){
+            ll sum = intsum(a, b);
+            ll rest = K-sum;
+            if(rest>=0){
+                result = min(result, b-a+smallestIntUpToA[rest]);
+            }
+        }
+        forn(b, a+1){
+            ll sum = intsum(b, a);
+            if(sum<=K){
+                smallestIntUpToA[sum] = min(smallestIntUpToA[sum], a-b);
+            }
+        }
+    }
+    if(result > N) result = -1;
 }
 
 } // namespace task
