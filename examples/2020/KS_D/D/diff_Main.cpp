diff --git a/CodeJam/Main.cpp b/examples/2020/KS_D/D/Main.cpp
index a7f0d62..b8ebebd 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/KS_D/D/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1501,11 +1501,115 @@ void init(){
     cin >> T;
 }
 
+const ll MAXLOG2N = 17;
+ll N, Q;
+v(ll) Di;
+v(ll) Si, Ki;
+v(ll) st_amax;
+
 void readInput(){
+    cin >> N >> Q;
+    Di.resize(N-1);
+    Si.resize(Q);
+    Ki.resize(Q);
+
+    forn(i, N-1) cin >> Di[i];
+    forn(i, Q) cin >> Si[i] >> Ki[i];
+    st_amax.assign(1<<(MAXLOG2N+1), -1);
+}
+
+ll get_argmax(ll l, ll r, ll node=0, ll nl=0, ll nr=(1<<MAXLOG2N)-1){
+    if(l>r) return -1;
+    if(l == nl && r == nr) return st_amax[node];
+    ll nm = (nl+nr)/2;
+    ll lamax = get_argmax(l,min(r,nm), 2*node+1, nl, nm);
+    ll ramax = get_argmax(max(l,nm+1), r, 2*node+2, nm+1, nr);
+    if(lamax == -1) return ramax;
+    if(ramax == -1) return lamax;
+    return Di[lamax] > Di[ramax] ? lamax : ramax;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    forn(i, N-1){
+        st_amax[i+(1<<MAXLOG2N) - 1] = i;
+    }
+    forn(ii, (1<<MAXLOG2N)-1){
+        ll i = (1<<MAXLOG2N) -2 - ii;
+        if(st_amax[2*i+1] == -1){
+            st_amax[i] = st_amax[2*i+2];
+            continue;
+        }
+        if(st_amax[2*i+2] == -1){
+            st_amax[i] = st_amax[2*i+1];
+            continue;
+        }
+        st_amax[i] = Di[st_amax[2*i+1]] > Di[st_amax[2*i+2]] ? st_amax[2*i+1] : st_amax[2*i+2];
+    }
+
+    result.cl;
+    forn(i, Q){
+        ll k = Ki[i];
+        ll s = Si[i];
+        lg(s);
+        lg(k);
+        ll l = s, r=s;
+        ll leftmax = 0;
+        ll rightmax = 0;
+        ll rest = k - (r-l+1);
+        while(rest > 0 && l>1 && r<N){
+            llog("");
+            ll halfrest = (rest+1)/2;
+            lg(l);
+            lg(r);
+            lg(leftmax);
+            lg(rightmax);
+            lg(halfrest);
+            ll nl = get_argmax(max<ll>(l-1-halfrest, 0L), l-2);
+            ll nr = get_argmax(r-1, min(r-2+halfrest, N-2));
+            lg(nl);
+            lg(nr);
+            lg(Di[nl]);
+            lg(Di[nr]);
+            bool goleft = true;
+            if(Di[nr] < leftmax && Di[nl] < rightmax){
+                goleft = leftmax < rightmax;
+            } else if(Di[nr] < leftmax && rightmax < leftmax){
+                goleft = false;
+            } else if(Di[nl] < rightmax && leftmax < rightmax){
+                goleft = true;
+            } else {
+                goleft = Di[nl] < Di[nr];
+            }
+            lg(goleft);
+            if(goleft){
+                l-=halfrest;
+                l = max<ll>(l, 1L);
+                leftmax = max(leftmax, Di[nl]);
+            } else {
+                r+=halfrest;
+                r = min(r, N);
+                rightmax = max(rightmax, Di[nr]);
+            }
+            lg(l);
+            lg(r);
+            rest = k - (r-l+1);
+        }
+        if(l==1){
+            r = k;
+        }
+        if(r==N){
+            // r-l=k-1
+            l = r-k+1;
+        }
+        lg(l);
+        lg(r);
+        ll leftamax = get_argmax(l-1, s-2);
+        ll rightamax = get_argmax(s-1, r-2);
+        bool lastmove_right = (leftamax == -1) || (rightamax >= 0 && leftamax >= 0 && Di[leftamax] < Di[rightamax]);
+        lg(lastmove_right);
+        result.pb(lastmove_right?r:l);
+    }
 }
 
 } // namespace task
