diff --git a/CodeJam/Main.cpp b/examples/2017/Round3/A/Main.cpp
index 27af2c8..1ee0f1f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2017/Round3/A/Main.cpp
@@ -1020,11 +1020,55 @@ void init(){
     cin >> T;
 }
 
+str G;
+ll N;
+
 void readInput(){
+    cin >> G;
+    N = G.sz;
+}
+
+ll recur(str g){
+    llog("starting recur");
+    lg(g);
+    ll s=0;
+    forn(i, N) s+= (g[i]-'0')*(i+1);
+    if(s>N){
+        ll ans=1;
+        ll rd=N;
+        forn(i, N){
+            ans *= choosell(rd, g[i]-'0');
+            rd -=g[i]-'0';
+        }
+        llog("early break");
+        lg(ans);
+        return ans+1;
+    }
+
+    ll ans=0;
+    str curg="";
+    forn(i, N){
+        forn(j, g[i]-'0') curg += '1'+i;
+    }
+    while(curg.sz < N) curg += '0';
+    sort(all(curg));
+    lg(curg);
+    while(true){
+        if(curg!=g){
+            llog("answer before recur");
+            lg(ans);
+            ans += recur(curg);
+            llog("answer after recur");
+            lg(ans);
+        }
+        if(!next_permutation(all(curg))) break;
+    }
+    return ans + 1;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = recur(G);
 }
 
 } // namespace task
