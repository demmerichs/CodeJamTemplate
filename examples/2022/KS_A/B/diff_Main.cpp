diff --git a/CodeJam/Main.cpp b/examples/2022/KS_A/B/Main.cpp
index 0f47b9d..5047469 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/KS_A/B/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1569,11 +1569,36 @@ void init(){
     cin >> T;
 }
 
+str N;
+
 void readInput(){
+    cin >> N;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "99" + N;
+
+    ll sod = 0;
+    forn(i, N.sz){
+        sod += N[i] - '0';
+    }
+    ll rest = sod % 9;
+
+    v(char) add_digits;
+    add_digits.pb('0' + (9 - rest));
+    if(rest == 0)
+        add_digits.pb('0');
+
+    forn(i, add_digits.sz){
+        char add = add_digits[i];
+        forn(pos, N.sz+1){
+            str cur_poss = N.substr(0, pos) + add + N.substr(pos, N.sz-pos);
+            lg(cur_poss);
+            if(cur_poss < result && cur_poss[0] > '0')
+                result = cur_poss;
+        }
+    }
 }
 
 } // namespace task
