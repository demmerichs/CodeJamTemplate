diff --git a/CodeJam/Main.cpp b/examples/template_tests/strongly_connected_components/small_graphs/Main.cpp
index 2150379..c1969b1 100644
--- a/CodeJam/Main.cpp
+++ b/examples/template_tests/strongly_connected_components/small_graphs/Main.cpp
@@ -5,7 +5,7 @@
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE v(ll)
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1570,11 +1570,25 @@ void init(){
     cin >> T;
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
