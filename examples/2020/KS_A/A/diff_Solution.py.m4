diff --git a/CodeJam/Solution.py.m4 b/examples/2020/KS_A/A/Solution.py.m4
index 10cac5c..75cc9d3 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2020/KS_A/A/Solution.py.m4
@@ -388,12 +388,20 @@ def init():
 
 
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
