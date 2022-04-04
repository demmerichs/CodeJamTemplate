diff --git a/CodeJam/Main.cpp b/examples/2021/Round1A/B/Main.cpp
index 6e1211d..1f9bde2 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1A/B/Main.cpp
@@ -1065,11 +1065,49 @@ void init(){
     cin >> T;
 }
 
+ll N, S;
+v(ll) Pi, Ni;
+
 void readInput(){
+    cin >> N;
+    Pi.resize(N);
+    Ni.resize(N);
+    S = 0;
+    forn(i, N){
+        cin >> Pi[i] >> Ni[i];
+        S += Pi[i] * Ni[i];
+    }
+    lg(S);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    ll maxprodcards = log2ll(S);
+    lg(maxprodcards);
+    result = 0;
+    ll start_sum = S-1;
+    while(start_sum >= S - maxprodcards * 499 && start_sum >= 1){
+        ll left_factors = start_sum;
+        ll sum_of_factors = 0;
+        forn(i, N){
+            ll ni = 0;
+            while(left_factors % Pi[i] == 0){
+                ni++;
+                left_factors /= Pi[i];
+                sum_of_factors += Pi[i];
+            }
+            if(ni > Ni[i]){
+                sum_of_factors = 0;
+                break;
+            }
+            if(left_factors == 1) break;
+        }
+        if(start_sum == S-sum_of_factors && left_factors == 1){
+            result = start_sum;
+            break;
+        }
+        start_sum--;
+    }
 }
 
 } // namespace task
