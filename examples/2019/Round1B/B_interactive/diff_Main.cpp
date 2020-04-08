diff --git a/CodeJam/Main.cpp b/examples/2019/Round1B/B_interactive/Main.cpp
index 0493fca..91fe0f7 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Round1B/B_interactive/Main.cpp
@@ -1,9 +1,9 @@
 // #define DEFAULT_VAL    //remove comment on this line, to activate default value trigger
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define ERROR_WORD "IMPOSSIBLE"
-#define COMM_TYPE ll
-#define IA_ERROR_CODE "ERROR"
+#define COMM_TYPE str
+#define IA_ERROR_CODE "-1"
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -825,14 +825,47 @@ using namespace std;
 
 namespace task {
 
+ll W;
+
 void init(){
+    W = stoll(in());
 }
 
+ll large, small;
+
 void readInput(){
+    out("210");
+    large = stoll(in());
+    llog("large value saved:", large);
+    out("42");
+    small = stoll(in());
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    lassert(large % (1L<<35) == 0, "large not divisible by expected");
+    large /= (1L<<35);
+    ll R6 = large % (1L<<7);
+    large /= (1L<<7);
+    ll R5 = large % (1L<<7);
+    large /= (1L<<10);
+    ll R4 = large;
+    lassert(small % (1L<<7) == 0, "small not divisible by expected");
+    small /= (1L<<7);
+    small -= R6;
+    small -= 2 * R5;
+    small -= 8 * R4;
+    lassert(small % (1L<<7) == 0, "small not divisible by expected");
+    small /= (1L<<7);
+    ll R3 = small % (1L<<7);
+    small /= (1L<<7);
+    ll R2 = small % (1L<<7);
+    small /= (1L<<21);
+    ll R1 = small;
+    sstr ss;
+    ss << R1 << " " << R2 << " " << R3 << " " << R4 << " " << R5 << " " << R6;
+    out(ss.str());
+    in();
 }
 
 } // namespace task
