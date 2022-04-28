diff --git a/CodeJam/Main.cpp b/examples/2021/KS_F/B/Main.cpp
index fa1026d..4e0ada7 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_F/B/Main.cpp
@@ -1414,11 +1414,91 @@ void init(){
     cin >> T;
 }
 
+ll D, N, K;
+v(ll) hi, si, ei;
+d(ll, v(ll)) starts, ends;
+
 void readInput(){
+    cin >> D >> N >> K;
+    hi.resize(N);
+    si.resize(N);
+    ei.resize(N);
+    starts.cl;
+    ends.cl;
+    forn(i, N){
+        cin >> hi[i] >> si[i] >> ei[i];
+        si[i]--;
+        starts[si[i]].pb(i);
+        ends[ei[i]].pb(i);
+    }
+}
+
+void insert(ll attr, ll &topksum, v(ll) &stack, s(ll) &avail_hap, ll &ptr_hp, ll &ptr_nbr){
+    ll h = hi[attr];
+    stack[h]++;
+    avail_hap.insert(h);
+    if(h > ptr_hp){
+        topksum += h - ptr_hp;
+        ptr_nbr--;
+        if(ptr_nbr == 0){
+            auto ptr_avail_hap = avail_hap.find(ptr_hp);
+            ptr_avail_hap++;
+            ptr_hp = *ptr_avail_hap;
+            ptr_nbr = stack[ptr_hp];
+        }
+    }
+}
+
+void remove(ll attr, ll &topksum, v(ll) &stack, s(ll) &avail_hap, ll &ptr_hp, ll &ptr_nbr){
+    ll h = hi[attr];
+    stack[h]--;
+
+    if(h > ptr_hp){
+        if(stack[ptr_hp] > ptr_nbr){
+            topksum += ptr_hp - h;
+            ptr_nbr++;
+        } else {
+            lassert(stack[ptr_hp] == ptr_nbr, "no match");
+            auto ptr_avail_hap = avail_hap.find(ptr_hp);
+            ptr_avail_hap--;
+            ptr_hp = *ptr_avail_hap;
+            topksum += ptr_hp - h;
+            ptr_nbr = 1;
+        }
+    }
+    else if(h == ptr_hp){
+        if(ptr_nbr>stack[ptr_hp]){
+            lassert(ptr_nbr-1==stack[ptr_hp], "logic error");
+            auto ptr_avail_hap = avail_hap.find(ptr_hp);
+            ptr_avail_hap--;
+            ptr_hp = *ptr_avail_hap;
+            topksum += ptr_hp - h;
+            ptr_nbr = 1;
+        }
+    }
+
+    if(stack[h] == 0) avail_hap.erase(h);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+
+    ll curtopksum = 0;
+
+    v(ll) stack(3*1e5L + 1, 0);
+    s(ll) avail_hap;
+    stack[0] = K;
+    avail_hap.insert(0);
+    ll ptr_hp = 0;
+    ll ptr_nbr = K;
+
+
+    forn(d, D){
+        foreach(attr, starts[d]) insert(attr, curtopksum, stack, avail_hap, ptr_hp, ptr_nbr);
+        foreach(attr, ends[d]) remove(attr, curtopksum, stack, avail_hap, ptr_hp, ptr_nbr);
+        result = max(result, curtopksum);
+    }
 }
 
 } // namespace task
