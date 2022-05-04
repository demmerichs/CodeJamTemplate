diff --git a/CodeJam/Main.cpp b/examples/2020/Round3/B/Main.cpp
index 6f10f99..b63528e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round3/B/Main.cpp
@@ -1551,11 +1551,92 @@ void init(){
     cin >> T;
 }
 
+ll K, N;
+v(ll) D;
+
 void readInput(){
+    cin >> K >> N;
+    D.resize(N);
+    ll last, sum = 0;
+    ll t;
+    cin >> last;
+    forn(i, N-1){
+        cin >> t;
+        D[i] = t-last;
+        last = t;
+        sum += D[i];
+    }
+    D[N-1] = K - sum;
+    forn(i, N) cin >> t;
+    lg(D);
+}
+
+ll greedy_placement(v(ll) d){
+    ll res = N;
+    llog("start greedy");
+    lg(d);
+    ll left=0, right=d[0], border=d[0];
+    ll origleft = 0, origright=d[0];
+    lg(0);
+    lg(res);
+    lg(left);
+    lg(right);
+    lg(border);
+    lg(origleft);
+    lg(origright);
+    fornn(i, 1, N+1){
+        ll newleft = 2*border - right;
+        ll newright = 2*border - left;
+        ll newborder = border + d[i%N];
+
+        if(newborder < newright){
+            ll delta = newright-newborder;
+            if(i%2==1) origleft += delta;
+            else origright -= delta;
+            newright -= delta;
+        }
+        if(newright <= newleft){
+            res++;
+            newleft = border;
+            newright = newborder;
+        }
+
+        left = newleft;
+        right = newright;
+
+        border = newborder;
+
+        llog("");
+        lg(i);
+        lg(res);
+        lg(left);
+        lg(right);
+        lg(border);
+        lg(origleft);
+        lg(origright);
+    }
+    if(res == N){
+        if(N%2 == 1){
+            if(d[0]-origright<border-left && d[0]-origleft>border-right) return res;
+        }
+        else
+            if(d[0]-origleft==border-left && d[0]-origright == border-right) return res;
+    }
+    return res+1;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = greedy_placement(D);
+    lg(result);
+    fornn(i, 1, N){
+        if(result == N) break;
+        v(ll) d;
+        d.insert(d.ed, msel(D, N-i, N));
+        d.insert(d.ed, msel(D, 0, N-i));
+        result = min(result, greedy_placement(d));
+        lg(result);
+    }
 }
 
 } // namespace task
