diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/C/Main.cpp
index 6e1211d..a5d769d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/C/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1065,11 +1065,92 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(ll) Si, Ei;
+
 void readInput(){
+    Si.cl;
+    Ei.cl;
+    cin >> N;
+    ll s,e;
+    forn(i,N){
+        cin >> s >> e;
+        Si.pb(s);
+        Ei.pb(e);
+    }
+}
+
+v(v(ll)) overlaps;
+void compute_overlaps(){
+    overlaps.cl;
+    overlaps = v(v(ll))(N);
+    forn(i, N){
+        forn(j,i){
+            if(Si[i]<Ei[j] && Ei[i]>Si[j]){
+                overlaps[i].pb(j);
+                overlaps[j].pb(i);
+            }
+        }
+    }
+}
+
+v(ll) resultv;
+
+bool recur(ll act, ll p){
+    lassert(1<=p, "1<=p");
+    lassert(2>=p, "2>=p");
+    if(resultv[act] > 0 && resultv[act] != p){
+        return false;
+    }
+    if(resultv[act] == p){
+        return true;
+    }
+    resultv[act] = p;
+    if(overlaps[act].sz == 0){
+        return true;
+    } else {
+        foreach(other_act, overlaps[act]){
+            bool r = recur(other_act, 3-p);
+            if(!r){
+                return false;
+            }
+        }
+        return true;
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    compute_overlaps();
+    llog(overlaps);
+    resultv.cl;
+    resultv = v(ll)(N, 0);
+    result.cl;
+    bool possible=true;
+    while(true){
+        ll unfilled = distance(resultv.bn, find(all(resultv), 0));
+        if(unfilled != resultv.sz){
+            llog("resultv", resultv);
+            possible &= recur(unfilled, 1);
+            llog("resultv", resultv);
+            if(!possible){
+                break;
+            }
+        } else {
+            break;
+        }
+    }
+    if(possible){
+        foreach(p, resultv){
+            if(p==1){
+                result += "C";
+            } else{
+                lassert(p==2,"p==2");
+                result += "J";
+            }
+        }
+    }
+
 }
 
 } // namespace task
