diff --git a/CodeJam/Solution.py.m4 b/examples/2022/Qualification/A/Solution.py.m4
index ecd70df..dbff985 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2022/Qualification/A/Solution.py.m4
@@ -460,12 +460,21 @@ def init():
 
 
 def readInput():
-    global result
+    global result, R, C
+    R, C = cin(2)
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, R, C
+    plusstr = "+-" * C + "+"
+    dotstr = "|." * C + "|"
+    result = "\n"
+    result += ".." + plusstr[2:] + "\n"
+    result += ".." + dotstr[2:] + "\n"
+    for _i in range(R - 1):
+        result += plusstr + "\n" + dotstr + "\n"
+    result += plusstr
 
 
 if __name__ == "__main__":
