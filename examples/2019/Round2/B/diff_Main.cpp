diff --git a/CodeJam/Main.cpp b/examples/2019/Round2/B/Main.cpp
index 44d71ea..40aa44e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round2/B/Main.cpp
@@ -1,10 +1,10 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result<0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE "ERROR"
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE "-1"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -947,11 +947,61 @@ namespace task {
 void init(){
 }
 
+ll N=100, V=20;
+ll n=78, v=7;
+ll daynbr;
+
+void put_in_vase(ll i){
+    llog("putting my token in vase", i, "##################################");
+    str day = in();
+    lassert(atoi(day.data()) == daynbr, "wrong day detected");
+    daynbr++;
+    sstr s;
+    s << i+1 << " " << N;
+    out(s.str());
+}
+
+ll get_count(ll i){
+    llog("getting count for vase", i, "=======================================");
+    str day = in();
+    lassert(atoi(day.data()) == daynbr, "wrong day detected");
+    daynbr++;
+    sstr s;
+    s << i+1 << " " << 0;
+    out(s.str());
+    str ans = in();
+    llog("got an answer", ans);
+    s.str("");
+    s << ans;
+    ll res;
+    s >> res;
+    llog("converted answer to ll", res);
+    forn(j,res){
+        in();
+    }
+    return res;
+}
+
 void readInput(){
+    daynbr = 1;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    forn(i, n){
+        put_in_vase(i%(V-v) + v);
+    }
+    v(ll) counts;
+    forn(i, v){
+        counts.pb(get_count(i));
+    }
+    forn(i, N-1-n-v){
+        v(ll) idxsort = argsort(counts);
+        put_in_vase(idxsort[1]);
+        counts[idxsort[1]]++;
+    }
+    v(ll) idxsort = argsort(counts);
+    put_in_vase(idxsort[0]);
 }
 
 } // namespace task
