diff --git a/CodeJam/Main.cpp b/examples/atcoder/contests/practice/B/Main.cpp
index 00aa56c..edcf44f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/atcoder/contests/practice/B/Main.cpp
@@ -1,11 +1,11 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE -1
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE ""
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1457,7 +1457,7 @@ void out(T t){
     #ifdef IA_COMM_LOG
     llog("sending output:", t);
     #endif /*IA_COMM_LOG*/
-    std::cout << t << std::endl;
+    std::cout << t << std::endl << std::flush;
 }
 
 template<typename T, typename... Args>
@@ -1465,7 +1465,7 @@ void out(T t, Args... args){
     #ifdef IA_COMM_LOG
     llog("sending output:", t);
     #endif /*IA_COMM_LOG*/
-    std::cout << t << std::endl;
+    std::cout << t << std::endl << std::flush;
     out(args...);
 }
 
@@ -1541,14 +1541,97 @@ using namespace std;
 namespace task {
 
 void init(){
-    cin >> T;
+    // cin >> T;
+    T = 1;
 }
 
+ll N, Q;
+
 void readInput(){
+    cin >> N >> Q;
+}
+
+str binaryInsertion(str base, char insert){
+    if(base.sz == 0)
+        return base + insert;
+    ll mid = base.sz / 2;
+    out(str("? ") + base[mid] + " " + insert);
+    str ans = in();
+    if(ans == "<")
+        return base.substr(0, mid+1) + binaryInsertion(base.substr(mid+1, base.sz-mid-1), insert);
+    return binaryInsertion(base.substr(0, mid), insert) + base.substr(mid, base.sz-mid);
+}
+
+str mergeInsertSort(str base){
+    if(base.sz <= 1)
+        return base;
+
+    str upper;
+    s(char) rest;
+    d(char, char) lower2upper;
+    while(base.sz >= 2){
+        char a = base[0];
+        char b = base[1];
+        base = base.substr(2, base.sz-2);
+
+        out(str("? ") + a + " " + b);
+        str ans = in();
+        if(ans == "<"){
+            rest.insert(a);
+            upper += b;
+            lower2upper[a] = b;
+        } else {
+            rest.insert(b);
+            upper += a;
+            lower2upper[b] = a;
+        }
+    }
+    str ans = mergeInsertSort(upper);
+
+    if(base.sz)
+        rest.insert(base[0]);
+
+    while(rest.sz){
+        char next2place = *rest.bn;
+        ll count = ans.sz;
+        if(lower2upper.count(next2place))
+            count = ans.find(lower2upper[next2place]);
+        foreach(c, rest){
+            ll curcount = ans.sz;
+            if(lower2upper.count(c))
+                curcount = ans.find(lower2upper[c]);
+            if(curcount == 0){
+                next2place = c;
+                count = curcount;
+                break;
+            }
+            if(log2ll(curcount)<log2ll(count)){
+                next2place = c;
+                count = curcount;
+                continue;
+            }
+            if(log2ll(curcount) == log2ll(count) && curcount > count){
+                next2place = c;
+                count = curcount;
+                continue;
+            }
+        }
+        ans = binaryInsertion(ans.substr(0, count), next2place) + ans.substr(count, ans.sz-count);
+        rest.erase(next2place);
+    }
+    
+    return ans;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "";
+    lg(N);
+    forn(n, N)
+        result += 'A' + n;
+    lg(result);
+    result = mergeInsertSort(result);
+    out("! " + result);
 }
 
 } // namespace task
