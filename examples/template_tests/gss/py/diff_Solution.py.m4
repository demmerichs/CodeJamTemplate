diff --git a/CodeJam/Solution.py.m4 b/examples/template_tests/gss/py/Solution.py.m4
index 10cac5c..5ffdeea 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/template_tests/gss/py/Solution.py.m4
@@ -388,12 +388,19 @@ def init():
 
 
 def readInput():
-    global result
+    global result, a, b, c
+    a = cin()
+    b = cin()
+    c = cin()
 
 
 #  write to result
 def calcFunction():
     global result
+    f = lambda x: a * x * x + b * x + c
+    interval = gss(f, -100, 100, tol=1)
+    llog("result interval:", interval)
+    result = "%d %.2f" % (interval[1], f(interval[1]))
 
 
 if __name__ == "__main__":
