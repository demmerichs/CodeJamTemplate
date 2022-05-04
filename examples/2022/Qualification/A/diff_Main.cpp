diff --git a/CodeJam/Main.cpp b/examples/2022/Qualification/A/Main.cpp
index 00aa56c..4038cee 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2022/Qualification/A/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1544,11 +1544,27 @@ void init(){
     cin >> T;
 }
 
+d(p(bool, bool), char) draw = {{{false, false}, '.'}, {{false, true}, '|'}, {{true, false}, '-'}, {{true, true}, '+'}};
+ll R, C;
+
 void readInput(){
+    cin >> R >> C;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    sstr out;
+    out << endl;
+    forn(r, R*2+1){
+        forn(c, C*2+1){
+            bool horiline = r%2 == 0 && (r>1 || c>1);
+            bool vertline = c%2 == 0 && (r>1 || c>1);
+            out << draw[mp(horiline, vertline)];
+        }
+        out << endl;
+    }
+    result = out.str();
+    result = result.substr(0, result.sz-1);
 }
 
 } // namespace task
