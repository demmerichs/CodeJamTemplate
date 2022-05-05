diff --git a/CodeJam/Main.cpp b/examples/2021/Round2/C/Main.cpp
index 2150379..9dbe2d3 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round2/C/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE mint
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1570,11 +1570,69 @@ void init(){
     cin >> T;
 }
 
+const ll MAXLOG2N = 17;
+// const ll MAXLOG2N = 2;
+ll N;
+v(int) Vi;
+v(int) st_amin;
+
 void readInput(){
+    cin >> N;
+    Vi.resize(N);
+    forn(i, N) cin >> Vi[i];
+    st_amin.assign(1<<(MAXLOG2N+1), -1);
+}
+
+ll argmin(ll l, ll r, ll node=0, ll nl=0, ll nr=(1<<MAXLOG2N)-1){
+    if(l>r) return -1;
+    if(l==nl && r==nr) return st_amin[node];
+    ll nm = (nl+nr)/2;
+    ll ql = argmin(l, min(r, nm), 2*node+1, nl, nm);
+    ll qr = argmin(max(l, nm+1), r, 2*node+2, nm+1, nr);
+    if(ql==-1) return qr;
+    if(qr==-1) return ql;
+    if(Vi[ql] < Vi[qr]) return ql;
+    return qr;
+}
+
+
+void recur(ll l, ll r, ll mi){
+    if(l>r) return;
+    ll pos = argmin(l, r);
+    if(Vi[pos] != mi){
+        result = 0;
+        return;
+    }
+    ll lcount = pos - l;
+    ll rcount = r - pos;
+    lg(lcount+rcount);
+    lg(rcount);
+    result = result * choose<mint>(lcount+rcount, rcount);
+    recur(l, pos-1, mi);
+    recur(pos+1, r, mi+1);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    forn(i, N){
+        st_amin[i+(1<<MAXLOG2N)-1] = i;
+    }
+    forn(ii, (1<<MAXLOG2N)-1){
+        ll i = (1<<MAXLOG2N)-2-ii;
+        ll lidx = st_amin[2*i+1];
+        ll ridx = st_amin[2*i+2];
+        if(lidx==-1) st_amin[i]=ridx;
+        else if(ridx==-1) st_amin[i]=lidx;
+        else if(Vi[lidx]<Vi[ridx]) st_amin[i] = lidx;
+        else st_amin[i] = ridx;
+    }
+    // lg(st_amin);
+    // lg(argmin(0,3));
+
+    result = 1;
+    recur(0, N-1, 1);
+    // lg(choosemod(5000, 2500));
+    // lg(choosemod(50000, 25000));
 }
 
 } // namespace task
