diff --git a/CodeJam/Main.cpp b/examples/2022/KS_A/C/Main.cpp
index 00aa56c..9804b84 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/KS_A/C/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1540,15 +1540,80 @@ using namespace std;
 
 namespace task {
 
+bool contains5palindrom(ll n){
+    if((((n>>0)&1) == ((n>>4)&1)) && (((n>>1)&1) == ((n>>3)&1))){
+        lg(n);
+        lg("contains 5");
+        return true;
+    }
+    return false;
+}
+
+bool contains5or6palindrom(ll n){
+    if(contains5palindrom(n%(1<<5)) || contains5palindrom(n>>1))
+        return true;
+    if(((n>>0)&1) == ((n>>5)&1) && ((n>>1)&1) == ((n>>4)&1) && ((n>>2)&1) == ((n>>3)&1))
+        return true;
+    return false;
+}
+
+v(bool) contains5or6;
+
 void init(){
     cin >> T;
+    forn(i, 64){
+        contains5or6.pb(contains5or6palindrom(i));
+    }
+    lg(contains5or6);
 }
 
+ll N;
+str S;
+
 void readInput(){
+    cin >> N >> S;
 }
 
+
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "POSSIBLE";
+    if(N<5) return;
+
+    s(ll) poss;
+    poss.insert(0);
+    lg(poss);
+
+    forn(i, N){
+        s(ll) newposs;
+        if(S[i]=='0' || S[i]=='?'){
+            foreach(p, poss){
+                ll n = (p*2)%(1<<6);
+                if(i<5 || !contains5or6[n])
+                    newposs.insert(n);
+            }
+        }
+        if(S[i]=='1' || S[i]=='?'){
+            foreach(p, poss){
+                ll n = (p*2+1)%(1<<6);
+                if(i<5 || !contains5or6[n])
+                    newposs.insert(n);
+            }
+        }
+        poss = newposs;
+        lg(poss);
+        if(poss.sz == 0){
+            result = "IMPOSSIBLE";
+            break;
+        }
+    }
+    if(N==5){
+        result = "IMPOSSIBLE";
+        foreach(p, poss){
+            if(!contains5palindrom(p))
+                result = "POSSIBLE";
+        }
+    }
 }
 
 } // namespace task
