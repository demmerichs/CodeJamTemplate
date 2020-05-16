diff --git a/CodeJam/Main.cpp b/examples/2016/Round2/C/Main.cpp
index e858c1d..e929cd1 100644
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
@@ -1012,11 +1012,232 @@ namespace task {
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
+ll walk_left_wall(cell cur_pos, char incoming_dir){
+    lassert(incoming_dir=='N' || incoming_dir=='S' || incoming_dir=='W' || incoming_dir=='E', "assert not a valid direction");
+    llog("walking over", cur_pos, "and walking to", incoming_dir);
+    cell mc = cell(R-cur_pos.y, cur_pos.x+1);
+    llog("maze grid coords", mc);
+    if(mc.x == 0 || mc.x == R+1 || mc.y == 0 || mc.y == C+1){
+        llog("finished walk");
+        llog("finished walk at", ll(maze[mc.x][mc.y]));
+        return maze[mc.x][mc.y];
+    }
+    char outdir;
+    lassert(maze[mc.x][mc.y] == 0 || maze[mc.x][mc.y] == '/' || maze[mc.x][mc.y] == '\\', "not a valid maze character");
+    if(maze[mc.x][mc.y] == 0){
+        if(incoming_dir=='N'){
+            outdir = 'W';
+            maze[mc.x][mc.y] = '\\';
+        }
+        if(incoming_dir=='S'){
+            outdir = 'E';
+            maze[mc.x][mc.y] = '\\';
+        }
+        if(incoming_dir=='W'){
+            outdir = 'S';
+            maze[mc.x][mc.y] = '/';
+        }
+        if(incoming_dir=='E'){
+            outdir = 'N';
+            maze[mc.x][mc.y] = '/';
+        }
+    } else if (maze[mc.x][mc.y] == '/'){
+        switch(incoming_dir){
+            case 'N':
+                outdir = 'E';
+                break;
+            case 'S':
+                outdir = 'W';
+                break;
+            case 'E':
+                outdir = 'N';
+                break;
+            case 'W':
+                outdir = 'S';
+                break;
+        }
+    } else if (maze[mc.x][mc.y] == '\\'){
+        switch(incoming_dir){
+            case 'N':
+                outdir = 'W';
+                break;
+            case 'S':
+                outdir = 'E';
+                break;
+            case 'E':
+                outdir = 'S';
+                break;
+            case 'W':
+                outdir = 'N';
+                break;
+        }
+    }
+    return walk_left_wall(cur_pos+DIRECTIONS[outdir], outdir);
+}
+
+bool connect(cell lovers){
+    cell start;
+    char dir='#';
+    forn(r, R){
+        if(maze[r+1][0] == lovers.x){
+            start=cell(-1, R-1-r);
+            dir='E';
+        }
+        if(maze[r+1][C+1] == lovers.x){
+            start=cell(C, R-1-r);
+            dir='W';
+        }
+    }
+    forn(c, C){
+        if(maze[0][c+1] == lovers.x){
+            start=cell(c,R);
+            dir='S';
+        }
+        if(maze[R+1][c+1] == lovers.x){
+            start=cell(c, -1);
+            dir='N';
+        }
+    }
+    lassert(dir!='#', "could not find start");
+    llog("starting walk at ", start, "with dir", dir);
+    ll outcome=walk_left_wall(start+DIRECTIONS[dir], dir);
+    return outcome == lovers.y;
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
+    // v(ll) left_lovers;
+    // forn(i, 2*(R+C)){
+    //     left_lovers.pb(i+1);
+    // }
+    // while(love.sz>0){
+    //     cell sol(0,0);
+    //     ll pos=0;
+    //     forn(i, left_lovers.sz-1){
+    //         pos=i;
+    //         sol = cell(left_lovers[i], left_lovers[i+1]);
+    //         if(love.count(sol)) break;
+    //         sol = cell(left_lovers[i+1], left_lovers[i]);
+    //         if(love.count(sol)) break;
+    //         sol = cell(0,0);
+    //     }
+    //     if(sol.real()==0){
+    //         pos=left_lovers.sz-1;
+    //         sol = cell(left_lovers[0], left_lovers.bk);
+    //         if(0 == love.count(sol)){
+    //             sol = cell(left_lovers.bk, left_lovers[0]);
+    //             if(0==love.count(sol)) sol=cell(0,0);
+    //         }
+    //     }
+    //     if(sol.real()==0){
+    //         result = "";
+    //         return;
+    //     }
+    //
+    //     love.erase(sol);
+    //     if(sol.real()!=left_lovers[pos]){
+    //         sol = cell(sol.imag(), sol.real());
+    //     }
+    //     if(pos==left_lovers.sz-1){
+    //         left_lovers.popb;
+    //         left_lovers.erase(left_lovers.bn);
+    //     } else {
+    //         left_lovers.erase(left_lovers.bn+pos+1);
+    //         left_lovers.erase(left_lovers.bn+pos);
+    //     }
+    //
+    //     llog("found lover:", sol);
+    //     llog("left lovers:", left_lovers);
+    //     if(!connect(sol)){
+    //         result = "";
+    //         return;
+    //     }
+    // }
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
