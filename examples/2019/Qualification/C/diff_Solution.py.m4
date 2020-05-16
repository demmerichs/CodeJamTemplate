diff --git a/CodeJam/Solution.py.m4 b/examples/2019/Qualification/C/Solution.py.m4
index c0a068a..473426f 100644
--- a/CodeJam/Solution.py.m4
+++ b/examples/2019/Qualification/C/Solution.py.m4
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
@@ -438,12 +438,41 @@ def init():
 
 
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
