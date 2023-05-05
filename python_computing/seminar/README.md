---
marp: true
math: mathjax
---

# Python序列实现的底层原理

> 以`list`为例
> 版本：[CPython 3.12.0 alpha 7](https://github.com/python/cpython)
> `Include/internal/pycore_list.h`

---

# Python部分

> 不那么底层的逻辑

---

# `list`

> 长度会自动扩展的顺序表

`list`继承于`MutableSequence`，而`MutableSequence`继承于`Sequence`，再往上的父类就与序列没有特别的关系了

---

# `Sequence`

> `Sequence`就是数组，只不过内容不可变

`Sequence`是只读的序列，继承于
- `Reversible`
  - 可反向的
- `Collection`
  - 是个集合
- ...
  - 其实`Collection`还有三个基类，篇幅所限就不赘述了

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

很简单，就是通过`del`删除数组的元素

---

# `MutableSequence.clear()`

> `Lib/_collections_abc.py`

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

# C语言部分

> 底层逻辑

---

# `list` 主要函数

> `Objects/listobject.h`

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

先获取直接可用的空余列表个数，如果有就直接新建列表；否则就通过GC新建列表。

新建列表之后，如果需要的`size`不为0，就通过`PyMem_Calloc`申请空间，然后通过GC跟踪，以便垃圾回收。

---

# 列表长度

> `PyList_Size`

转换为`PyVarObject`再获取长度。

---

# 获取指定下标的内容

> `PyList_GetItem`

与顺序表相同，通过数组下标访问

---

# `list_resize`

> `Objects/listobject.c`

```c
if (allocated >= newsize && newsize >= (allocated >> 1)) {
    assert(self->ob_item != NULL || newsize == 0);
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

但是并不是总会多申请空间的，需要的空间增量比多申请的空间余量还要多的时候就会这样。

```c
if (newsize - Py_SIZE(self) > (Py_ssize_t)(new_allocated - newsize))
    new_allocated = ((size_t)newsize + 3) & ~(size_t)3;
```

---

# 谢谢
