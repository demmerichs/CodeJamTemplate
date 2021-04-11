diff --git a/CodeJam/Solution.py.m4 b/examples/2020/Round3/A/Solution.py.m4
index e5aa38d..b80db18 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/Round3/A/Solution.py.m4
@@ -444,12 +444,56 @@ def init():
 
 
 def readInput():
-    global result
+    global result, C, J
+    C = cin()
+    J = cin()
 
 
 #  write to result
 def calcFunction():
     global result
+    result = C
+    lsm = np.zeros((len(C) + 1, len(J) + 1), dtype=np.int32)
+    lsm[0, :] = np.arange(len(J) + 1)
+    lsm[:, 0] = np.arange(len(C) + 1)
+    for i in range(1, len(C) + 1):
+        for j in range(1, len(J) + 1):
+            if C[i - 1] == J[j - 1]:
+                sub_cost = 0
+            else:
+                sub_cost = 1
+
+            lsm[i, j] = min(
+                lsm[i - 1, j] + 1, lsm[i, j - 1] + 1, lsm[i - 1, j - 1] + sub_cost
+            )
+
+    result = ""
+    p = (len(C), len(J))
+    c = 0
+    llog(lsm)
+    while c < lsm[len(C), len(J)] // 2:
+        if lsm[p] == lsm[p[0] - 1, p[1]] + 1:
+            # result=C[]
+            result = C[p[0] - 1] + result
+            p = (p[0] - 1, p[1])
+            c += 1
+            llog("deleting from C position", p[0])
+        elif lsm[p] == lsm[p[0], p[1] - 1] + 1:
+            p = (p[0], p[1] - 1)
+            c += 1
+            llog("deleting from J position", p[1])
+        else:
+            result = C[p[0] - 1] + result
+            p = (p[0] - 1, p[1] - 1)
+            if C[p[0]] == J[p[1]]:
+                pass
+            else:
+                llog("changing from J position", p[1])
+                c += 1
+        llog("result is now:", result)
+        llog("next pos", p)
+    llog("final pos", p)
+    result = J[: p[1]] + result
 
 
 if __name__ == "__main__":
