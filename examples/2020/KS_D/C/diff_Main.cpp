diff --git a/CodeJam/Main.cpp b/examples/2020/KS_D/C/Main.cpp
index 2150379..e364fdb 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_D/C/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1570,11 +1570,86 @@ void init(){
     cin >> T;
 }
 
+ll N, A, B;
+v(ll) Pi;
+v(s(ll)) childs;
+
 void readInput(){
+    cin >> N >> A >> B;
+    Pi.resize(N-1);
+    childs.cl;
+    childs.resize(N);
+    forn(i, N-1) cin >> Pi[i];
+    forn(i, N-1) Pi[i]--;
+    forn(i, N-1) childs[Pi[i]].insert(i+1);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    if(N==1){
+        result = 1.0;
+        return;
+    }
+
+    v(ll) lvl;
+    lvl.assign(N, -1);
+    lvl[0] = 0;
+    queue<ll> q;
+    foreach(c, childs[0])
+        q.push(c);
+    while(!q.empty()){
+        ll i = q.front();
+        lg(i);
+        q.pop();
+        lvl[i] = lvl[Pi[i-1]] + 1;
+        foreach(c, childs[i]) q.push(c);
+    }
+    lg(childs);
+    lg(lvl);
+
+    v(ll) ac, bc;
+    ac.assign(N, 0);
+    bc.assign(N, 0);
+    v(bool) visited(N, false);
+    v(int) curdepthtrack_a(A, 0);
+    v(int) curdepthtrack_b(B, 0);
+
+    forn(leaf, N){
+        if(childs[leaf].sz) continue;
+        curdepthtrack_a.assign(A, 0);
+        curdepthtrack_b.assign(B, 0);
+        ll c = 0;
+        ll node = leaf;
+        ac[leaf]++;
+        bc[leaf]++;
+        curdepthtrack_a[0]++;
+        curdepthtrack_b[0]++;
+        visited[leaf] = true;
+        while(node!=0){
+            node = Pi[node-1];
+            c++;
+            // lg(node);
+            // lg(c);
+            if(!visited[node]){
+                curdepthtrack_a[c%A]++;
+                curdepthtrack_b[c%B]++;
+                visited[node] = true;
+            }
+            ac[node] += curdepthtrack_a[c%A];
+            bc[node] += curdepthtrack_b[c%B];
+            // lg(curdepthtrack_a);
+            // lg(curdepthtrack_b);
+            // lg(ac);
+            // lg(bc);
+        }
+    }
+    lg(ac);
+    lg(bc);
+
+    result = 0.0l;
+    forn(i, N){
+        result += 1.0l - (1.0l-(ld)ac[i]/N) * (1.0l-(ld)bc[i]/N);
+    }
 }
 
 } // namespace task
