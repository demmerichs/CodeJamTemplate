diff --git a/CodeJam/Solution.py b/examples/template_tests/gss/py/Solution.py
old mode 100755
new mode 100644
index c61c5b3..fe5fdc1
--- a/CodeJam/Solution.py
+++ b/examples/template_tests/gss/py/Solution.py
@@ -325,12 +325,19 @@ def init():
 
 
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
