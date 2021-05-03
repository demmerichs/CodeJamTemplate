diff --git a/CodeJam/Main.cpp b/examples/2019/Round1B/C/Main.cpp
index fad3e96..0e67112 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1B/C/Main.cpp
@@ -1025,11 +1025,41 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
+v(ll) Ci, Di;
+
 void readInput(){
+    cin >> N >> K;
+    Ci.cl;
+    Di.cl;
+    forn(i, N){
+        ll t;
+        cin >> t;
+        Ci.pb(t);
+    }
+    forn(i, N){
+        ll t;
+        cin >> t;
+        Di.pb(t);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    RangeMinMaxTable<ll> lookup_C(Ci, false);
+    RangeMinMaxTable<ll> lookup_D(Di, false);
+    forn(i, N){
+        auto charles_chooses_i_and_is_good_lower = [&](ll l){return Ci[i] >= Di[lookup_D.query(l, i+1)] - K && lookup_C.query(l, i+1) == i;};
+        auto not_charles_chooses_i_and_is_good_upper = [&](ll u){return !(Ci[i] >= Di[lookup_D.query(i, u)] - K && lookup_C.query(i, u) == i);};
+        auto charles_chooses_i_and_is_too_good_lower = [&](ll l){return Ci[i] > Di[lookup_D.query(l, i+1)] + K && lookup_C.query(l, i+1) == i;};
+        auto not_charles_chooses_i_and_is_too_good_upper = [&](ll u){return !(Ci[i] > Di[lookup_D.query(i, u)] + K && lookup_C.query(i, u) == i);};
+        ll low_good_enough = lower_bound_function<ll,bool>(true, charles_chooses_i_and_is_good_lower, i+1);
+        ll low_too_good = lower_bound_function<ll,bool>(true, charles_chooses_i_and_is_too_good_lower, i+1);
+        ll up_good_enough = upper_bound_function<ll,bool>(false, not_charles_chooses_i_and_is_good_upper, N-i, i+1);
+        ll up_too_good = upper_bound_function<ll,bool>(false, not_charles_chooses_i_and_is_too_good_upper, N-i, i+1);
+        result += (i+1-low_good_enough) * (up_good_enough-1-i) - (i+1-low_too_good) * (up_too_good-1-i);
+    }
 }
 
 } // namespace task
