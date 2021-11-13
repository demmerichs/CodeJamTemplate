diff --git a/CodeJam/Solution.py.m4 b/examples/2020/Round2/B/Solution.py.m4
index afb0931..6477cf5 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/Round2/B/Solution.py.m4
@@ -444,12 +444,59 @@ def init():
 
 
 def readInput():
-    global result
+    global result, C, D, Xi, Di
+    C, D = cin(2)
+    Xi = cin(C - 1)
+    Di = [cin(2) for _ in range(D)]
+    Di = [(x - 1, y - 1) for x, y in Di]
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, C, D, Xi, Di
+    order = [None] * C
+    order[0] = 0
+    ord_t = [None] * C
+    ord_t[0] = 0
+    ord_idx = [None] * C
+    ord_idx[0] = 0
+    times = []
+    for i, xi in enumerate(Xi, 1):
+        if xi > 0:
+            times += [(i, xi)]
+            continue
+        order[i] = -xi
+        for add in range(C + 1):
+            if ord_idx[add - xi] is None:
+                ord_idx[add - xi] = i
+                break
+    times = sorted(times, key=lambda t: t[1])
+    for idx, ti in times:
+        for i in range(C):
+            if ord_idx[i] is None:
+                ord_idx[i] = idx
+                ord_t[i] = ti
+                order[idx] = i
+                break
+    llog("ord_t", ord_t)
+    llog("order", order)
+    llog("ord_idx", ord_idx)
+    for i in range(C):
+        if ord_t[i] is None:
+            lassert(order[ord_idx[i]] is not None, "no info at all???")
+            if order[ord_idx[i - 1]] is not None:
+                if order[ord_idx[i - 1]] == order[ord_idx[i]]:
+                    ord_t[i] = ord_t[i - 1]
+                else:
+                    lassert(order[ord_idx[i - 1]] < order[ord_idx[i]], "wrong order???")
+                    ord_t[i] = ord_t[i - 1] + 1
+            else:
+                ord_t[i] = ord_t[i - 1]
+    llog("ord_t after", ord_t)
+    llog("Di", Di)
+    result = " ".join(
+        map(str, [max(1, abs(ord_t[order[x]] - ord_t[order[y]])) for x, y in Di])
+    )
 
 
 if __name__ == "__main__":
