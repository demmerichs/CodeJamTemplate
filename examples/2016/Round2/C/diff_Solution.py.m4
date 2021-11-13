diff --git a/CodeJam/Solution.py.m4 b/examples/2016/Round2/C/Solution.py.m4
index afb0931..3bd948b 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2016/Round2/C/Solution.py.m4
@@ -1,9 +1,9 @@
 #!/usr/bin/env python3
 
 FLAGS = set()
-# FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
+FLAGS.add("DEFAULT_VAL_MODE")  # remove comm, to activate default value trigger
 DEFAULT_VAL_TRIGGER = lambda result: result is None  # noqa: E731
-DEFAULT_VAL = "IMPOSSIBLE"
+DEFAULT_VAL = "\nIMPOSSIBLE"
 # FLAGS.add("IA_MODE")  # remove comm, to activate interactive problem mode
 IA_ERROR_CODE = "ERROR"
 
@@ -444,12 +444,59 @@ def init():
 
 
 def readInput():
-    global result
+    global result, R, C, permutation
+    R, C = cin(2)
+    permutation = cin(2 * (R + C))
+
+
+def get_start_position(lover):
+    global R, C
+    # Map from outer cell number to a direction facing into the maze
+    # and the position of the outer cell
+    # 0->downwards, 1->rightwards, 2->upwards, 3->leftwards
+    #  W
+    # S N
+    #  E
+    if lover <= C:
+        return 0, v([-1, lover - 1])
+    lover -= C
+    if lover <= R:
+        return 3, v([lover - 1, C])
+    lover -= R
+    if lover <= C:
+        return 2, v([R, C - lover])
+    lover -= C
+    return 1, v([R - lover, -1])
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, R, C, permutation
+    hedges = {0: "/", 1: "\\", 3: "/"}
+
+    maze = np.zeros((R, C), dtype=np.uint8)
+    size = 2 * (R + C)
+    permutation = list(zip(permutation[::2], permutation[1::2]))
+    permutation.sort(key=lambda ab: min((ab[1] - ab[0]) % size, (ab[0] - ab[1]) % size))
+    for start, end in permutation:
+
+        if (end - start) % size > R + C:
+            start, end = end, start
+
+        direction, pos = get_start_position(start)
+        pos += DIRECTIONS[direction]
+
+        while np.all(pos >= 0) and np.all(pos < v([R, C])):
+            if maze[(*pos,)] == 0:
+                maze[(*pos,)] = (direction & 1) * 2 + 1
+            direction ^= maze[(*pos,)]
+            pos += DIRECTIONS[direction]
+
+        if not np.all(pos == get_start_position(end)[1:]):
+            result = None
+            return
+
+    result = "\n" + "\n".join("".join(hedges[c] for c in row) for row in maze)
 
 
 if __name__ == "__main__":
