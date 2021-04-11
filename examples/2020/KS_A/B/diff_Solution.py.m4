diff --git a/CodeJam/Solution.py.m4 b/examples/2020/KS_A/B/Solution.py.m4
index 2766187..842291d 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/KS_A/B/Solution.py.m4
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
@@ -444,12 +444,26 @@ def init():
 
 
 def readInput():
-    global result
+    global result, N, K, P, bnk
+    N, K, P = cin(3)
+    bnk = []
+    for _ in range(N):
+        bnk.append([0] + np.cumsum(cin(K)).tolist())
+        bnk[-1] += [bnk[-1][-1]] * (P - K)
+    bnk = v(bnk)
+    llog(bnk)
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, N, K, P, bnk
+    dp = np.zeros((N + 1, P + 1), dtype=np.int64)
+    for n in range(1, N + 1):
+        for p in range(P + 1):
+            dp[n, p] = np.max(dp[n - 1, : p + 1] + bnk[n - 1, : p + 1][::-1])
+    llog(dp)
+
+    result = dp[N, P]
 
 
 if __name__ == "__main__":
