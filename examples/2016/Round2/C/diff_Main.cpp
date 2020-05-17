diff --git a/CodeJam/Main.cpp b/examples/2016/Round2/C/Main.cpp
index e858c1d..9f0cc1f 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2016/Round2/C/Main.cpp
@@ -1,10 +1,10 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
-#define DEFAULT_VAL "IMPOSSIBLE"
+#define DEFAULT_VAL "\nIMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1012,11 +1012,93 @@ namespace task {
 void init(){
 }
 
+ll R, C;
+d(ll, v(cell)) love;
+v(v(ll)) maze;
+
 void readInput(){
+    cin >> R >> C;
+    ll size=2*(R+C);
+
+    love.cl;
+    maze.assign(R, v(ll)(C, 0));
+
+    forn(i, R+C){
+        ll t1, t2;
+        cin >> t1 >> t2;
+        ll dist = (size+t2-t1)%size;
+        lassert(dist>0, "dist was negative");
+        if( (size+t1-t2)%size < dist){
+            swap(t1, t2);
+            dist = (size+t2-t1)%size;
+            lassert(dist>0, "dist was negative");
+        }
+        love[dist].pb(cell(t1,t2));
+    }
+}
+
+p(ll, cell) get_start_position(ll lover){
+    // Map from outer cell number to a direction facing into the maze
+    // and the position of the outer cell
+    // 0->downwards, 1->rightwards, 2->upwards, 3->leftwards
+    //  W
+    // S N
+    //  E
+    if(lover <= C)
+        return mp(0, cell(-1, lover - 1));
+    lover -= C;
+    if(lover <= R)
+        return mp(3, cell(lover - 1, C));
+    lover -= R;
+    if(lover <= C)
+        return mp(2, cell(R, C - lover));
+    lover -= C;
+    return mp(1, cell(R - lover, -1));
+}
+
+bool inside_maze(cell pos){
+    if(pos.x<0 || pos.y < 0) return false;
+    if(pos.x>=R || pos.y >= C) return false;
+    return true;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    d(ll, char) hedges = {{0, '/'}, {1, '\\'}, {3, '/'}};
+    foreach(dist_pairs, love){
+        llog("current distance", dist_pairs.st);
+        foreach(pair, dist_pairs.nd){
+            llog("current pair", pair);
+            cell final_pos = get_start_position(pair.y).nd;
+            p(ll, cell) direction_pos = get_start_position(pair.x);
+            cell pos = direction_pos.nd;
+            llog("start pos", pos);
+            ll direction = direction_pos.st;
+            pos += DIRECTIONS[direction];
+
+            while(inside_maze(pos)){
+                llog("walked over", pos);
+                if (maze[pos.x][pos.y] == 0)
+                    maze[pos.x][pos.y] = (direction & 1) * 2 + 1;
+                direction ^= maze[pos.x][pos.y];
+                pos += DIRECTIONS[direction];
+            }
+            llog("finished at pos", pos);
+            llog("target final pos", final_pos);
+
+            if (final_pos != pos){
+                result = "";
+                return;
+            }
+        }
+    }
+    result = "\n";
+    forn(r, R){
+        forn(c, C){
+            result += hedges[maze[r][c]];
+        }
+        if(r!=R-1) result += "\n";
+    }
 }
 
 } // namespace task
