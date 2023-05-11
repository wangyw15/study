import random

def remove_duplicates(lst):
    return list(dict.fromkeys(lst))

lst = [random.randint(0, 10) for i in range(10)]
print("Original list:", lst)
print("List with duplicates removed:", remove_duplicates(lst))

dct = {i: random.randint(0, 10) for i in range(10)}
print("Original dictionary:", dct)
print("Dictionary with duplicates removed:", {v: k for k, v in remove_duplicates(list(dct.items()))})
