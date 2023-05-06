# %%
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

# %%
import time

for i in range(100):
    t1 = time.perf_counter_ns()
    lst = list([1, 2, 3])
    print(i, time.perf_counter_ns() - t1)

# %%

a = [1, 2, 3]
b = a[:2]
print(a)
print(b)
a[0] = 10
print(a)
print(b)

# %%

a = [1, 2, 3]
print(a)
a[:2] = [5, 10, 11]
print(a)
a[:2] = []
print(a)

# %%
