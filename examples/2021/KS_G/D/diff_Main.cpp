diff --git a/CodeJam/Main.cpp b/examples/2021/KS_G/D/Main.cpp
index e05e235..f46b158 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_G/D/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(cell)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -122,7 +122,7 @@ std::ostream& _outstream_iteratables(std::ostream& os, T iteratable){
         return os;
     os << *iteratable.begin();
     for(auto it = (++iteratable.begin()); it != iteratable.end(); ++it)
-        os << ' ' << *it;
+        os << std::endl << *it;
     return os;
 }
 
@@ -1537,7 +1537,7 @@ int main() {
         }
         else{
             llog("default val NOT triggered");
-            std::cout << result << std::endl;
+            std::cout << "POSSIBLE" << std::endl << result << std::endl;
         }
 #endif /*DEFAULT_VAL_MODE*/
 #endif /*IA_MODE*/
@@ -1555,11 +1555,63 @@ void init(){
     cin >> T;
 }
 
+ll B, A;
+
 void readInput(){
+    result.cl;
+    cin >> B >> A;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    if(A+2-B<0) return;
+    ll E = (A+2-B)%2;
+    ll I = (A+2-B-E)/2;
+    if(I<0) return;
+    lg(I);
+
+    if(B==3){
+        result.pb({0, 0});
+        result.pb({1-E, 2});
+        result.pb({I+1, 1});
+        return;
+    }
+
+    if(B==4){
+        if(I==0){
+            result.pb({0,0});
+            result.pb({0,1});
+            result.pb({1,1+E});
+            result.pb({1,0});
+        } else {
+            result.pb({0,1-E});
+            result.pb({1,0});
+            result.pb({I+1,1});
+            result.pb({1-E,2});
+        }
+        return;
+    }
+
+    ll xoffset = B;
+    result.pb({xoffset-1-E, 2});
+    result.pb({xoffset, 2});
+    result.pb({xoffset+I+1, 1});
+    result.pb({xoffset, 0});
+    result.pb({xoffset, 1});
+    ll restB = B - 5;
+    // xoffset-=E;
+    while(restB>=2){
+        xoffset--;
+        result.pb({xoffset,0});
+        result.pb({xoffset,1});
+        restB-=2;
+    }
+    if(restB==0)return;
+    // if(restB == 2){
+    //     result.pb({xoffset-1,0});
+    //     result.pb({xoffset-1,1});
+    // }
+    result.pb({xoffset-1, 1});
 }
 
 } // namespace task
