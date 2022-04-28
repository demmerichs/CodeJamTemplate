diff --git a/CodeJam/Main.cpp b/examples/2021/Round1C/C/Main.cpp
index a7f0d62..b1e877e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1C/C/Main.cpp
@@ -1,5 +1,5 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result == -1
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
@@ -1501,11 +1501,111 @@ void init(){
     cin >> T;
 }
 
+str S, E;
+
 void readInput(){
+    cin >> S >> E;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    if(S==E){
+        return;
+    }
+    if(S=="0"){
+        result = 1;
+        S = "1";
+    }
+
+    dq(ll) s, e;
+    lg(S);
+    lg(E);
+    forn(i, S.sz){
+        if(S[i]-'0' == s.sz%2){
+            s.bk++;
+        } else {
+            s.pb(1);
+        }
+    }
+    if(E!="0"){
+        forn(i, E.sz){
+            if(E[i]-'0' == e.sz%2){
+                e.bk++;
+            } else {
+                e.pb(1);
+            }
+        }
+    }
+    lg(s);
+    lg(e);
+    if(E=="0"){
+        result += s.sz;
+        return;
+    }
+
+    if(s.sz + (s.sz%2) < e.sz){
+        result = -1;
+        return;
+    }
+
+    while(s.sz > (e.sz+1)/2*2){
+        s.popf;
+        result++;
+    }
+    while(s!=e){
+        ll pivot = max<ll>(s.sz-e.sz, 0LL);
+        while(true){
+            if(pivot == s.sz) break;
+            bool pivot_works = true;
+            fornn(i, pivot, s.sz-1){
+                if(s[i]!=e[i-pivot]){
+                    pivot_works=false;
+                    break;
+                }
+            }
+            if(s.bk > e[s.sz-pivot-1]) pivot_works=false;
+            if(s.sz%2==1){
+                if(s.bk < e[s.sz-pivot-1]) pivot_works=false;
+            }
+            if(pivot_works){
+                break;
+            } else {
+                pivot++;
+            }
+        }
+        lg(s);
+        lg(e);
+        lg(pivot);
+        if(pivot == s.sz){
+            if(s.sz % 2 == 0){
+                s.popf;
+                result++;
+                pivot--;
+                continue;
+            } else {
+                s.pb(1);
+                result++;
+                continue;
+            }
+        }
+        if(s.sz%2==0){
+            if(s.bk < e[s.sz-pivot-1]){
+                s.bk++;
+                result++;
+                continue;
+            }
+            if(s.bk == e[s.sz - pivot-1]){
+                s.popf;
+                pivot--;
+                result++;
+                continue;
+            }
+        } else {
+            s.pb(1);
+            result++;
+        }
+    }
 }
 
 } // namespace task
