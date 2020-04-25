diff --git a/CodeJam/Solution.py.m4 b/examples/2019/Qualification/C/Solution.py.m4
index 10cac5c..b751acb 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2019/Qualification/C/Solution.py.m4
@@ -388,12 +388,41 @@ def init():
 
 
 def readInput():
-    global result
+    global result, N, L, numbers
+    N, L = cin(2)
+    numbers = cin(L)
 
 
 #  write to result
 def calcFunction():
-    global result
+    global result, N, L, numbers
+
+    i = 0
+    while numbers[i] == numbers[i + 1]:
+        i += 1
+    primeip1 = math.gcd(numbers[i], numbers[i + 1])
+
+    primesbeforeip1 = [primeip1]
+    for k in range(i, -1, -1):
+        primesbeforeip1.append(numbers[k] // primesbeforeip1[-1])
+    primesbeforeip1 = primesbeforeip1[1:]
+    primesbeforeip1 = primesbeforeip1[::-1]
+
+    primesafterip1 = [primeip1]
+    for k in range(i + 2, L + 1):
+        primesafterip1.append(numbers[k - 1] // primesafterip1[-1])
+    primesafterip1 = primesafterip1[1:]
+
+    primes = primesbeforeip1 + [primeip1] + primesafterip1
+
+    sorted_primes = sorted(list(set(primes)))
+    assert len(sorted_primes) == 26
+
+    result = ""
+    for prime in primes:
+        result += chr(sorted_primes.index(prime) + ord("A"))
+
+    assert len(set(result)) == 26
 
 
 if __name__ == "__main__":
