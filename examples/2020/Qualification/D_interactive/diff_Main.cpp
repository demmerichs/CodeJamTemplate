diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/D_interactive/Main.cpp
index b62b2a6..d58f692 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/D_interactive/Main.cpp
@@ -1,11 +1,11 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE -1
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE "N"
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1016,15 +1016,91 @@ using namespace std;
 
 namespace task {
 
+ll B;
 void init(){
-    cin >> T;
+    cin >> T >> B;
 }
 
+v(bool) start;
+v(bool) end;
+
 void readInput(){
+    start.cl;
+    end.cl;
+}
+
+void invert(){
+    forn(i, start.sz){
+        start[i] = !start[i];
+        end[i] = !end[i];
+    }
+}
+
+bool ask(ll pos){
+    out(pos+1);
+    return in() == "1";
+}
+
+void reorganize(){
+    ll same_pos = 0;
+    while(same_pos < start.sz){
+        if(start[same_pos] == end[same_pos]){
+            break;
+        }
+        same_pos++;
+    }
+    if(same_pos == start.sz){
+        ask(0);
+    } else {
+        bool bit = ask(same_pos);
+        if(bit != start[same_pos]){
+            invert();
+        }
+    }
+    ll diff_pose = 0;
+    while(diff_pose < start.sz){
+        if(start[diff_pose] != end[diff_pose]){
+            break;
+        }
+        diff_pose++;
+    }
+    if(diff_pose == start.sz){
+        ask(0);
+    } else {
+        bool bit = ask(diff_pose);
+        if(bit != start[diff_pose]){
+            v(bool) t = start;
+            start = end;
+            end = t;
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    while(start.sz + end.sz < B){
+        reorganize();
+        forn(i, 4){
+            start.pb(ask(start.sz));
+            end.pb(ask(B-1-end.sz));
+        }
+    }
+    reorganize();
+    while(start.sz + end.sz > B){
+        start.popb;
+        end.popb;
+    }
+    sstr outr;
+    foreachc(bit, start){
+        if(bit) outr << "1"; else outr << "0";
+    }
+    forn(i, end.sz){
+        if(end[end.sz-1-i]) outr << "1"; else outr << "0";
+    }
+    llog("start", start);
+    llog("end", end);
+    out(outr.str());
+    in();
 }
 
 } // namespace task
