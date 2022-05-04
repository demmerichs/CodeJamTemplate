diff --git a/CodeJam/Main.cpp b/examples/2021/Final/B/Main.cpp
index 6f10f99..146744d 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Final/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(str)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1551,11 +1551,88 @@ void init(){
     cin >> T;
 }
 
+ll B, S, N;
+v(ll) Xi, Yi;
+v(ull) slide_hashes;
+d(ull, ll) Si;
+v(bool) Aj;
+v(ll) Lj, Rj, Mj;
+v(ull) building_hashes;
+
 void readInput(){
+    cin >> B >> S >> N;
+    Xi.resize(S);
+    Yi.resize(S);
+    slide_hashes.resize(S);
+    Aj.resize(N);
+    Lj.resize(N);
+    Rj.resize(N);
+    Mj.resize(N);
+    building_hashes.resize(2*B);
+    forn(b, B){
+        building_hashes[2*b] = rand();
+        building_hashes[2*b] <<= 31;
+        building_hashes[2*b] |= rand();
+        building_hashes[2*b] <<= 31;
+        building_hashes[2*b] |= rand();
+        building_hashes[2*b+1] = rand();
+        building_hashes[2*b+1] <<= 31;
+        building_hashes[2*b+1] |= rand();
+        building_hashes[2*b+1] <<= 31;
+        building_hashes[2*b+1] |= rand();
+    }
+    forn(s, S)
+        cin >> Xi[s] >> Yi[s];
+    char d;
+    forn(n, N){
+        cin >> d >> Lj[n] >> Rj[n] >> Mj[n];
+        Aj[n] = d == 'E';
+        ++Rj[n];
+    }
+    forn(s, S){
+        slide_hashes[s] = building_hashes[2*(Xi[s]-1)] ^ building_hashes[2*(Yi[s]-1)+1];
+        lassert(Si.count(slide_hashes[s]) == 0, "hash collision");
+        Si[slide_hashes[s]] = s+1;
+    }
+    lg(building_hashes);
+    lg(slide_hashes);
+    lg(Si);
 }
 
+
 // write to COMM_TYPE result
 void calcFunction() {
+    result.resize(N);
+    v(v(ull)) precompute_mod_hashes(S);
+    forn(m, S){
+        ull cur_h_sum = 0;
+        precompute_mod_hashes[m].pb(0);
+        for(ll i = m+1; i<=S; i+=m+1){
+            cur_h_sum ^= slide_hashes[i-1];
+            precompute_mod_hashes[m].pb(cur_h_sum);
+        }
+    }
+    ull hash_state = 0;
+    forn(b, 2*B)
+        hash_state ^= building_hashes[b];
+    ll count_enabled = 0;
+    forn(n, N){
+        ll cur_count = (Rj[n]-1)/Mj[n] - (Lj[n]-1)/Mj[n];
+        if(!Aj[n]) cur_count *= -1;
+        count_enabled += cur_count;
+        hash_state ^= precompute_mod_hashes[Mj[n]-1][(Rj[n]-1)/Mj[n]];
+        hash_state ^= precompute_mod_hashes[Mj[n]-1][(Lj[n]-1)/Mj[n]];
+        lg(hash_state);
+        lg(count_enabled);
+        if(count_enabled != B-1){
+            result[n] = "X";
+            continue;
+        }
+        if(Si.count(hash_state))
+            result[n] = to_string(Si[hash_state]);
+        else
+            result[n] = "X";
+    }
 }
 
 } // namespace task
