diff --git a/CodeJam/Main.cpp b/examples/2020/Round1B/C/Main.cpp
index fabbe5f..e55111e 100644
--- a/CodeJam/Main.cpp
+++ b/examples/2020/Round1B/C/Main.cpp
@@ -4,7 +4,7 @@
 // #define IA_MODE        //remove comment on this line, to activate interactive problem mode
 #define IA_ERROR_CODE "ERROR"
 // #define XY_NOTATION    //remove commment on this line, to activate xy notation on complex numbers
-#define COMM_TYPE ll
+#define COMM_TYPE str
 
 // The maintained and empty code template can be found at:
 // https://github.com/DavidS3141/CodeJamTemplate
@@ -1013,11 +1013,102 @@ namespace task {
 void init(){
 }
 
+ll R, S;
+v(p(ll,ll)) deck;
+v(p(ll,ll)) sorted;
+
 void readInput(){
+    cin >> R >> S;
+    deck.cl;
+    sorted.cl;
+    forn(s, S){
+        forn(r,R){
+            deck.emplace_back(r, 1);
+        }
+    }
+}
+
+bool first_merge(){
+    forn(i, deck.sz-1){
+        if(deck[i].st == deck[i+1].st){
+            deck[i].nd += deck[i+1].nd;
+            deck.erase(deck.bn + (i+1));
+            return true;
+        }
+    }
+    return false;
+}
+
+bool drop_end_if_max(){
+    if(deck.sz==0) return false;
+    ll curmax = deck[0].st;
+    fornn(i,1,deck.sz){
+        curmax = max<ll>(curmax, deck[i].st);
+    }
+    if(curmax == deck.bk.st){
+        deck.popb;
+        return true;
+    }
+    return false;
+}
+
+void pack_away(){
+    llog("deck before merging");
+    llog(deck);
+    while(first_merge());
+    llog("deck after merging");
+    llog(deck);
+    llog("deck before dropping");
+    llog(deck);
+    while(drop_end_if_max());
+    llog("deck after dropping");
+    llog(deck);
+    return;
 }
 
 // write to COMM_TYPE result
 void calcFunction() {
+    sstr res;
+    res << ceill(R*(S-1), 2);
+    pack_away();
+    while(deck.sz > 0){
+        res << endl;
+        ll a=0, b=0;
+        ll na=0, nb=0;
+        if(deck.sz == R){
+            ll i = 0;
+            while(deck[i].st != 0){
+                a += deck[i].nd;
+                na++;
+                i++;
+            }
+            fornn(j, i, deck.sz){
+                b += deck[1].nd;
+                nb++;
+            }
+        } else {
+            a = deck[0].nd + deck[1].nd;
+            na = 2;
+            ll i=2;
+            while(deck[i].st != deck[0].st){
+                b += deck[i].nd;
+                nb++;
+                i++;
+            }
+            b += deck[i].nd;
+            nb++;
+        }
+        res << a << " " << b;
+        llog("deck before reordering with na, nb:", na, nb);
+        llog(deck);
+        v(p(ll,ll)) areg(msel(deck, 0, na));
+        deck.erase(msel(deck, 0, na));
+        deck.insert(deck.bn + nb, all(areg));
+        llog("deck after:");
+        llog(deck);
+        pack_away();
+    }
+    result = res.str();
 }
 
 } // namespace task
