diff --git a/CodeJam/Main.cpp b/examples/template_tests/strongly_connected_components/Main.cpp
index 57063df..05c9d95 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/strongly_connected_components/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1009,11 +1009,25 @@ namespace task {
 void init(){
 }
 
+ll V, E;
+v(s(ll)) adjacency_list;
+
 void readInput(){
+    str t;
+    cin >> t >> V >> E;
+    lassert(t=="X", "wrong input format");
+    adjacency_list.cl;
+    adjacency_list.resize(V);
+    forn(i, E){
+        ll a,b;
+        cin >> a >> b;
+        adjacency_list[a].insert(b);
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = strongly_connected_components_tarjan(adjacency_list);
 }
 
 } // namespace task
