diff --git a/CodeJam/Main.cpp b/examples/2020/Round1A/A/Main.cpp
index d7377dd..fdb44d3 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1A/A/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -897,11 +897,58 @@ namespace task {
 void init(){
 }
 
+ll N;
+v(str) pats;
+str start, end;
+
 void readInput(){
+    cin >> N;
+    pats.cl;
+    start.cl;
+    end.cl;
+    forn(i,N){
+        str t;
+        cin >> t;
+        pats.pb(t);
+        if(t[0] != '*'){
+            if(start.sz < t.find("*")){
+                start = t.substr(0, t.find("*"));
+            }
+        }
+        if(t[t.sz-1] != '*'){
+            if(end.sz < t.sz - t.rfind("*")-1){
+                end = t.substr(t.rfind("*")+1,t.sz-t.rfind("*")-1);
+            }
+        }
+    }
+    llog("start", start);
+    llog("end", end);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = start;
+    forn(i,N){
+        ll f = pats[i].find("*");
+        ll l = pats[i].rfind("*");
+        str cur_start = pats[i].substr(0, f);
+        str cur_end = pats[i].substr(l+1, pats[i].sz - l - 1);
+        str mid = pats[i].substr(f, l-f);
+        while(mid.find("*") != string::npos){
+            mid.replace(mid.find("*"), 1, "");
+        }
+        if(cur_start != start.substr(0, cur_start.sz)){
+            result = "*";
+            return;
+        }
+        if(cur_end != end.substr(end.sz - cur_end.sz, cur_end.sz)){
+            result = "*";
+            return;
+        }
+        result += mid;
+
+    }
+    result += end;
 }
 
 } // namespace task
