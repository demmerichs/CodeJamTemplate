diff --git a/CodeJam/Solution.py.m4 b/examples/2020/KS_A/B/Solution.py.m4
index 3a95eba..6bfbef4 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/KS_A/B/Solution.py.m4
@@ -391,12 +391,26 @@ def init():
 
 
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
