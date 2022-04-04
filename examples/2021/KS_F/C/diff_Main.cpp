diff --git a/CodeJam/Main.cpp b/examples/2021/KS_F/C/Main.cpp
index 6e1211d..dc8872e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2021/KS_F/C/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
-#define DEFAULT_VAL_TRIGGER result.sz == 0
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_TRIGGER result == 5 * 1e6
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define COMM_TYPE ld
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1065,11 +1065,128 @@ void init(){
     cin >> T;
 }
 
+ll N;
+v(cell) stars;
+cell blue;
+
+d(ll, s(ll)) connects_through_blue;
+
 void readInput(){
+    cin >> N;
+    stars.resize(N);
+    connects_through_blue.cl;
+    ll px,py;
+    forn(i, N){
+        cin >> px >> py;
+        stars[i] = cell(px, py);
+    }
+    cin >> px >> py;
+    blue = cell(px, py);
+}
+
+bool line_contains_blue(ll s, ll e){
+    cell other_white = stars[e] - stars[s];
+    cell rel_blue = blue - stars[s];
+    ll k;
+    if(rel_blue.x != 0){
+        k = other_white.x / rel_blue.x;
+    } else {
+        k = other_white.y / rel_blue.y;
+    }
+    if(k<=1) return false;
+    if(rel_blue * k == other_white) return true;
+    return false;
+}
+
+ld length(ll s, ll e){
+    return sqrtl(norm(stars[s]-stars[e]));
+}
+
+ll sign (cell p1, cell p2, cell p3)
+{
+    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
+}
+
+bool all_on_line (ll s1, ll s2, ll s3) {
+    return sign(stars[s1], stars[s2], stars[s3]) == 0;
+}
+
+bool blue_inside (ll s1, ll s2, ll s3)
+{
+    ll d1, d2, d3;
+    bool all_neg, all_pos;
+
+    d1 = sign(blue, stars[s1], stars[s2]);
+    d2 = sign(blue, stars[s2], stars[s3]);
+    d3 = sign(blue, stars[s3], stars[s1]);
+
+    all_neg = (d1 < 0) && (d2 < 0) && (d3 < 0);
+    all_pos = (d1 > 0) && (d2 > 0) && (d3 > 0);
+
+    return all_neg || all_pos;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 5 * 1e6;
+
+    forn(s, N){
+        fornn(e, s+1, N){
+            if(line_contains_blue(s, e)){
+                connects_through_blue[s].insert(e);
+                connects_through_blue[e].insert(s);
+            }
+        }
+    }
+
+    forn(i, N){
+        lg(i);
+        lg(connects_through_blue[i]);
+    }
+
+    forn(s1, N){
+        fornn(s2, s1+1, N){
+            fornn(s3, s2+1, N){
+                if(blue_inside(s1,s2,s3)){
+                    result = min(result, length(s1, s2) + length(s2, s3) + length(s3, s1));
+                    lg(s1);
+                    lg(s2);
+                    lg(s3);
+                }
+                if(all_on_line(s1, s2, s3)) continue;
+                if(connects_through_blue[s1].count(s2)){
+                    foreach(s4, connects_through_blue[s3]){
+                        result = min(result, length(s1, s3) + length(s1, s4) + length(s2, s3) + length(s2, s4));
+                        lg("quad");
+                        lg(s1);
+                        lg(s2);
+                        lg(s3);
+                        lg(s4);
+                    }
+                }
+                if(connects_through_blue[s1].count(s3)){
+                    foreach(s4, connects_through_blue[s2]){
+                        result = min(result, length(s1, s2) + length(s1, s4) + length(s3, s2) + length(s3, s4));
+                        lg("quad");
+                        lg(s1);
+                        lg(s3);
+                        lg(s2);
+                        lg(s4);
+                    }
+                }
+                if(connects_through_blue[s2].count(s3)){
+                    foreach(s4, connects_through_blue[s1]){
+                        result = min(result, length(s2, s1) + length(s2, s4) + length(s3, s1) + length(s3, s4));
+                        lg("quad");
+                        lg(s2);
+                        lg(s3);
+                        lg(s1);
+                        lg(s4);
+                    }
+                }
+            }
+        }
+    }
 }
 
 } // namespace task
