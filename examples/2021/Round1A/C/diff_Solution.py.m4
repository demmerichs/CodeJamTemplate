diff --git a/CodeJam/Solution.py.m4 b/examples/2021/Round1A/C/Solution.py.m4
index 2766187..e3f4be1 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2021/Round1A/C/Solution.py.m4
@@ -444,12 +444,178 @@ def init():
 
 
 def readInput():
-    global result
+    global result, N, Q, Ai, Si
+    N, Q = cin(2)
+    Ai = []
+    Si = []
+    for _ in range(N):
+        Ai.append(cin())
+        Si.append(int(cin()))
+    lg(Ai)
+    lg(Si)
+
+
+def invert(c):
+    return "TF"[c == "T"]
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, N, Q, Ai, Si
+    result = ["T" * Q, 0]
+    if N == 1:
+        result[0] = Ai[0]
+        result[1] = str(Si[0]) + "/1"
+        if Si[0] * 2 < Q:
+            for q in range(Q):
+                result[0] = result[0][:q] + invert(result[0][q]) + result[0][q + 1 :]
+            result[1] = str(Q - Si[0]) + "/1"
+    elif N == 2:
+        expscore = 0
+        diff = 0
+        for q in range(Q):
+            if Ai[0][q] != Ai[1][q]:
+                diff += 1
+        same = Q - diff
+        score_on_same = (Si[0] + Si[1] - diff) // 2
+        score_on_diff = (Si[0] - Si[1] + diff) // 2
+        lg(diff)
+        lg(score_on_diff)
+        lg(same)
+        lg(score_on_same)
+        if score_on_diff * 2 < diff:
+            result[0] = Ai[1]
+            expscore += diff - score_on_diff
+        else:
+            result[0] = Ai[0]
+            expscore += score_on_diff
+
+        if score_on_same * 2 < same:
+            for q in range(Q):
+                if Ai[0][q] == Ai[1][q]:
+                    result[0] = (
+                        result[0][:q] + invert(result[0][q]) + result[0][q + 1 :]
+                    )
+            expscore += same - score_on_same
+        else:
+            expscore += score_on_same
+        result[1] = str(expscore) + "/1"
+    else:
+        best_prob = Fraction(0, 1)
+        ab = ""
+        ac = ""
+        bc = ""
+        same = ""
+        for q in range(Q):
+            ab += " "
+            ac += " "
+            bc += " "
+            same += " "
+            if Ai[0][q] == Ai[1][q] == Ai[2][q]:
+                same = same[:-1] + Ai[0][q]
+            elif Ai[0][q] == Ai[1][q]:
+                ab = ab[:-1] + Ai[0][q]
+            elif Ai[0][q] == Ai[2][q]:
+                ac = ac[:-1] + Ai[0][q]
+            else:
+                lassert(Ai[1][q] == Ai[2][q], "logic error")
+                bc = bc[:-1] + Ai[1][q]
+        lg(ab)
+        lg(ac)
+        lg(bc)
+        lg(same)
+        AB = sum(s != " " for s in ab)
+        AC = sum(s != " " for s in ac)
+        BC = sum(s != " " for s in bc)
+        SAME = sum(s != " " for s in same)
+        counts = 0
+        exp_counts_AB = 0
+        exp_counts_AC = 0
+        exp_counts_BC = 0
+        exp_counts_SAME = 0
+        for curS in range(SAME + 1):
+            # curAB + curAC + BC - curBC + curS = Si[0]
+            # curAB + curAC - curBC = Si[0] - BC - curS
+            # inv = (np.linalg.inv([[1, 1, -1], [1, -1, 1], [-1, 1, 1]]) * 2).astype(
+            #     np.int32
+            # )
+
+            curAB = (Si[0] + Si[1] - AC - BC) // 2 - curS
+            curAC = (Si[0] + Si[2] - BC - AB) // 2 - curS
+            curBC = (Si[1] + Si[2] - AB - AC) // 2 - curS
+
+            if curAB < 0 or curAB > AB:
+                continue
+            if curAC < 0 or curAC > AC:
+                continue
+            if curBC < 0 or curBC > BC:
+                continue
+
+            cur_counts = (
+                choosell(AB, curAB)
+                * choosell(AC, curAC)
+                * choosell(BC, curBC)
+                * choosell(SAME, curS)
+            )
+            lg(curS)
+            lg(curAB)
+            lg(curAC)
+            lg(curBC)
+            lg(cur_counts)
+            counts += cur_counts
+            exp_counts_AB += cur_counts * curAB
+            exp_counts_AC += cur_counts * curAC
+            exp_counts_BC += cur_counts * curBC
+            exp_counts_SAME += cur_counts * curS
+
+        answer_build = [" " for _ in range(Q)]
+        if exp_counts_AB * 2 >= counts * AB:
+            for q in range(Q):
+                if ab[q] != " ":
+                    answer_build[q] = ab[q]
+        else:
+            exp_counts_AB = counts * AB - exp_counts_AB
+            for q in range(Q):
+                if ab[q] != " ":
+                    answer_build[q] = invert(ab[q])
+        if exp_counts_AC * 2 >= counts * AC:
+            for q in range(Q):
+                if ac[q] != " ":
+                    answer_build[q] = ac[q]
+        else:
+            exp_counts_AC = counts * AC - exp_counts_AC
+            for q in range(Q):
+                if ac[q] != " ":
+                    answer_build[q] = invert(ac[q])
+        if exp_counts_BC * 2 >= counts * BC:
+            for q in range(Q):
+                if bc[q] != " ":
+                    answer_build[q] = bc[q]
+        else:
+            exp_counts_BC = counts * BC - exp_counts_BC
+            for q in range(Q):
+                if bc[q] != " ":
+                    answer_build[q] = invert(bc[q])
+        if exp_counts_SAME * 2 >= counts * SAME:
+            for q in range(Q):
+                if same[q] != " ":
+                    answer_build[q] = same[q]
+        else:
+            exp_counts_SAME = counts * SAME - exp_counts_SAME
+            for q in range(Q):
+                if same[q] != " ":
+                    answer_build[q] = invert(same[q])
+        result[0] = "".join(answer_build)
+        lg(exp_counts_SAME)
+        lg(exp_counts_AB)
+        lg(exp_counts_AC)
+        lg(exp_counts_BC)
+        result[1] = Fraction(
+            exp_counts_SAME + exp_counts_AB + exp_counts_AC + exp_counts_BC, counts,
+        )
+        result[1] = "/".join(map(str, [result[1].numerator, result[1].denominator]))
+
+    result = " ".join(result)
 
 
 if __name__ == "__main__":
