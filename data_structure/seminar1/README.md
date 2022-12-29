---
marp: true
paginate: true
---

# 第五周研讨课

`RabinKarp`算法与`KMP`算法比较

---

 - RabinKarp参考[此处](https://zhuanlan.zhihu.com/p/563551141)
 - KMP参考[此处](https://www.cnblogs.com/cherryljr/p/6519748.html)

---

程序运行结果
```
  pattern: JKA
   source: AKJKDJKASJDKK
      KMP: 12
RabinKarp: 5

  pattern: hjk
   source: asjdhjkahdjk
      KMP: 11
RabinKarp: 4

  pattern: 023
   source: 10829238740230
      KMP: 23
RabinKarp: 10

  pattern: 021
   source: 10829238740230
      KMP: 23
RabinKarp: 12

  pattern: 6nA
   source: qw378hf6nADIOU45t
      KMP: 17
RabinKarp: 7
```

---

两种算法比较次数的差别在于

 - 尽管KMP算法使用了失效函数避免原串在比较时回退以减少比较次数，但仍然是逐字比较，且模式串会回退
 - 而RabinKarp算法则是使用了滚动哈希函数，直接将模式串与相同长度的原串一部分比较，且原串和模式串都不存在回退比较次数更少

---

# 题外话

原来KMP算法存在一个小问题，使得在测试的时候KMP算法的比较次数永远为`1`，且得不到想要的结果

通过调试发现，问题在于比较时的判断条件`while (i < str.length() && j < pat.length() && pat.length() - j <= str.length() - i)`。

当`j = -1`时问题出现。根据[cppreference](https://en.cppreference.com/w/cpp/string/basic_string/size)，`std::string::length()`返回的类型为`size_t`。

在`MSVC 64bit`编译器中`typeid(size_t).name()`为`unsigned __int64`，并非`int`，而`(int)-1 < (unsigned int)5 == 0`因此无法比较。

将`size_t`强制转换为`long`即可：`while (i < str.length() && j < (long)pat.length() && pat.length() - j <= str.length() - i)`