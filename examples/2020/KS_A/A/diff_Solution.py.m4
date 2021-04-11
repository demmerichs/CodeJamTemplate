diff --git a/CodeJam/Solution.py.m4 b/examples/2020/KS_A/A/Solution.py.m4
index e5aa38d..00e03f3 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/KS_A/A/Solution.py.m4
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
@@ -444,12 +444,20 @@ def init():
 
 
 def readInput():
-    global result
+    global result, N, B, Ai
+    N = cin()
+    B = cin()
+    Ai = cin(N)
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, N, B, Ai
+    Ai = v(Ai)
+    Ai = np.sort(Ai)
+    llog(Ai)
+    llog(len(Ai))
+    result = np.sum(np.cumsum(Ai) <= B)
 
 
 if __name__ == "__main__":
