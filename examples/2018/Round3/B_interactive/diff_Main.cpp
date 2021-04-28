diff --git a/CodeJam/Main.cpp b/examples/2018/Round3/B_interactive/Main.cpp
index 42da9e7..c6aa9fa 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2018/Round3/B_interactive/Main.cpp
@@ -1,7 +1,7 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
@@ -1024,11 +1024,155 @@ void init(){
     cin >> T;
 }
 
+ll L, U, N;
+v(v(bool)) adj;
+
 void readInput(){
+    cin >> L >> U;
+    N = L;
+    lg(L);
+    lg(U);
+    lg(N);
+    // N = U;
+
+    out(N);
+    out(mp(1, N-2));
+    out(mp(1, N));
+    out(mp(2, N-4));
+    out(mp(N-6, N-5));
+    out(mp(N-6, N-3));
+    out(mp(N-5, N-1));
+    out(mp(N-5, N));
+    out(mp(N-4, N-3));
+    out(mp(N-4, N-2));
+    out(mp(N-4, N-1));
+    out(mp(N-3, N-2));
+    out(mp(N-3, N));
+    out(mp(N-2, N-1));
+    out(mp(N-1, N));
+    fore(i, 1, N-7){
+        out(mp(i, i+1));
+        out(mp(i, i+2));
+    }
+
+    adj.assign(N+1, v(bool)(N+1, false));
+    ll incomingN = in();
+    lassert(N==incomingN, "return is not same size");
+    // lassert(N==in(), "return is not same size");
+    forn(i, 2*N){
+        ll a,b;
+        a = in();
+        b = in();
+        adj[a][b] = true;
+        adj[b][a] = true;
+    }
+    lg(adj);
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) Xi(N+1, -1);
+
+    s(ll) regulars;
+    fore(i, 1, N){
+        ll tri_count=0;
+        fore(m, 1, N){
+            if(!adj[i][m]) continue;
+            fore(n, 1, N){
+                if(adj[m][n] && adj[n][i]){
+                    tri_count++;
+                }
+            }
+        }
+        if(tri_count==6) regulars.insert(i);
+    }
+
+    lg(regulars);
+
+    s(ll) corners;
+    foreach(reg, regulars){
+        fore(i, 1, N){
+            if(regulars.count(i)) continue;
+            if(adj[reg][i]) corners.insert(i);
+        }
+    }
+
+    lg(corners);
+    lassert(corners.sz == 4, "not 4 corners?");
+
+    s(ll) rest;
+    fore(i, 1, N){
+        if(corners.count(i) || regulars.count(i)) continue;
+        rest.insert(i);
+    }
+
+    lg(rest);
+    lassert(rest.sz == 5, "not 5 rest?");
+
+    foreach(cr, corners){
+        foreach(r1, rest){
+            foreach(r2, rest){
+                if(adj[cr][r1] && adj[cr][r2] && adj[r1][r2]){
+                    lassert(Xi[N-5] == -1 || Xi[N-5] == cr, "was set differently");
+                    Xi[N-5] = cr;
+                }
+            }
+        }
+    }
+
+    llog("found N-5");
+    lg(Xi);
+
+    foreach(cr, corners){
+        ll count_rest_neigh=0;
+        foreach(r, rest) count_rest_neigh += adj[r][cr];
+        if(count_rest_neigh==2){
+            if(cr==Xi[N-5]) continue;
+            Xi[1] = cr;
+        } else {
+            if(adj[cr][Xi[N-5]]) Xi[N-6]=cr;
+            else Xi[2] = cr;
+        }
+    }
+
+    llog("found all corners");
+    lg(Xi);
+
+    foreach(r, rest){
+        if(adj[r][Xi[N-6]]){
+            Xi[N-3]=r; continue;
+        }
+        if(adj[r][Xi[2]]){
+            Xi[N-4]=r; continue;
+        }
+        if(adj[r][Xi[1]] && adj[r][Xi[N-5]]){
+            Xi[N] = r; continue;
+        }
+        if(adj[r][Xi[N-5]]){
+            Xi[N-1]=r; continue;
+        }
+        Xi[N-2] = r;
+    }
+
+    llog("found rest");
+    lg(Xi);
+
+    fore(i, 3, N-7){
+        foreach(n, regulars){
+            if(adj[n][Xi[i-2]]){
+                Xi[i]=n;
+                regulars.erase(n);
+                break;
+            }
+        }
+    }
+
+    llog("found all");
+    lg(Xi);
+
+    lassert(Xi[0]==-1, "dummy value not set");
+    Xi.erase(Xi.bn);
+    out(Xi);
 }
 
 } // namespace task
