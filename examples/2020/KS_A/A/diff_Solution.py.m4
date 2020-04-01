diff --git a/CodeJam/Solution.py.m4 b/examples/2020/KS_A/A/Solution.py.m4
index 3a95eba..df23fbc 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/KS_A/A/Solution.py.m4
@@ -391,12 +391,20 @@ def init():
 
 
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
