diff --git a/CodeJam/Main.cpp b/examples/2018/Round3/C/Main.cpp
index 0f47b9d..312030e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round3/C/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1569,11 +1569,121 @@ void init(){
     cin >> T;
 }
 
+#define cell v(ll)
+ll N;
+v(cell) tips;
+
 void readInput(){
+    cin >> N;
+    tips.assign(N+1, {0, 0, 0});
+    fore(i,1,N){
+        cin >> tips[i][0];
+        cin >> tips[i][1];
+        cin >> tips[i][2];
+    }
+}
+
+cell cross(cell a, cell b){
+    cell res;
+    res.pb(a[1]*b[2]-a[2]*b[1]);
+    res.pb(a[2]*b[0]-a[0]*b[2]);
+    res.pb(a[0]*b[1]-a[1]*b[0]);
+    return res;
+}
+
+cell plane_vec(cell a, cell b, cell c){
+    cell d1 = vecOp<ll>(a, b, minus<ll>());
+    cell d2 = vecOp<ll>(a, c, minus<ll>());
+    cell ans = cross(d1, d2);
+    if(ans[2] < 0){
+        ans[0] *= -1;
+        ans[1] *= -1;
+        ans[2] *= -1;
+    }
+    return ans;
+}
+
+ld plane_sp(cell p1i, cell p2i){
+    v(ld) p1, p2;
+    forn(i,3){
+        p1.pb(p1i[i]);
+        p2.pb(p2i[i]);
+    }
+    ld sp = p1[0]*p2[0] + p1[1]*p2[1]+p1[2]*p2[2];
+    ld n1_sqr = p1[0]*p1[0] + p1[1]*p1[1]+p1[2]*p1[2];
+    ld n2_sqr = p2[0]*p2[0] + p2[1]*p2[1]+p2[2]*p2[2];
+    lg(p1);
+    lg(p2);
+    lg(sp);
+    lg(n1_sqr);
+    lg(n2_sqr);
+    return sp * abs(sp) / (n1_sqr * n2_sqr);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result.cl;
+    result.pb(1);
+    fore(i, 1, N){
+        if(tips[result.bk][2] < tips[i][2]) result.bk = i;
+    }
+    v(bool) lefts(N+1, true);
+    lefts[0] = false;
+    lefts[result.bk] = false;
+    lg(result);
+    lg(lefts);
+    cell last_plane = {0, 0, 1};
+    ll bidx = 0;
+    ld min_sp = 2.0;
+    fore(i, 1, N){
+        if(!lefts[i]) continue;
+        cell cur_ortho_plane_vec = vecOp<ll>(tips[result.bk], tips[i], minus<ll>());
+        ld cur_sp = plane_sp(cur_ortho_plane_vec, last_plane);
+        if(cur_sp<=min_sp){
+            min_sp=cur_sp;
+            bidx = i;
+        }
+    }
+    lassert(bidx > 0, "nothing found");
+    result.pb(bidx);
+    lefts[bidx] = false;
+    cell initial_diff =  vecOp<ll>(tips[result[0]], tips[result[1]], minus<ll>());
+    lg(initial_diff);
+    last_plane = cross(last_plane, initial_diff);
+    lg(last_plane);
+    last_plane = cross(last_plane, initial_diff);
+    if(last_plane[2]<0){
+        last_plane[0]*=-1;
+        last_plane[1]*=-1;
+        last_plane[2]*=-1;
+    }
+    lg(last_plane);
+    lg(result);
+    while(result.sz < N){
+        bidx = 0;
+        cell new_best_plane = last_plane;
+        ld max_sp = -2.0;
+        lg(last_plane);
+        lg(lefts);
+        fore(i, 1, N){
+            if(!lefts[i]) continue;
+            cell new_plane = plane_vec(tips[result[result.sz-2]], tips[result.bk], tips[i]);
+            lg(last_plane);
+            lg(new_plane);
+            ld sp = plane_sp(new_plane, last_plane);
+            lg(sp);
+            if(sp>max_sp){
+                max_sp=sp;
+                bidx = i;
+                new_best_plane = new_plane;
+            }
+        }
+        lassert(bidx > 0, "nothing found");
+        result.pb(bidx);
+        lefts[bidx] = false;
+        last_plane = new_best_plane;
+    }
+    reverse(all(result));
 }
 
 } // namespace task
