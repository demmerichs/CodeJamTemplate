diff --git a/CodeJam/Main.cpp b/examples/2020/Qualification/E/Main.cpp
index e05e235..5d9ed99 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Qualification/E/Main.cpp
@@ -1,11 +1,11 @@
-// #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
+#define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE -1
 #define IA_COMM_LOG    //add comment on this line, to deactivate the interactive communication error log
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/demmerichs/CodeJamTemplate
@@ -1555,11 +1555,114 @@ void init(){
     cin >> T;
 }
 
+ll N, K;
 void readInput(){
+    cin >> N >> K;
+}
+
+v(ll) get_parts(){
+    ll A=-1, B=-1, C=-1;
+    fore(a,1, N){
+        fore(b,1, N){
+            fore(c,1,N){
+                if((a==b || a == c) && b != c) continue;
+                if(N==3 && b==c && a!=b) continue;
+                if((N-2)*a+b+c != K) continue;
+                A = a;
+                B = b;
+                C = c;
+                break;
+            }
+            if(A>=0) break;
+        }
+        if(A>=0) break;
+    }
+    if(A==-1) return v(ll)();
+    v(ll) res(N, A-1);
+    res[0] = B-1;
+    res[1] = C-1;
+    llog("res",res);
+    lassert(accumulate(all(res), 0) == K-N, "sum of parts does not fit");
+    return res;
+}
+
+v(v(ll)) ls;
+
+str visu(){
+    sstr res;
+    forn(i,N){
+        forn(j,N){
+            ll v = ls[i][j];
+            if(v==N || v == -1){
+                // result = "";
+                res << "#";
+                // return;
+            } else
+                res << v;
+            if(j<N-1) res << " ";
+        }
+        if(i<N-1) res << endl;
+    }
+    return "\n"+res.str();
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    v(ll) parts = get_parts();
+    if(parts.sz == 0){
+        result = "";
+        return;
+    }
+    if(K==N+1 || K == N*N - 1){
+        llog(parts);
+        lassert(false, "get_parts did produce something valid what?");
+        result = "";
+        return;
+    }
+    ls.cl;
+    ls = v(v(ll))(N, v(ll)(N, -1));
+    forn(i,N){
+        ls[i][i] = parts[i];
+    }
+
+    forn(r,N){
+        v(v(bool)) col_can_have(N, v(bool)(N, true));
+        forn(i, N){
+            forn(j, N){
+                if(ls[i][j] >= 0)
+                    col_can_have[j][ls[i][j]] = false;
+            }
+        }
+        forn(i, N){
+            col_can_have[i][ls[r][r]] = false;
+            col_can_have[r][i] = false;
+        }
+        col_can_have[r][ls[r][r]] = true;
+        v(ll) matched_vals, matched_cols;
+        ll num_matches = maximal_bipartite_matching(col_can_have, matched_vals, matched_cols);
+        lassert(num_matches == N, "how did this happen?");
+        forn(c, N){
+            ls[r][c] = matched_vals[c];
+        }
+    }
+
+    sstr res;
+    result = "POSSIBLE\n";
+    forn(i,N){
+        forn(j,N){
+            // ll v = distance(occ[i][j].bn, find(all(occ[i][j]), -1));
+            ll v = ls[i][j];
+            if(v==N || v == -1){
+                // res << "#";
+                result = "";
+                return;
+            } else
+                res << v+1;
+            if(j<N-1) res << " ";
+        }
+        if(i<N-1) res << endl;
+    }
+    result += res.str();
 }
 
 } // namespace task
