diff --git a/CodeJam/Main.cpp b/examples/2022/KS_A/D/Main.cpp
index fa1026d..cadedbf 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/KS_A/D/Main.cpp
@@ -1414,11 +1414,120 @@ void init(){
     cin >> T;
 }
 
+ll A, B;
+
 void readInput(){
+    cin >> A >> B;
+}
+
+bool nice_interval(ll a, ll b){
+    if(a==b)
+        return true;
+    str diff = to_string(b-a);
+    str as = to_string(a);
+    forn(i, diff.sz){
+        if(diff[i]!='9')
+            return false;
+    }
+    forn(i, diff.sz){
+        if(as[i+as.sz-diff.sz]!='0')
+            return false;
+    }
+    return true;
+}
+
+ll compute_split(ll a, ll b){
+    str as = to_string(a);
+    str diff = to_string(b-a);
+    ll s = a;
+    ll counter = 0;
+    while(counter<as.sz){
+        if(as[as.sz-1-counter] != '0'){
+            break;
+        }
+        ll news = a+powll(10, counter+1)-1;
+        if(news<=b){
+            counter++;
+            s = news;
+        } else {
+            break;
+        }
+    }
+    return s;
+}
+
+bool is_interesting(str a){
+    ll s=0;
+    ll p=1;
+    forn(i, a.sz){
+        ll d = a[i] - '0';
+        s += d;
+        p *= d;
+    }
+    return (p%s) == 0;
+}
+
+d(p(ll, ll), ll) mem_results;
+
+ll countInterestings(ll a, ll b){
+    if(mem_results.count(mp(a,b)))
+        return mem_results[mp(a,b)];
+    if(!nice_interval(a, b)){
+        ll s = compute_split(a, b);
+        return countInterestings(a, s)
+            + countInterestings(s+1, b);
+    }
+    if(a==b){
+        return is_interesting(to_string(a));
+    }
+    str diff = to_string(b-a);
+    str as = to_string(a);
+    str prefix = as.substr(0, as.sz-diff.sz);
+    ll nbr_free_digits = diff.sz;
+    forn(i, prefix.sz){
+        if(prefix[i]=='0')
+            return b-a+1;
+    }
+    v(bool) separators(nbr_free_digits+9, false);
+    forn(i, 9)
+        separators[nbr_free_digits+i]=true;
+    ll ans = 0;
+    llog("all sep combs");
+    ll count_combs = 0;
+    do{
+        count_combs++;
+        // lg(separators);
+        str post;
+        ll cur_free_digits = nbr_free_digits;
+        ll permutations = 1;
+        ll count = 0;
+        ll digit = 0;
+        forn(i, separators.sz + 1){
+            if(i == separators.sz || separators[i]){
+                forn(j, count)
+                    post += '0' + digit;
+                permutations *= choosell(cur_free_digits, count);
+                cur_free_digits -= count;
+                digit++;
+                count = 0;
+            } else
+                count++;
+        }
+        // lg(post);
+        // lg(permutations);
+        ans += permutations * is_interesting(prefix + post);
+    } while(next_permutation(all(separators)));
+    lg(count_combs);
+    if(nbr_free_digits > 7){
+        mem_results[mp(a,b)] = ans;
+        lg(mem_results.sz);
+    }
+    return ans;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = countInterestings(A, B);
 }
 
 } // namespace task
