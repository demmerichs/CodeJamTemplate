diff --git a/CodeJam/Solution.py.m4 b/examples/2019/Round1A/B_interactive/Solution.py.m4
index 2766187..23a8147 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2019/Round1A/B_interactive/Solution.py.m4
@@ -1,11 +1,11 @@
 #!/usr/bin/env python3
 
 FLAGS = set()
-# FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
+# FLAGS.add("DEFAULT_VAL_MODE")  #remove comm, to activate default value trigger
 DEFAULT_VAL_TRIGGER = lambda result: result is None  # noqa: E731
 DEFAULT_VAL = "IMPOSSIBLE"
-# FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
-IA_ERROR_CODE = "ERROR"
+FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
+IA_ERROR_CODE = -1
 
 # The maintained and empty code template can be found at:
 # https://github.com/demmerichs/CodeJamTemplate
@@ -440,16 +440,34 @@ def main():
 
 
 def init():
-    global result
+    global result, N, m
+    N = get_in()
+    m = get_in()
 
 
 def readInput():
     global result
 
 
+def ask(p):
+    ps = [p] * 18
+    out(" ".join(map(str, ps)))
+    sum = 0
+    for i in range(18):
+        sum += get_in()
+    return sum % p
+
+
 #  write to result
 def calcFunction():
-    global result
+    global result, N, m
+    lassert(N >= 7, "N was smaller than 7")
+    p = [17, 16, 13, 11, 9, 7, 5]
+    ans = []
+    for i in range(7):
+        ans.append(ask(p[i]))
+    out(crt(ans, p))
+    get_in()
 
 
 if __name__ == "__main__":
