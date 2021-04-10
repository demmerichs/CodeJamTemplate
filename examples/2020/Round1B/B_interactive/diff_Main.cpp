diff --git a/CodeJam/Main.cpp b/examples/2020/Round1B/B_interactive/Main.cpp
index 27af2c8..59c0193 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1B/B_interactive/Main.cpp
@@ -1,11 +1,11 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE "ERROR"
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE "WRONG"
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1016,15 +1016,109 @@ using namespace std;
 
 namespace task {
 
+ll A, B;
+bool found_center;
+
 void init(){
-    cin >> T;
+    cin >> T >> A >> B;
+}
+
+ll ask(cell p){
+    if(found_center) return 2;
+    sstr o;
+    lassert(p.x>=ll(-1e9), "x too small");
+    lassert(p.x<=ll(1e9), "x too big");
+    lassert(p.y>=ll(-1e9), "y too small");
+    lassert(p.y<=ll(1e9), "y too big");
+    o << p;
+    out(o.str());
+    str ans = in();
+    if(ans=="HIT") return 1;
+    if(ans=="MISS") return 0;
+    if(ans=="CENTER"){
+        found_center=true;
+        return 2;
+    };
+    lassert(false, "ans not recogni");
+    return 0;
 }
 
 void readInput(){
+    found_center = false;
+}
+
+pnt get_border(cell outs, cell ins){
+    pnt outsf(outs.x, outs.y);
+    pnt insf(ins.x, ins.y);
+    ld found_t = lower_bound_function<ld,bool>(true, [&](ld t){pnt p=insf*t+outsf*(1-t); return ask(cell(p.x,p.y))>=1;}, 1.0, 0.0, 1e-10);
+    pnt result = insf * found_t + outsf * (1-found_t);
+    return result;
+}
+
+cell get_center(pnt a, pnt b, pnt c){
+    ld denom = 2* (a.x * (b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y));
+    pnt res = norm(a) * (b-c) + norm(b) * (c-a) + norm(c) * (a-b);
+    res = pnt(res.y, -res.x);
+    res /= denom;
+    return cell(res.x,res.y);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    cell start(2e9,2e9);
+    v(cell) starts = {{0, 0}, {-1, 0},{0, -1},{0, 1},{1,0},{-1,-1}, {-1, 1}, {1, -1}, {1,1}};
+    llog("ask for a start cell");
+    foreach(s, starts){
+        ll ans = ask(s*ll(5e8));
+        if(ans > 0){
+            start = s;
+            break;
+        }
+    }
+    start *= ll(5e8);
+    llog("found a start cell", start);
+    pnt a = get_border(cell(-ll(1e9), -ll(1e9)), start);
+    pnt b = get_border(cell(-ll(1e9), ll(1e9)), start);
+    pnt c = get_border(cell(ll(1e9), ll(1e9)), start);
+    pnt d = get_border(cell(ll(1e9), -ll(1e9)), start);
+    ld dist_ab = norm(a-b);
+    ld dist_bc = norm(b-c);
+    ld dist_cd = norm(c-d);
+    ld dist_da = norm(d-a);
+    llog("computed a, b, c, d", a, b, c, d);
+    ld min_dist = min<ld>(dist_ab, min<ld>(dist_bc, min<ld>(dist_cd, dist_da)));
+    cell center;
+    if(min_dist == dist_ab){
+        llog("selected", b, c, d);
+        center = get_center(b,c,d);
+    }
+    else if(min_dist == dist_bc){
+        llog("selected", a, c, d);
+        center = get_center(c,d,a);
+    }
+    else if(min_dist == dist_cd){
+        llog("selected", a, b, d);
+        center = get_center(d,a,b);
+    }
+    else{
+        llog("selected", a, b, c);
+        center = get_center(a,b,c);
+    }
+    // llog("computed a,b,c", a, b, c);
+    // cell center = get_center(a,b,c);
+    ll delta = 0;
+    while(!found_center){
+        llog("checking delta", delta, "########################");
+        fore(r, center.x-delta, center.x+delta){
+            fore(c, center.y-delta, center.y+delta){
+                if(delta>max<ll>(abs<ll>(r-center.x),abs<ll>(c-center.y))) continue;
+                ask(cell(r,c));
+                if(found_center) break;
+            }
+            if(found_center) break;
+        }
+        delta++;
+    }
 }
 
 } // namespace task
