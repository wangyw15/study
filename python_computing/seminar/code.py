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
