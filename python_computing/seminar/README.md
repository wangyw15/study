---
# marp
title: Python 序列实现的底层原理
marp: true
paginate: true
theme: default
description: '从官方文档看到 Cpython 底层代码'
footer: '[跳到结尾](#结尾)'
# marp end

subtitle: ''
date: 2023-05-07T15:11:13+08:00
lastmod: 2023-05-07T15:11:13+08:00
draft: false
authors: ['wangyw15']

tags: ['编程', '学习']
categories: []
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: ''
featuredImagePreview: ''

toc:
  enable: true
math:
  enable: true
lightgallery: true
license: ''
slug: '403c7a43'
---

# Python 序列实现的底层原理

> 版本：[CPython 3.11.3](https://github.com/python/cpython/tree/v3.11.3)

<!--more-->

---

# 序列

> Python
> 文件 `Lib/_collections_abc.py`

---

# `Sequence`

`Sequence`是只读的序列，继承于
- `Reversible`
  - 可反向的
- `Collection`
  - 是个集合
- ...
  - 其实`Collection`还有三个基类，篇幅所限就不赘述了

---

# `MutableSequence`

> 就是顺序表

可变序列，着重介绍

---

# `MutableSequence.remove()`

```python
def remove(self, value):
    del self[self.index(value)]
```

先通过`list.index`通过`del`删除元素

---

# `MutableSequence.pop()`

```python
def pop(self, index=-1):
    v = self[index]
    del self[index]
    return v
```

很简单，就是先把值保留下来，然后通过`del`删除数组的元素，最后返回这个元素值

---

# `MutableSequence.clear()`

```python
def clear(self):
    try:
        while True:
            self.pop()
    except IndexError:
        pass
```

清空数组就是`pop()`到报错为止

---

# `Sequence` 底层实现

> 文件 `Include/abstract.h`
> 文件 `Objects/abstract.c`

---

# `Sequence` 主要函数

```c
PyAPI_FUNC(Py_ssize_t) PySequence_Size(PyObject *o);

#undef PySequence_Length
PyAPI_FUNC(Py_ssize_t) PySequence_Length(PyObject *o);
#define PySequence_Length PySequence_Size
PyAPI_FUNC(PyObject *) PySequence_Concat(PyObject *o1, PyObject *o2);
PyAPI_FUNC(PyObject *) PySequence_Repeat(PyObject *o, Py_ssize_t count);
PyAPI_FUNC(PyObject *) PySequence_GetItem(PyObject *o, Py_ssize_t i);
PyAPI_FUNC(PyObject *) PySequence_GetSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2);
PyAPI_FUNC(int) PySequence_SetItem(PyObject *o, Py_ssize_t i, PyObject *v);
PyAPI_FUNC(int) PySequence_DelItem(PyObject *o, Py_ssize_t i);
PyAPI_FUNC(int) PySequence_SetSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2, PyObject *v);
PyAPI_FUNC(int) PySequence_DelSlice(PyObject *o, Py_ssize_t i1, Py_ssize_t i2);
PyAPI_FUNC(PyObject *) PySequence_Tuple(PyObject *o);
PyAPI_FUNC(PyObject *) PySequence_List(PyObject *o);
```

---

```c
typedef struct {
    lenfunc sq_length;
    binaryfunc sq_concat;
    ssizeargfunc sq_repeat;
    ssizeargfunc sq_item;
    void *was_sq_slice;
    ssizeobjargproc sq_ass_item;
    void *was_sq_ass_slice;
    objobjproc sq_contains;

    binaryfunc sq_inplace_concat;
    ssizeargfunc sq_inplace_repeat;
} PySequenceMethods;
```

根据我的观察，`Sequence` 更接近于接口，具体实现要看子类

---

# `list`

> 文件 `Include/listobject.h`
> 文件 `Objects/listobject.c`
> 文件 `Include/internal/pycore_list.h`
> 后面展示的代码都是简化过的

`list` 同样是Python的内置类型，在 `Python/bltinmodule.c` 中定义，并且在[官方文档](https://docs.python.org/3/library/stdtypes.html)描述中，`list` 就是可变序列。

---

# Python内置模块

> 文件 `Python/bltinmodule.c`

|    内置模块    |             |          |              |           |              |
| :------------: | :---------: | :------: | :----------: | :-------: | :----------: |
|      None      | classmethod | **list** | **Ellipsis** |  complex  |     map      |
| NotImplemented |    dict     |  object  |    False     | enumerate |    range     |
|      True      |   filter    | reversed |     bool     |   float   |     set      |
|   memoryview   |  frozenset  |  slice   |  bytearray   | property  | staticmethod |
|     bytes      |     int     |   str    |    super     |   tuple   |     type     |
|      zip       |             |          |              |           |              |

---

# `list.extend()` 实现

> 后面要用到就提前说了

```c
static PyObject *list_extend(PyListObject *self, PyObject *iterable)
{
    PyObject *it;      /* iter(v) */
    Py_ssize_t m;      /* size of self */
    Py_ssize_t n;      /* guess for size of iterable */
    // ...
    /* Guess a result list size. */
    n = PyObject_LengthHint(iterable, 8);
    m = Py_SIZE(self);
    if (m > PY_SSIZE_T_MAX - n) {
        /* m + n overflowed; on the chance that n lied, and there really
         * is enough room, ignore it.  If n was telling the truth, we'll
         * eventually run out of memory during the loop.
         */
    }
```

会先“猜测”额外需要多少空间，在后面申请这些空间

---

```c
    else if (self->ob_item == NULL) {
        if (n && list_preallocate_exact(self, n) < 0)
            goto error;
    }
    else {
        if (list_resize(self, m + n) < 0)
            goto error;
        // ...
    }
    // ...
    if (Py_SIZE(self) < self->allocated) {
        if (list_resize(self, Py_SIZE(self)) < 0)
            goto error;
    }
    // ...
}
```

如果本身没有东西，那就照着要添加的序列长度来申请空间，否则就根据 `list_resize()` 中的算法来申请空间，这个方法在之后会提到

完成之后把多申请的空间削减一点

---

# `list` 主要函数

```c
PyAPI_FUNC(PyObject *) PyList_New(Py_ssize_t size);
PyAPI_FUNC(Py_ssize_t) PyList_Size(PyObject *);

PyAPI_FUNC(PyObject *) PyList_GetItem(PyObject *, Py_ssize_t);
PyAPI_FUNC(int) PyList_SetItem(PyObject *, Py_ssize_t, PyObject *);
PyAPI_FUNC(int) PyList_Insert(PyObject *, Py_ssize_t, PyObject *);
PyAPI_FUNC(int) PyList_Append(PyObject *, PyObject *);

PyAPI_FUNC(PyObject *) PyList_GetSlice(PyObject *, Py_ssize_t, Py_ssize_t);
PyAPI_FUNC(int) PyList_SetSlice(PyObject *, Py_ssize_t, Py_ssize_t, PyObject *);

PyAPI_FUNC(int) PyList_Sort(PyObject *);
PyAPI_FUNC(int) PyList_Reverse(PyObject *);
PyAPI_FUNC(PyObject *) PyList_AsTuple(PyObject *);
```

---

# 新建列表

> `PyList_New`

```c
#define PyList_MAXFREELIST 80
if (PyList_MAXFREELIST && state->numfree) {
    state->numfree--;
    op = state->free_list[state->numfree];
    OBJECT_STAT_INC(from_freelist);
    _Py_NewReference((PyObject *)op);
}
else {
    op = PyObject_GC_New(PyListObject, &PyList_Type);
    if (op == NULL) {
        return NULL;
    }
}
```

Python 是有缓存的，所以会先检查 `list` 的缓存，如果还有空就直接拿来用，否则就新建一个。但是实际存储数据的内存空间没有缓存，还是需要分配的

---

```c
if (size <= 0) {
    op->ob_item = NULL;
}
else {
    op->ob_item = (PyObject **) PyMem_Calloc(size, sizeof(PyObject *));
    if (op->ob_item == NULL) {
        Py_DECREF(op);
        return PyErr_NoMemory();
    }
}
```

然后开始根据 `size` 分配空间，如果为0就跳过分配空间

`PyListObject` 这个结构体本身是存储在栈上的，有缓存；而实际存储数据的 `ob_item` 是通过 `calloc` 分配的堆空间，没有缓存

`calloc` 可以参考[微软官方文档](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/calloc)

---

# 列表长度

```c
Py_ssize_t PyList_Size(PyObject *op)
{
    return Py_SIZE(op);
}
// Py_SIZE
#define Py_SIZE(ob) Py_SIZE(_PyObject_CAST(ob))

static inline Py_ssize_t Py_SIZE(PyObject *ob) {
    // ..
    PyVarObject *var_ob = _PyVarObject_CAST(ob);
    return var_ob->ob_size;
}
```

转换为`PyVarObject`再获取长度。

---

# 获取指定下标的内容

```c
PyObject *PyList_GetItem(PyObject *op, Py_ssize_t i)
{
    return ((PyListObject *)op) -> ob_item[i];
}
```

与顺序表相同，通过数组下标访问

---

# 设置指定下标的内容

```c
int PyList_SetItem(PyObject *op, Py_ssize_t i, PyObject *newitem)
{
    PyObject **p;
    p = ((PyListObject *)op) -> ob_item + i;
    Py_XSETREF(*p, newitem); // copy
    return 0;
}
```

与顺序表相同，将数据浅拷贝至目标内存

---

# 插入

```c
int PyList_Insert(PyObject *op, Py_ssize_t where, PyObject *newitem)
{
    return ins1((PyListObject *)op, where, newitem);
}

static int ins1(PyListObject *self, Py_ssize_t where, PyObject *v)
{
    // ...
    if (list_resize(self, n+1) < 0) //important
        return -1;
    // ...
    return 0;
}
```

因为是顺序表，所以每次插入时要通过 `list_resize` 来扩容，然后就是普通的顺序表插入。

`list_resize` 会在后面讲到

---

# 在尾部追加

```c
int PyList_Append(PyObject *op, PyObject *newitem)
{
    return _PyList_AppendTakeRef((PyListObject *)op, Py_NewRef(newitem));
}
```

`_PyList_AppendTakeRef` 在下一页

---

```c
static inline int _PyList_AppendTakeRef(PyListObject *self, PyObject *newitem)
{
    Py_ssize_t len = PyList_GET_SIZE(self);
    Py_ssize_t allocated = self->allocated;
    if (allocated > len) {
        PyList_SET_ITEM(self, len, newitem);
        Py_SET_SIZE(self, len + 1);
        return 0;
    }
    return _PyList_AppendTakeRefListResize(self, newitem);
}
```

虽然这里没有用到 `list_resize`，但是也要提到一下：在申请新内存空间的时候会有意多申请一部分空间，避免多次申请降低效率

---

```c
int _PyList_AppendTakeRefListResize(PyListObject *self, PyObject *newitem)
{
    Py_ssize_t len = PyList_GET_SIZE(self);
    if (list_resize(self, len + 1) < 0) {
        Py_DECREF(newitem);
        return -1;
    }
    PyList_SET_ITEM(self, len, newitem);
    return 0;
}
```

这里与之前的 `PyList_Insert` 一样，要重新分配内存空间大小，然后在尾部添加新数据

---

# 获取切片

```c
PyObject *PyList_GetSlice(PyObject *a, Py_ssize_t ilow, Py_ssize_t ihigh)
{
    // ...
    return list_slice((PyListObject *)a, ilow, ihigh);
}
static PyObject *list_slice(PyListObject *a, Py_ssize_t ilow, Py_ssize_t ihigh)
{
    PyListObject *np;
    // ...
    np = (PyListObject *) list_new_prealloc(len);
    // ...
    for (i = 0; i < len; i++) {
        PyObject *v = src[i];
        Py_INCREF(v);
        dest[i] = v;
    }
    // ...
    return (PyObject *)np;
}
```

---

切片作为右值的时候返回的是浅拷贝，如

```python
a = [1, 2, 3]
b = a[:2]
print(a)
print(b)
a[0] = 10
print(a)
print(b)
```

运行结果是

```
[1, 2, 3]
[1, 2]
[10, 2, 3]
[1, 2]
```

与此相对的就是左值了，后文的设置切片

---

# 设置切片

> 复杂一点了

```python
a = [1, 2, 3]
print(a)
a[:2] = [5, 10, 11]
print(a)
a[:2] = []
print(a)
```

运行结果是

```
[1, 2, 3]
[5, 10, 11, 3]
[11, 3]
```

当切片作为左值的时候，在底层与右值处理方式不一样

---

```c
int PyList_SetSlice(PyObject *a, Py_ssize_t ilow, Py_ssize_t ihigh, PyObject *v) {
    // ...
    return list_ass_slice((PyListObject *)a, ilow, ihigh, v);
}
static int list_ass_slice(PyListObject *a, Py_ssize_t ilow, Py_ssize_t ihigh, PyObject *v) {
    Py_ssize_t n; /* # of elements in replacement list */
    Py_ssize_t norig; /* # of elements in list getting replaced */
    Py_ssize_t d; /* Change in size */
    // ...
    if (d < 0) { /* Delete -d items */
        Py_ssize_t tail;
        tail = (Py_SIZE(a) - ihigh) * sizeof(PyObject *);
        memmove(&item[ihigh+d], &item[ihigh], tail);
        if (list_resize(a, Py_SIZE(a) + d) < 0) {
            memmove(&item[ihigh], &item[ihigh+d], tail);
            memcpy(&item[ilow], recycle, s);
            goto Error;
        }
        item = a->ob_item;
    }
```

`list.remove()` 和 `list.pop()` 就是通过这个函数来实现的

---

```c
    else if (d > 0) { /* Insert d items */
        k = Py_SIZE(a);
        if (list_resize(a, k+d) < 0)
            goto Error;
        item = a->ob_item;
        memmove(&item[ihigh+d], &item[ihigh],
            (k - ihigh)*sizeof(PyObject *));
    }
    for (k = 0; k < n; k++, ilow++) {
        PyObject *w = vitem[k];
        Py_XINCREF(w);
        item[ilow] = w;
    }
    result = 0;
    // ...
    return result;
}
```

新赋值比切片长度长，就先把列表变短再赋值；更短则反之

---

# 排序

> 代码太长放不下

```c
int PyList_Sort(PyObject *v)
{
    // ...
    v = list_sort_impl((PyListObject *)v, NULL, 0);
    // ...
    return 0;
}
static PyObject *list_sort_impl(PyListObject *self, PyObject *keyfunc, int reverse)
{
    // ...
}
```

使用了 timsort 算法，也就是归并排序加上二叉排序，先进行归并排序，对于短序列则使用二叉排序（最大堆或最小堆）

具体参考 `Objects/listsort.txt` 文件

---

短序列的长度是通过 `list` 的长度计算得出的

```c
static Py_ssize_t merge_compute_minrun(Py_ssize_t n)
{
    Py_ssize_t r = 0;           /* becomes 1 if any 1 bits are shifted off */
    assert(n >= 0);
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}
```

以 `n=67` 为例，转换为二进制为 `100 0011`，`r` 此时变为 1，`n` 右移一位变为 `10 0001=33`，循环停止，最终返回 34。因此，当剩余序列长度小于 34 时变为二叉排序。

---

# 反序

```c
int PyList_Reverse(PyObject *v)
{
    // ...
    reverse_slice(self->ob_item, self->ob_item + Py_SIZE(self));
    return 0;
}
static void reverse_slice(PyObject **lo, PyObject **hi)
{
    --hi;
    while (lo < hi) {
        PyObject *t = *lo;
        *lo = *hi;
        *hi = t;
        ++lo;
        --hi;
    }
}
```

反序很简单，就是一直交换首尾直到中间为止

---

# `list_resize`

> 比较有意思的

```c
if (allocated >= newsize && newsize >= (allocated >> 1)) {
    Py_SET_SIZE(self, newsize);
    return 0;
}
```

```c
allocated >= newsize && newsize >= (allocated >> 1)
```
可以看作
```c
allocated >= newsize && newsize >= allocated / 2
```

在重新申请空间之前，会先检查已申请的空间 `allocated`，如果 $2\times\text{newsize}>\text{allocated}>\text{newsize}$，就跳过重新申请空间的步骤。

---

```c
new_allocated = ((size_t)newsize + (newsize >> 3) + 6) & ~(size_t)3;
```
这是计算新空间大小的代码，简化后的代码如下
```c
new_allocated = (newsize + (newsize >> 3) + 6) & ~3;
```
可以得到如下数学公式（$x$ 代表 `newsize`，$y$ 代表 `new_allocated`）
$$
y = \lfloor \cfrac{x + \lfloor \cfrac{x}{8} \rfloor + 6}{4}\rfloor \times 4
$$

---

以 $25$ 为例，通过公式可以计算出新空间大小

$$
\begin{aligned}
y &= \lfloor \cfrac{25 + \lfloor \cfrac{25}{8} \rfloor + 6}{4}\rfloor \times 4 \\
&= \lfloor \cfrac{25 + 3 + 6}{4} \rfloor \times 4 \\
&= \lfloor \cfrac{34}{4} \rfloor \times 4 \\
&= 8 \times 4 = 32 \\
\end{aligned}
$$

通过公式，可以计算出新空间大小的序列
$$
0, 4, 8, 16, 24, 32, 40, 52, 64, 76, \cdots
$$

---

通过这样按比例申请比实际需要更多的空间（over-allocate），可以为之后的增长预留空间，可以让一个长列表扩展的时间复杂度接近线性，因为系统的`realloc`性能很差。

`new_allocated` 不会发生上溢，因为最大的值是 `PY_SSIZE_T_MAX * (9 / 8) + 6`，永远比 `size_t` 的最大值小。

注：`PY_SSIZE_T_MAX` 在 `PC/pyconfig.h` 中定义，在64位架构是`int32` 的最大值，为 $2^{31}-1=2147483647$

---

但是并不是总会按公式申请空间的，需要的空间增量比多申请的空间余量还要多的时候就会这样。

```c
if (newsize - Py_SIZE(self) > (Py_ssize_t)(new_allocated - newsize))
    new_allocated = ((size_t)newsize + 3) & ~(size_t)3;
```

---

# `list.append()` 和列表推导式

> 在速度上一较高下

`list.append()` 一般来说会慢一点

列表推导式就会快一点，那么快在哪里？使用 `dis` 库来看看两者区别

---

# `dis` 库

> Disassembler of Python byte code into mnemonics.
> 反汇编！
> 操作码列表请看[官方文档](https://docs.python.org/zh-cn/3/library/dis.html#opcode-collections)

可以把编译之后的 Python 字节码转换为助记符

---

# 怎么比

```python
import dis

def use_append():
    lst = []
    for i in range(10):
        lst.append(i)

def use_list_comprehension():
    lst = [i for i in range(10)]

dis.dis(use_append)
print('-------------------')
dis.dis(use_list_comprehension)
```

两个函数都是生成 0-9 的列表，区别是上面一个用 `list.append()`，下面一个用列表推导式，用 `dis` 来分析一下

---

# `use_append`

```
  6          40 LOAD_FAST                0 (lst)
             42 LOAD_METHOD              1 (append)
             64 LOAD_FAST                1 (i)
             66 PRECALL                  1
             70 CALL                     1
             80 POP_TOP
             82 JUMP_BACKWARD           24 (to 36)

```

---

# `use_list_comprehension`

```
  9           0 RESUME                   0
              2 BUILD_LIST               0
              4 LOAD_FAST                0 (.0)
        >>    6 FOR_ITER                 4 (to 16)
              8 STORE_FAST               1 (i)
             10 LOAD_FAST                1 (i)
             12 LIST_APPEND              2
             14 JUMP_BACKWARD            5 (to 6)
        >>   16 RETURN_VALUE
```

---

# 差别

使用 `list.append` 会多一步调用这个函数的步骤，堆栈操作有一定开销，而列表推导式直接调用更为底层的 `LIST_APPEND` 相比之下会快一点

`LIST_APPEND` 是专门用于实现列表推导式的操作码

---

# 结尾

> https://github.com/wangyw15/study/tree/main/python_computing/seminar
> 上面是包括这个文档的 GitHub 链接
> 二维码是这个文档的 Markdown 版本

![bg w:500 left:45%](data:image/png;base64,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)

---

# 接下来是意外收获

---

# `Ellipsis` ( `...` )

> 对没错，就是三个点

打开 Python 输入 `...`，解释器就会告诉你这个是 `Ellipsis`

```
>>> type(...)
<class 'ellipsis'>
```

---

# `Ellipsis` 的源码

> 文件 `Include/sliceobject.h`

```c
/* The unique ellipsis object "..." */

PyAPI_DATA(PyObject) _Py_EllipsisObject; /* Don't use this directly */

#define Py_Ellipsis (&_Py_EllipsisObject)
```

对，只有这些，什么都没有用的类，但是在 numpy 中作为语法糖出现了
