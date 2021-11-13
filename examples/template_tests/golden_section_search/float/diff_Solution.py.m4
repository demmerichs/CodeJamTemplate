diff --git a/CodeJam/Solution.py.m4 b/examples/template_tests/golden_section_search/float/Solution.py.m4
index ecd70df..82f3152 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/template_tests/golden_section_search/float/Solution.py.m4
@@ -460,12 +460,35 @@ def init():
 
 
 def readInput():
-    global result
+    global result, t, N, params
+    t = cin()
+    N = cin()
+    params = cin(N)
+
+
+def f(x):
+    if t == "polynom":
+        r = params[0]
+        for p in params[1:]:
+            r *= x
+            r += p
+        return r
+    if t == "linear":
+        assert N % 2 == 0
+        xs, ys = params[: N // 2], params[N // 2 :]
+        assert xs[0] <= x <= xs[-1]
+        for i in range(N // 2 - 1):
+            if xs[i] <= x <= xs[i + 1]:
+                pi = (xs[i + 1] - x) / (xs[i + 1] - xs[i])
+                return pi * ys[i] + (1 - pi) * ys[i + 1]
 
 
 #  write to result
 def calcFunction():
     global result
+    a, fa = gss(f, -100.0, 100.0, tol=1e-2)
+    b, fb = gss(f, -100.0, 100.0, tol=1e-2, upper=True)
+    result = "%.4f %.4f %.4f %.4f" % (a, b, fa, fb)
 
 
 if __name__ == "__main__":
