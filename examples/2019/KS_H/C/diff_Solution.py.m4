diff --git a/CodeJam/Solution.py.m4 b/examples/2019/KS_H/C/Solution.py.m4
index 3a95eba..e002663 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2019/KS_H/C/Solution.py.m4
@@ -391,12 +391,49 @@ def init():
 
 
 def readInput():
-    global result
+    global result, num_digits
+    num_digits = {}
+    for dig in range(1, 10):
+        val = cin()
+        if val > 0:
+            num_digits[dig] = val
+
+
+def check_all_combos():
+    sorted_digits = sorted(list(num_digits.keys()), key=lambda dig: num_digits[dig])
+    total_digits = sum(num_digits.values())
+    left_half_num = total_digits // 2
+    for vals in it.product(
+        *(list(range(num_digits[d] + 1)) for d in sorted_digits[:-1])
+    ):
+        cur_left_digits = sum(vals)
+        remain = left_half_num - cur_left_digits
+        if remain < 0 or remain > num_digits[sorted_digits[-1]]:
+            continue
+        left_vals = dict(zip(sorted_digits, vals + (remain,)))
+        right_vals = {d: num_digits[d] - left_vals[d] for d in sorted_digits}
+        llog("left vals:", left_vals)
+        llog("right vals:", right_vals)
+        llog("")
+        if (
+            sum(k * v for k, v in left_vals.items())
+            - sum(k * v for k, v in right_vals.items())
+        ) % 11 == 0:
+            return True
+    return False
 
 
 #  write to result
 def calcFunction():
     global result
+    occs = sorted(num_digits.values())
+    if len(occs) >= 2 and occs[-2] >= 10:
+        result = "YES"
+    else:
+        if check_all_combos():
+            result = "YES"
+        else:
+            result = "NO"
 
 
 if __name__ == "__main__":
