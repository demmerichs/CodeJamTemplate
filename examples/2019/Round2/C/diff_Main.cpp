diff --git a/CodeJam/Main.cpp b/examples/2019/Round2/C/Main.cpp
index d8e2c23..ce0682f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round2/C/Main.cpp
@@ -1,10 +1,10 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result<0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result.x==0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define COMM_TYPE cell
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1010,11 +1010,136 @@ namespace task {
 void init(){
 }
 
+ll N;
+v(cell) mols;
+
+d(ld, cell) lower_cj;
+d(ld, cell) upper_cj;
+
 void readInput(){
+    mols.cl;
+    lower_cj.cl;
+    upper_cj.cl;
+    lower_cj[ld(0.0)] = cell(1, INF);
+    upper_cj[ld(INF)] = cell(INF, 1);
+    cin >> N;
+    forn(i, N){
+        ll a,b;
+        cin >> a >> b;
+        mols.emplace_back(a,b);
+    }
+}
+
+void cf(cell frac, v(ll)& res){
+    if(frac.y == 1){
+        res.pb(frac.x);
+        res.pb(INF);
+        return;
+    }
+    ll full = frac.x / frac.y;
+    ll restx = frac.x % frac.y;
+    res.pb(full);
+    cf(cell(frac.y, restx), res);
+}
+
+cell icf(v(ll) cf){
+    cell result(1, 0);
+    llog("inverse cf of", cf);
+    lassert(cf.bk >= INF, "cf.bk >= INF");
+    while(cf.bk >= INF){
+        cf.popb;
+    }
+    if(cf.sz == 0) return cell(INF, 1);
+    while(cf.sz>0){
+        result = cell(result.y + cf.bk * result.x, result.x);
+        cf.popb;
+    }
+    llog(result);
+    return result;
+}
+
+v(ll) combine(v(ll) a, v(ll) b){
+    llog("combination of ", a, "and", b);
+    v(ll) cfr;
+    ll i=0;
+    while(a[i] == b[i]){
+        cfr.pb(a[i]);
+        i++;
+    }
+    cfr.pb(min(a[i], b[i])+1);
+    cfr.pb(INF);
+    llog(cfr);
+    return cfr;
+}
+
+cell find_best_inbetween(cell l, cell u){
+    cell t(l);
+    l = cell(u.y, u.x);
+    u = cell(t.y, t.x);
+    llog("start interval search for ", l, u);
+    v(ll) cfl, cfu;
+    cf(l, cfl);
+    cf(u, cfu);
+    llog("lower cf", cfl);
+    llog("upper cf", cfu);
+    v(cell) results;
+    results.pb(icf(combine(cfl, cfu)));
+    cfu.popb;
+    cfu.bk -= 1;
+    cfu.pb(1);
+    cfu.pb(INF);
+    results.pb(icf(combine(cfl, cfu)));
+    cfl.popb;
+    cfl.bk -= 1;
+    cfl.pb(1);
+    cfl.pb(INF);
+    results.pb(icf(combine(cfl, cfu)));
+    cfu.popb;
+    cfu.popb;
+    cfu.bk += 1;
+    cfu.pb(INF);
+    results.pb(icf(combine(cfl, cfu)));
+    cell best_result = results[0];
+    foreach(r, results){
+        if(r!=l && r!=u) best_result = r;
+    }
+    foreach(r, results){
+        if(r==l || r==u) continue;
+        if(best_result.y > r.y){
+            best_result = r;
+        } else if (best_result.y == r.y && best_result.x > r.x){
+            best_result = r;
+        }
+    }
+    return cell(best_result.y,best_result.x);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    forn(i, N-1){
+        if(mols[i].x <= mols[i+1].x && mols[i].y <= mols[i+1].y) continue;
+        if(mols[i].x >= mols[i+1].x && mols[i].y >= mols[i+1].y) {
+            result = cell(0,0);
+            return;
+        }
+        ll delx = mols[i].x - mols[i+1].x;
+        ll dely = mols[i].y - mols[i+1].y;
+        ll g = gcd(abs(delx), abs(dely));
+        delx /= g;
+        dely /= g;
+        if(delx < 0){
+            lower_cj[ld(dely)/(-delx)] = cell(dely, -delx);
+        } else {
+            lassert(dely < 0, "logic error here");
+            lassert(delx > 0, "logic error here");
+            upper_cj[ld(-dely)/delx] = cell(-dely, delx);
+        }
+    }
+    if(lower_cj.rbegin()->st >= upper_cj.bn->st){
+        result = cell(0,0);
+        return;
+    }
+    result = find_best_inbetween(lower_cj.rbegin()->nd, upper_cj.bn->nd);
 }
 
 } // namespace task
