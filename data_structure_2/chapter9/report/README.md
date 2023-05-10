# 排序实验报告

# 要求

对八种排序算法进行了测试，包括冒泡排序、插入排序、希尔排序、快速排序、选择排序、堆排序、归并排序和基数排序。每种算法使用四种不同类型的输入数据（已排序，反向排序，部分有序和随机顺序）进行测试，并在 10 100 1000 的数据规模下进行了实验。实验数据包含了数组的大小、比较次数、交换次数和排序时间。

# 运行结果

选取了所有数据中 1000 个数据、随机顺序的运行结果

| algorithm | data scale | data type | duration | comparisons | swaps | valid |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| straight insert sort | 1000 | random | 2193 | 246472 | 245480 | true |
| shell sort | 1000 | random | 181 | 14134 | 6627 | true |
| bubble sort | 1000 | random | 8618 | 497847 | 254830 | true |
| quick sort | 1000 | random | 2647763 | 754363131 | 122998 | true |
| simple selection sort | 1000 | random | 2988 | 499500 | 990 | true |
| heap sort | 1000 | random | 211 | 16818 | 999 | true |
| merge sort | 1000 | random | 853 | 8680 | 1000 | true |
| radix sort | 1000 | random | 59 | 999 | 3000 | true |

# 结论

由于基数排序为无比较排序，所以比较次数仅来自于排序开始时寻找最大值的比较次数；在数组已排序的情况下，冒泡排序的交换次数为 0。

从实验结果可以看出，不同排序算法在不同数据类型和数据规模下表现出不同的性能表现。

基数排序在大多数情况下的性能都比较好，因为基数排序是无比较排序，比较次数最少。

对于有序数据，插入排序和冒泡排序表现较好，因为仅需要比较，对有序数据不需要重新插入。

对于无序数据，希尔排序表现较好。而对于部分有序数据，希尔排序和插入排序有较好的性能表现。

从比较次数和交换次数两个方面来看，不同算法的差异也比较明显。

冒泡排序的比较次数和交换次数都比较多；选择排序的交换和比较次数在同一数据规模下是固定不变的，而快速排序和堆排序在无序数组的情况下交换次数较少。

在实际使用时，需要综合考虑数据规模、数据分布、计算资源等因素来选择适合的排序算法。

快速排序的数据比较特殊，可能是因为对于较大规模的数据需要多层递归，需要不断对栈进行操作，调用函数的开销较大，此外在大规模数据排序时会发生栈溢出，因此大规模数据不适合使用快速排序。

# 附录

> 运行出的原始数据
>
> 测试用代码托管在 [GitHub](https://github.com/wangyw15/study/tree/main/data_structure_2/chapter9)

| algorithm | data scale | data type | duration | comparisons | swaps | valid |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| straight insert sort | 10 | ordered | 3 | 9 | 0 | true |
| straight insert sort | 10 | reversed | 2 | 45 | 45 | true |
| straight insert sort | 10 | random | 3 | 29 | 21 | true |
| straight insert sort | 10 | partially ordered | 2 | 22 | 13 | true |
| straight insert sort | 100 | ordered | 2 | 99 | 0 | true |
| straight insert sort | 100 | reversed | 46 | 4950 | 4950 | true |
| straight insert sort | 100 | random | 28 | 2836 | 2738 | true |
| straight insert sort | 100 | partially ordered | 6 | 515 | 416 | true |
| straight insert sort | 1000 | ordered | 12 | 999 | 0 | true |
| straight insert sort | 1000 | reversed | 5983 | 499500 | 499500 | true |
| straight insert sort | 1000 | random | 2193 | 246472 | 245480 | true |
| straight insert sort | 1000 | partially ordered | 295 | 23814 | 22815 | true |
| shell sort | 10 | ordered | 7 | 22 | 0 | true |
| shell sort | 10 | reversed | 1 | 27 | 13 | true |
| shell sort | 10 | random | 1 | 28 | 9 | true |
| shell sort | 10 | partially ordered | 2 | 28 | 9 | true |
| shell sort | 100 | ordered | 6 | 503 | 0 | true |
| shell sort | 100 | reversed | 11 | 668 | 260 | true |
| shell sort | 100 | random | 11 | 779 | 336 | true |
| shell sort | 100 | partially ordered | 9 | 714 | 222 | true |
| shell sort | 1000 | ordered | 95 | 8006 | 0 | true |
| shell sort | 1000 | reversed | 127 | 11716 | 4700 | true |
| shell sort | 1000 | random | 181 | 14134 | 6627 | true |
| shell sort | 1000 | partially ordered | 143 | 12027 | 4093 | true |
| bubble sort | 10 | ordered | 1 | 9 | 0 | true |
| bubble sort | 10 | reversed | 3 | 45 | 45 | true |
| bubble sort | 10 | random | 2 | 35 | 12 | true |
| bubble sort | 10 | partially ordered | 3 | 44 | 13 | true |
| bubble sort | 100 | ordered | 2 | 99 | 0 | true |
| bubble sort | 100 | reversed | 153 | 4950 | 4950 | true |
| bubble sort | 100 | random | 110 | 4674 | 2391 | true |
| bubble sort | 100 | partially ordered | 39 | 4572 | 416 | true |
| bubble sort | 1000 | ordered | 7 | 999 | 0 | true |
| bubble sort | 1000 | reversed | 13795 | 499500 | 499500 | true |
| bubble sort | 1000 | random | 8618 | 497847 | 254830 | true |
| bubble sort | 1000 | partially ordered | 4248 | 488175 | 22815 | true |
| quick sort | 10 | ordered | 2 | 63 | 0 | true |
| quick sort | 10 | reversed | 1 | 58 | 5 | true |
| quick sort | 10 | random | 2 | 61 | 12 | true |
| quick sort | 10 | partially ordered | 1 | 53 | 1 | true |
| quick sort | 100 | ordered | 30 | 5148 | 0 | true |
| quick sort | 100 | reversed | 18 | 5098 | 50 | true |
| quick sort | 100 | random | 257 | 58820 | 1039 | true |
| quick sort | 100 | partially ordered | 229 | 63305 | 176 | true |
| quick sort | 1000 | ordered | 2028 | 501498 | 0 | true |
| quick sort | 1000 | reversed | 1691 | 500998 | 500 | true |
| quick sort | 1000 | random | 2647763 | 754363131 | 122998 | true |
| quick sort | 1000 | partially ordered | 239082 | 85998768 | 10553 | true |
| simple selection sort | 10 | ordered | 3 | 45 | 0 | true |
| simple selection sort | 10 | reversed | 2 | 45 | 5 | true |
| simple selection sort | 10 | random | 2 | 45 | 8 | true |
| simple selection sort | 10 | partially ordered | 1 | 45 | 1 | true |
| simple selection sort | 100 | ordered | 29 | 4950 | 0 | true |
| simple selection sort | 100 | reversed | 32 | 4950 | 50 | true |
| simple selection sort | 100 | random | 35 | 4950 | 95 | true |
| simple selection sort | 100 | partially ordered | 33 | 4950 | 10 | true |
| simple selection sort | 1000 | ordered | 2855 | 499500 | 0 | true |
| simple selection sort | 1000 | reversed | 2737 | 499500 | 500 | true |
| simple selection sort | 1000 | random | 2988 | 499500 | 990 | true |
| simple selection sort | 1000 | partially ordered | 2934 | 499500 | 87 | true |
| heap sort | 10 | ordered | 8 | 46 | 9 | true |
| heap sort | 10 | reversed | 2 | 38 | 9 | true |
| heap sort | 10 | random | 2 | 38 | 9 | true |
| heap sort | 10 | partially ordered | 2 | 46 | 9 | true |
| heap sort | 100 | ordered | 16 | 1094 | 99 | true |
| heap sort | 100 | reversed | 15 | 956 | 99 | true |
| heap sort | 100 | random | 16 | 1036 | 99 | true |
| heap sort | 100 | partially ordered | 16 | 1086 | 99 | true |
| heap sort | 1000 | ordered | 210 | 17626 | 999 | true |
| heap sort | 1000 | reversed | 230 | 15982 | 999 | true |
| heap sort | 1000 | random | 211 | 16818 | 999 | true |
| heap sort | 1000 | partially ordered | 203 | 17530 | 999 | true |
| merge sort | 10 | ordered | 8 | 19 | 10 | true |
| merge sort | 10 | reversed | 7 | 15 | 10 | true |
| merge sort | 10 | random | 11 | 23 | 10 | true |
| merge sort | 10 | partially ordered | 7 | 25 | 10 | true |
| merge sort | 100 | ordered | 88 | 356 | 100 | true |
| merge sort | 100 | reversed | 76 | 316 | 100 | true |
| merge sort | 100 | random | 77 | 544 | 100 | true |
| merge sort | 100 | partially ordered | 209 | 450 | 100 | true |
| merge sort | 1000 | ordered | 955 | 5044 | 1000 | true |
| merge sort | 1000 | reversed | 793 | 4932 | 1000 | true |
| merge sort | 1000 | random | 853 | 8680 | 1000 | true |
| merge sort | 1000 | partially ordered | 828 | 7620 | 1000 | true |
| radix sort | 10 | ordered | 2 | 9 | 10 | true |
| radix sort | 10 | reversed | 1 | 9 | 10 | true |
| radix sort | 10 | random | 2 | 9 | 10 | true |
| radix sort | 10 | partially ordered | 1 | 9 | 10 | true |
| radix sort | 100 | ordered | 6 | 99 | 200 | true |
| radix sort | 100 | reversed | 5 | 99 | 200 | true |
| radix sort | 100 | random | 5 | 99 | 200 | true |
| radix sort | 100 | partially ordered | 5 | 99 | 200 | true |
| radix sort | 1000 | ordered | 61 | 999 | 3000 | true |
| radix sort | 1000 | reversed | 58 | 999 | 3000 | true |
| radix sort | 1000 | random | 59 | 999 | 3000 | true |
| radix sort | 1000 | partially ordered | 58 | 999 | 3000 | true |
