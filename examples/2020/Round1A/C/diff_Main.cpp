diff --git a/CodeJam/Main.cpp b/examples/2020/Round1A/C/Main.cpp
index 98774ea..9566508 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1A/C/Main.cpp
@@ -149,6 +149,19 @@ using namespace printerTools;
 //#region debugTools
 namespace debugTools{
 
+#ifdef LOCAL
+    #include <chrono>
+    auto start=std::chrono::high_resolution_clock::now(), stop=std::chrono::high_resolution_clock::now();
+
+    inline void start_timer(){start=std::chrono::high_resolution_clock::now();}
+    inline void stop_timer(){stop=std::chrono::high_resolution_clock::now();}
+    inline double get_time(){return std::chrono::duration<double>(stop - start).count();}
+#else
+    #define start_timer()
+    #define stop_timer()
+    #define get_time()
+#endif /*LOCAL*/
+
 inline void local_log(){
     std::cerr << std::endl;
 }
@@ -797,9 +810,15 @@ int main() {
     task::init();
     for(long long unsigned test=1; test<=tests; ++test){
         //read input
+        start_timer();
         task::readInput();
+        stop_timer();
+        llog("test set", test, "input reading took", get_time(), "s");
         //calc result
+        start_timer();
         task::calcFunction();
+        stop_timer();
+        llog("test set", test, "calculation   took", get_time(), "s");
 #ifndef IA_MODE
         //write output
         std::cout << "Case #" << test << ": ";
@@ -828,11 +847,105 @@ namespace task {
 void init(){
 }
 
+ll R, C, sum_sk;
+v(v(ll)) sk;
+
+v(v(ll)) up, down, left, right;
+
+v(p(ll, ll)) get_compass_neigh(ll i, ll j){
+    v(p(ll, ll)) res;
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
+    sk.clear();
+    up.clear();
+    down.clear();
+    left.clear();
+    right.clear();
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
+    v(p(ll, ll)) todos;
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
+        v(p(ll,ll)) elims;
+        v(p(ll, ll)) next_todos;
+        for(auto &todo: todos){
+            ll i = todo.st, j = todo.nd;
+
+            if(sk[i][j] == 0) continue;
+
+            v(p(ll,ll)) neighs = get_compass_neigh(i, j);
+            ll sum = 0;
+            for(auto &neigh : neighs){
+                sum += sk[neigh.st][neigh.nd];
+            }
+
+            if(sum > neighs.sz * sk[i][j]){
+                elims.emplace_back(i,j);
+                for(auto &neigh: neighs){
+                    if(when_todo[neigh.st][neigh.nd] != round){
+                        when_todo[neigh.st][neigh.nd] = round;
+                        next_todos.pb(neigh);
+                    }
+                }
+            }
+        }
+        if(elims.sz == 0) return;
+        // perform elims
+        for(auto &elim: elims){
+            sum_sk -= sk[elim.st][elim.nd];
+            sk[elim.st][elim.nd] = 0;
+            if(up[elim.st][elim.nd]!=-1) down[up[elim.st][elim.nd]][elim.nd] = down[elim.st][elim.nd];
+            if(down[elim.st][elim.nd]!=R) up[down[elim.st][elim.nd]][elim.nd] = up[elim.st][elim.nd];
+            if(left[elim.st][elim.nd]!=-1) right[elim.st][left[elim.st][elim.nd]] = right[elim.st][elim.nd];
+            if(right[elim.st][elim.nd]!=C) left[elim.st][right[elim.st][elim.nd]] = left[elim.st][elim.nd];
+        }
+        // compute new todos
+        swap(todos, next_todos);
+    }
 }
 
 } // namespace task
