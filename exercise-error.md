---
title: exercise-error
cover: 
summary:
author: 王鸿奇
author_gh_user: Homqyy
email: yilupiaoxuewhq@163.com
date: 2023-06-24 12:41
status: draft
read_time: {{reading_time}}
comments: true
tags:
    - ComputerSystems
---

## 5

TODO: 延迟表

### 5.5

```c
double
poly(double a[], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr = x;

    for (i = 1; i <= degree; i++)
    {
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }

    return result;
}
```

**问题**：CPE的二级果是5，为什么呢？

> 我们可以看到，这里限制性能的计算是反复地计算表达式`xpwr=x*xpwr`。这需要一个浮点数乘法（5C），并且直到前一次迭代完成，下一次迭代的计算才能开始。两次连续的迭代之间，对result的更新只需要一个浮点加法（3C）

**疑问**：我理解这里的性能限制应该是`reulst += a[i] * xpwr`，因为它看起来执行时间更久

- `xpwr = x * xpwr`的结果会成为下个迭代开始的必要条件，因此如果此运算不完成，下次迭代就没法开展。因此它是性能瓶颈
- 虽然`result += a[i] * xpwr`看起来顺序操作时间似乎比`xpwr = x * xpwr`长，但是由于现在处理器可以并行处理，而它又不阻碍其他指令的开始，因此它不会成为瓶颈，在实际中，处理器会高效的执行它。
- **关键路径** 决定性能瓶颈

### 5.6

**问题**：在我们的参考机上测量这个函数的CPE等于8.00。解释为什么？

> 我们可以看到，这里的性能限制计算是反复地计算表达式`result = a[i] + x * result`。从来自上一次迭代的result的值开始，我们必须先把它乘以`x`（5C），然后把它加上`a[i]`（3C），然后得到本次迭代的值。因此，每次迭代造成了最小延迟时间为8个周期。

**疑问**：参阅5.5的疑问，可以解答此题。
