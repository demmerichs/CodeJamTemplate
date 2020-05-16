diff --git a/CodeJam/Main.cpp b/examples/2019/Qualification/D/Main.cpp
index eeb0376..36cf235 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2019/Qualification/D/Main.cpp
@@ -1,10 +1,10 @@
 // #define DEFAULT_VAL_MODE    //remove comment on this line, to activate default value trigger
 #define DEFAULT_VAL_TRIGGER result.sz == 0
 #define DEFAULT_VAL "IMPOSSIBLE"
-// #define IA_MODE        //remove comment on this line, to activate interactive problem mode
-#define IA_ERROR_CODE "ERROR"
+#define IA_MODE        //remove comment on this line, to activate interactive problem mode
+#define IA_ERROR_CODE "-1"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1007,14 +1007,93 @@ using namespace std;
 
 namespace task {
 
+str firstq = "";
+v(str) followups;
+
 void init(){
+    forn(i, 1024){
+        if((i/16) % 2 == 0)
+            firstq += "0";
+        else
+            firstq += "1";
+    }
+    forn(i, 4){
+        str q = "";
+        forn(j, 1024){
+            if((j/(1<<(3-i))) % 2 == 0)
+                q += "0";
+            else
+                q += "1";
+        }
+        followups.pb(q);
+    }
 }
 
+ll N, B, F;
+
 void readInput(){
+    cin >> N >> B >> F;
+    llog("NBF:", N, B, F);
+}
+
+str ask(str question){
+    lassert(question.sz == 1024, "question.sz == 1024");
+    str end = question.substr(N);
+    question = question.substr(0, N);
+    lassert(question.sz == N, "question.sz == N");
+    out(question);
+    str answer = in();
+    lassert(answer.sz == N - B, "answer.sz == N - B");
+    answer += end;
+    lassert(end.sz == 1024 - N, "end.sz == 1024 - N");
+    lassert(answer.sz == 1024 - B, "answer.sz == 1024 - B");
+    return answer;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    str initial = ask(firstq);
+    lassert(initial.sz == 1024 - B, "initial.sz == 1024 - B");
+    v(v(str)) groups(1<<6);
+    v(ll) bads(1<<6, 16);
+    char last = '0';
+    ll counter = 0;
+    forn(i, 1024 - B){
+        if(initial[i] == last){
+            --bads[counter];
+        } else {
+            last = initial[i];
+            ++counter;
+            --bads[counter];
+        }
+    }
+    forn(i, 4){
+        str answer = ask(followups[i]);
+        forn(j, 1<<6){
+            groups[j].pb(answer.substr(0, 16-bads[j]));
+            answer = answer.substr(16-bads[j]);
+        }
+    }
+    v(ll) result;
+    forn(i, 1<<6){
+        ll counter = 0;
+        forn(j, 16 - bads[i]){
+            ll curidx = groups[i][0][j] * 8 + groups[i][1][j] * 4 + groups[i][2][j] * 2 + groups[i][3][j] - 15 * '0';
+            while(counter < curidx){
+                result.pb(counter + 16 * i);
+                ++counter;
+            }
+            ++counter;
+        }
+        while(counter < 16){
+            result.pb(counter + 16 * i);
+            ++counter;
+        }
+    }
+    lassert(result.sz == B, "result.sz == B");
+    cout << result << endl;
+    str answer = in();
+    lassert(answer == "1", "answer == 1");
 }
 
 } // namespace task
