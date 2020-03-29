328c328,331
<     global result
---
>     global result, a, b, c
>     a = cin()
>     b = cin()
>     c = cin()
333a337,340
>     f = lambda x: a * x * x + b * x + c
>     interval = gss(f, -100, 100, tol=1)
>     llog("result interval:", interval)
>     result = "%d %.2f" % (interval[1], f(interval[1]))
