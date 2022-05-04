diff --git a/CodeJam/Main.cpp b/examples/2020/Round1A/C/Main.cpp
index 00aa56c..4669875 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1A/C/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
-// #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
+#define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
 #define COMM_TYPE ll
 
 // The maintained and empty code template can be found at:
@@ -1544,11 +1544,105 @@ void init(){
     cin >> T;
 }
 
+ll R, C, sum_sk;
+v(v(ll)) sk;
+
+v(v(ll)) up, down, left, right;
+
+v(cell) get_compass_neigh(ll i, ll j){
+    v(cell) res;
+    if(up[i][j] != -1){
+        res.emplace_back(up[i][j], j);
+    }
+    if(down[i][j] != R){
+        res.emplace_back(down[i][j], j);
+    }
+    if(left[i][j] != -1){
+        res.emplace_back(i, left[i][j]);
+    }
+    if(right[i][j] != C){
+        res.emplace_back(i, right[i][j]);
+    }
+    return res;
+}
+
 void readInput(){
+    sk.cl;
+    up.cl;
+    down.cl;
+    left.cl;
+    right.cl;
+    cin >> R >> C;
+    sk = v(v(ll))(R, v(ll)(C));
+    up = v(v(ll))(R, v(ll)(C));
+    down = v(v(ll))(R, v(ll)(C));
+    left = v(v(ll))(R, v(ll)(C));
+    right = v(v(ll))(R, v(ll)(C));
+    ll t;
+    sum_sk = 0;
+    forn(i, R){
+        forn(j, C){
+            cin >> t;
+            sk[i][j] = t;
+            sum_sk += t;
+            up[i][j] = i-1;
+            down[i][j] = i+1;
+            left[i][j] = j-1;
+            right[i][j] = j+1;
+        }
+    }
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    result = 0;
+    v(cell) todos;
+    forn(i, R){
+        forn(j, C){
+            todos.emplace_back(i,j);
+        }
+    }
+    v(v(ll)) when_todo(R, v(ll)(C, 0));
+    ll round = 0;
+    while(round++, true){
+        result += sum_sk;
+        // sim round
+        v(cell) elims;
+        v(cell) next_todos;
+        for(auto &todo: todos){
+            ll i = todo.x, j = todo.y;
+
+            if(sk[i][j] == 0) continue;
+
+            v(cell) neighs = get_compass_neigh(i, j);
+            ll sum = 0;
+            for(auto &neigh : neighs){
+                sum += sk[neigh.x][neigh.y];
+            }
+
+            if(sum > neighs.sz * sk[i][j]){
+                elims.emplace_back(i,j);
+                for(auto &neigh: neighs){
+                    if(when_todo[neigh.x][neigh.y] != round){
+                        when_todo[neigh.x][neigh.y] = round;
+                        next_todos.pb(neigh);
+                    }
+                }
+            }
+        }
+        if(elims.sz == 0) return;
+        // perform elims
+        for(auto &elim: elims){
+            sum_sk -= sk[elim.x][elim.y];
+            sk[elim.x][elim.y] = 0;
+            if(up[elim.x][elim.y]!=-1) down[up[elim.x][elim.y]][elim.y] = down[elim.x][elim.y];
+            if(down[elim.x][elim.y]!=R) up[down[elim.x][elim.y]][elim.y] = up[elim.x][elim.y];
+            if(left[elim.x][elim.y]!=-1) right[elim.x][left[elim.x][elim.y]] = right[elim.x][elim.y];
+            if(right[elim.x][elim.y]!=C) left[elim.x][right[elim.x][elim.y]] = left[elim.x][elim.y];
+        }
+        // compute new todos
+        swap(todos, next_todos);
+    }
 }
 
 } // namespace task
