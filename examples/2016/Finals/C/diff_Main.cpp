diff --git a/CodeJam/Main.cpp b/examples/2016/Finals/C/Main.cpp
index 16602b7..7f7a18f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2016/Finals/C/Main.cpp
@@ -1010,14 +1010,110 @@ using namespace std;
 
 namespace task {
 
+ll floorsqrtll(ll i){
+    lassert(i>=0, "sqrt of negative not allowed");
+    return upper_bound_function<ll, ll>(i, [&](ll x){return x*x;}, i+1)-1;
+}
+
+v(ll) primes;
+
+v(ll) pfs(ll i){
+    lassert(i>0, "no factors for 0");
+    v(ll) result;
+    ll sq = floorsqrtll(i);
+    foreach(p, primes){
+        if(p>sq)
+            break;
+        if(i%p==0){
+            result.pb(p);
+            while(i%p==0)
+                i/=p;
+            sq = floorsqrtll(i);
+        }
+    }
+    if(i>1)
+        result.pb(i);
+    return result;
+}
+
 void init(){
+    fornn(i, 2, 1000001L){
+        ll sq = floorsqrtll(i);
+        bool isprime = true;
+        foreach(p, primes){
+            if(p>sq)
+                break;
+            if(i%p == 0){
+                isprime = false;
+                break;
+            }
+        }
+        if(isprime)
+            primes.pb(i);
+    }
 }
 
+ll N, R;
+
 void readInput(){
+    cin >> N >> R;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    ll maxN = ceill(1000000, R);
+    lg(N);
+    lg(R);
+    lg(maxN);
+    N = min(N, maxN);
+
+    forn(x, N){
+        ll maxy = lower_bound_function<ll, ll>(1000000000000L, [&](ll y){return (y*y+x*x)*R*R;}, N)-1;
+        // lg(x);
+        // lg(maxy);
+        if(maxy+1 < N){
+            lassert((maxy*maxy+x*x)*R*R<1000000000000L, "maxy too big");
+            lassert(((maxy+1)*(maxy+1)+x*x)*R*R>=1000000000000L, "maxy too small");
+        }
+        ll fast_algo_result = 0;
+        ll old_algo_cur_result = 0;
+        if(x>0){
+            // forn(y, maxy+1){
+            //     if(gcd(x,y)==1)
+            //         old_algo_cur_result++;
+            // }
+            v(ll) pf = pfs(x);
+            // lg(pf);
+            forn(k, 1<<pf.sz){
+                ll prod = 1;
+                int sgn = 1;
+                forn(i, pf.sz){
+                    if((k>>i)&1){
+                        sgn *= -1;
+                        prod *= pf[i];
+                    }
+                }
+                fast_algo_result += sgn * (floorll(maxy, prod)+1);
+            }
+            // fore(k, 0, pf.sz){
+            //     for(seliter<ll> si(pf, k); !si.final(); ++si){
+            //         lg(*si);
+            //         ll prod = 1;
+            //         foreach(p, *si)
+            //             prod *= p;
+            //         if(k%2==1)
+            //             fast_algo_result -= floorll(maxy, prod)+1;
+            //         else
+            //             fast_algo_result += floorll(maxy, prod)+1;
+            //     }
+            // }
+            // lassert(fast_algo_result==old_algo_cur_result, "new algo is wrong");
+        } else
+            fast_algo_result = 1;
+        // lg(fast_algo_result);
+        result+=fast_algo_result;
+    }
 }
 
 } // namespace task
