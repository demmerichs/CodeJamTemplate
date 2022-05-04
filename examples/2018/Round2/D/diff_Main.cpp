diff --git a/CodeJam/Main.cpp b/examples/2018/Round2/D/Main.cpp
index 00aa56c..2089172 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round2/D/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1544,11 +1544,96 @@ void init(){
     cin >> T;
 }
 
-void readInput(){
+ll R, C;
+v(v(bool)) dg;
+v(v(bool)) matches_pattern;
+v(cell) visit_queue;
+v(v(bool)) visited;
+
+bool dg_contains_pattern(const v(v(bool)) &pattern){
+    ll pattern_rows = pattern.sz;
+    ll pattern_cols = pattern[0].sz;
+    fore(r, 0, R - pattern_rows){
+        fore(c, 0, C - pattern_cols){
+            bool ok = true;
+            forn(pr, pattern_rows)
+                forn(pc, pattern_cols)
+                    ok &= (dg[r + pr][c + pc] == pattern[pr][pc]);
+            if (ok) return true;
+        }
+    }
+    return false;
+}
+
+ll maximal_connected_component(){
+    ll ans = 0;
+    forn(r, R) forn(c, C) visited[r][c]=0;
+    forn(r, R) {
+        forn(c, C) {
+            if (visited[r][c] || !matches_pattern[r][c])
+                continue;
+
+            visit_queue.assign(1, cell(r,c));
+            visited[r][c] = 1;
+
+            forn(b, visit_queue.sz){
+                foreach(del, DIRECTIONS){
+                    cell n = visit_queue[b] + del;
+                    if (n.x >= 0 && n.y >= 0 && n.x < R && n.y < C) {
+                        if (!visited[n.x][n.y] && matches_pattern[n.x][n.y]) {
+                            visited[n.x][n.y] = 1;
+                            visit_queue.emplace_back(n.x, n.y);
+                        }
+                    }
+                }
+            }
+            ans = max<ll>(ans, visit_queue.sz);
+        }
+    }
+    return ans;
+}
+
+void readInput() {
+    cin >> R >> C;
+    dg.assign(R, v(bool)(C, false));
+    matches_pattern.assign(R, v(bool)(C));
+    visited.assign(R, v(bool)(C));
+    visit_queue.cl;
+    forn(r, R){
+        str line;
+        cin >> line;
+        forn(c, C){
+            if(line[c]=='B') dg[r][c]=true;
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    fore(border_row, 1, R){
+        fore(border_col, 1, C){
+            forn(pattern_idx, 16) {
+                v(v(bool)) pattern(border_row < R ? 2 : 1, v(bool)(border_col < C ? 2 : 1));
+                forn(pr, pattern.sz){
+                    forn(pc, pattern[pr].sz){
+                        pattern[pr][pc] = (pattern_idx >> (((pr >= 1) << 1) + (pc >= 1))) & 1;
+                    }
+                }
+                if (!dg_contains_pattern(pattern)) {
+                    continue;
+                }
+
+                forn(r, R){
+                    forn(c, C){
+                        bool target_value = pattern[r >= border_row][c >= border_col];
+                        matches_pattern[r][c] = (dg[r][c] == target_value);
+                    }
+                }
+                result = max(result, maximal_connected_component());
+            }
+        }
+    }
 }
 
 } // namespace task
