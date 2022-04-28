diff --git a/CodeJam/Main.cpp b/examples/2019/Round1C/A/Main.cpp
index fa1026d..429fff9 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1C/A/Main.cpp
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
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1414,11 +1414,43 @@ void init(){
     cin >> T;
 }
 
+ll A;
+v(str) Pi;
+
+d(char, char) winmoves = {{'R', 'P'}, {'P', 'S'}, {'S', 'R'}};
+d(s(char), char) partial_win = {{{'R', 'S'}, 'R'}, {{'S', 'P'}, 'S'}, {{'P', 'R'}, 'P'}};
+
 void readInput(){
+    cin >> A;
+    Pi.resize(A);
+    forn(i, A) cin >> Pi[i];
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = "";
+    v(bool) still_alive(A, true);
+    while(true){
+        s(char) opp_moves;
+        forn(i, A){
+            if(!still_alive[i]) continue;
+            opp_moves.insert(Pi[i][result.sz % Pi[i].sz]);
+        }
+        if(opp_moves.sz == 3){
+            result = "";
+            break;
+        }
+        if(opp_moves.sz == 1){
+            result += winmoves[*opp_moves.bn];
+            break;
+        }
+        lassert(opp_moves.sz == 2, "something wrong with opp moves");
+        result += partial_win[opp_moves];
+        forn(i, A){
+            if(Pi[i][(result.sz-1)%Pi[i].sz]!=result[result.sz-1]) still_alive[i]=false;
+        }
+    }
+    lassert(result.sz <= 500, "too long result");
 }
 
 } // namespace task
