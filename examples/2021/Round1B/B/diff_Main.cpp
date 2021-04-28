diff --git a/CodeJam/Main.cpp b/examples/2021/Round1B/B/Main.cpp
index 42da9e7..0690fd5 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1B/B/Main.cpp
@@ -1,5 +1,5 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
@@ -1024,11 +1024,67 @@ void init(){
     cin >> T;
 }
 
+ll N, A, B, smallestU;
+v(ll) Ui;
+
 void readInput(){
+    cin >> N >> A >> B;
+    Ui.resize(N);
+    forn(i, N) cin >> Ui[i];
+    smallestU = N;
+    forn(i, N){
+        if (Ui[i] > 0){
+            smallestU = i+1;
+            break;
+        }
+    }
+}
+
+bool simulate(d(ll, ll) curmetals, v(ll) needed){
+    ll largest_needed = 0;
+    forn(i, N){
+        if(needed[i] > 0) largest_needed = i+1;
+    }
+    lg(largest_needed);
+    if (largest_needed == 0) return true;
+    if(curmetals.sz == 0) return false;
+    lg(curmetals);
+    lg(needed);
+    lg(*curmetals.rbegin());
+    ll largestmetal = curmetals.rbegin()->st;
+    lg(largestmetal);
+    if(largest_needed == largestmetal){
+        curmetals[largestmetal] -= needed[largestmetal-1];
+        needed[largestmetal-1] = 0;
+        if(curmetals[largestmetal] < 0) return false;
+    }
+    else if(largest_needed > largestmetal) return false;
+    lg(curmetals);
+    if(largestmetal > A)
+        curmetals[largestmetal-A] = dget(curmetals, largestmetal-A, 0LL) + curmetals[largestmetal];
+    if(largestmetal > B)
+        curmetals[largestmetal-B] = dget(curmetals, largestmetal-B, 0LL) + curmetals[largestmetal];
+    curmetals.erase(largestmetal);
+    return simulate(curmetals, needed);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll g = gcd(A, B);
+    forn(i, N){
+        if(Ui[i] == 0) continue;
+        if( (i+1 - smallestU) % g != 0) {
+            lg(i+1);
+            lg(smallestU);
+            lg(g);
+            return;
+        }
+    }
+    while(true){
+        result++;
+        if(simulate({{result, 1}}, Ui)) break;
+    }
 }
 
 } // namespace task
