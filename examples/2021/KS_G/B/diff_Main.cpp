diff --git a/CodeJam/Main.cpp b/examples/2021/KS_G/B/Main.cpp
index 05e1aa9..8ad4c5a 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_G/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE cell
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1540,11 +1540,67 @@ void init(){
     cin >> T;
 }
 
+ll K;
+v(ll) x0, x1, y0, y1;
+
 void readInput(){
+    cin >> K;
+    x0.resize(K);
+    x1.resize(K);
+    y0.resize(K);
+    y1.resize(K);
+    forn(i, K){
+        cin >> x0[i] >> y0[i] >> x1[i] >> y1[i];
+    }
+}
+
+ll compute_dist(ll a, v(ll) &a0, v(ll) &a1){
+    ll r = 0;
+    forn(i, a0.sz){
+        ll dist = max(a-a1[i], a0[i]-a);
+        dist = max(dist, 0LL);
+        r += dist;
+        // r += max(dist, 0);
+    }
+    return r;
+}
+
+ld gr = (sqrtl(5.0L) + 1.0L)/2.0L;
+
+ll gss(const std::function<ll (ll, v(ll)&, v(ll)&)> &f, ll a, ll b, v(ll)&a0, v(ll)&a1){
+    ll c = b - roundl(ld(b - a) / gr);
+    ll d = a + roundl(ld(b - a) / gr);
+    while(abs(a-b) > 1){
+        if(f(c, a0, a1) <= f(d, a0, a1))
+            b = d;
+        else
+            a = c;
+
+        // We recompute both c and d here to avoid loss of precision which may lead to incorrect results or infinite loop
+        c = b - roundl(ld(b - a) / gr);
+        d = a + roundl(ld(b - a) / gr);
+        if(d==c) d++;
+        if(d==b) d--;
+        lg("");
+        lg(a);
+        lg(c);
+        lg(d);
+        lg(b);
+    }
+
+    if(f(a, a0, a1)<=f(b, a0, a1))
+        return a;
+    else return b;
+    // return c;
+    return (b + a) / 2;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll x = gss(compute_dist, -2e9, 2e9, x0, x1);
+    ll y = gss(compute_dist, -2e9, 2e9, y0, y1);
+    result = {x, y};
 }
 
 } // namespace task
