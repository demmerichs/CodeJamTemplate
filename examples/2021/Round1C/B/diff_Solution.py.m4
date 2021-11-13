diff --git a/CodeJam/Solution.py.m4 b/examples/2021/Round1C/B/Solution.py.m4
index afb0931..6d546b2 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2021/Round1C/B/Solution.py.m4
@@ -444,12 +444,36 @@ def init():
 
 
 def readInput():
-    global result
+    global result, Y
+    Y = str(cin())
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, Y
+    N = len(Y)
+    result = 1e100
+    for n, y in [(N, Y), (N + 1, "0" + Y)]:
+        for k in range(2, n + 1):
+            p2 = n % k
+            a = (n - p2) // k
+            p1 = k - p2
+
+            proposals = []
+            if p2 == 0:
+                n1 = int(y[:a])
+                proposals.append("".join(str(i) for i in range(n1, n1 + k)))
+                proposals.append("".join(str(i) for i in range(n1 + 1, n1 + 1 + k)))
+            else:
+                ncenter = 10 ** a
+                if ncenter > p1:
+                    proposals.append(
+                        "".join(str(i) for i in range(ncenter - p1, ncenter + p2))
+                    )
+            for p in proposals:
+                p = int(p)
+                if p > int(Y) and p < result:
+                    result = p
 
 
 if __name__ == "__main__":
