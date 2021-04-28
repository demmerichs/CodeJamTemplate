diff --git a/CodeJam/Main.cpp b/examples/2021/Round1A/A/Main.cpp
index 42da9e7..28c2892 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/Round1A/A/Main.cpp
@@ -1024,11 +1024,61 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(str) Xi;
+
 void readInput(){
+    cin >> N;
+    Xi.resize(N);
+    forn(i, N) cin >> Xi[i];
+}
+
+bool str_smaller_equal(str a, str b){
+    if(a.sz < b.sz) return true;
+    if(b.sz < a.sz) return false;
+    return a<=b;
+}
+
+str str_add_one(str a){
+    ll nbr_trail_9 = 0;
+    forn(i, a.sz){
+        if(a[a.sz-1-i] == '9') nbr_trail_9++;
+        else break;
+    }
+    lg(a);
+    lg(nbr_trail_9);
+    str result = a.substr(0, a.sz-nbr_trail_9);
+    if(result.sz==0) result = "0";
+    result[result.sz-1] = result[result.sz-1] + 1;
+    forn(i, nbr_trail_9) result += '0';
+    lg(result);
+    return result;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    str last = "0";
+    forn(i, N){
+        str cur = Xi[i];
+        while(str_smaller_equal(cur, last)){
+            if(last.substr(0, cur.sz)==cur){
+                str target = str_add_one(last);
+                if(target.substr(0, cur.sz)==cur){
+                    result += target.sz - cur.sz;
+                    cur = target;
+                } else{
+                    cur += "0";
+                    result++;
+                }
+            } else {
+                cur += "0";
+                result++;
+            }
+        }
+        last = cur;
+        lg(last);
+    }
 }
 
 } // namespace task
