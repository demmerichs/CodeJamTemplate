diff --git a/CodeJam/Solution.py.m4 b/examples/template_tests/golden_section_search/float/Solution.py.m4
index 2766187..15e4c38 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/template_tests/golden_section_search/float/Solution.py.m4
@@ -1,10 +1,10 @@
 #!/usr/bin/env python3
 
 FLAGS = set()
-# FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
+# FLAGS.add("DEFAULT_VAL_MODE")  #remove comm, to activate default value trigger
 DEFAULT_VAL_TRIGGER = lambda result: result is None  # noqa: E731
 DEFAULT_VAL = "IMPOSSIBLE"
-# FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
+# FLAGS.add("IA_MODE")      #remove comm, to activate interactive problem mode
 IA_ERROR_CODE = "ERROR"
 
 # The maintained and empty code template can be found at:
@@ -444,12 +444,19 @@ def init():
 
 
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
