# 一、实习目的与要求

1. 熟悉 Python 的开发调试环境
2. 熟悉 Python 外部库的调用
3. 掌握 Python 语言基本语法
4. 熟悉 Python 的数据结构

# 二、实习环境

Python3.11, Visual Studio Code, Jupyter

# 三、实习内容

## 1. Python 代码理解

`polygon.py`

1. 运行和阅读代码；
2. 理解代码功能；
3. 修改代码，练习调用文件中其他几个图形函数。

## 2. 输入输出

编写脚本文件，设计友好的用户输入输出提示，用户输入一个时间（24 小时制，包含时、分、秒），输出 1 秒后的时间。

## 3. 反序对

如果一个单词是另一个单词的反向序列，则称这两个单词为“反向对”。编写代码输出 word.txt 中词汇表包含的反向对。

## 4. 文本分析算法设计

1. 设计 Python 程序读入一个英文单词组成的文本文件，统计该文本文件中各个单词出现的次数。设计测试用例验证代码的正确性。
2. 设计 Python 程序读入一个英文单词组成的文本文件，统计其中包含的某给定关键词列表中各个单词出现的频率。设计测试用例验证代码的正确性.

# 四、实习内容的设计与实现

## 1. Python 代码理解

`turtle.exitonclick()`方法能够避免窗口出现未响应状态

## 2. 输入输出

利用`datetime`类，首先将输入的`str`类型的时间通过`datetime.datetime.strptime`方法转换为`datetime`类型，再将这个时间加上一秒之后转换为`str`输出

通过`datetime`类能够自动实现对于一些时间边界的处理，如59秒、23点等

## 3. 反序对

首先需要读取所有单词，使用自带的`readlines`按行读取文件可能会由于行尾而在每个单词末尾出现`\r`一类的转义字符，可以通过`strip`将这些空白字符去除

在这个程序中，对于存储所有单词的列表，最常用的操作是`in`，于是将单词列表转换为`set`类型（哈希表），这种类型对于`in`这样的查找速度最快，能够提升程序运行效率。

## 4. 文本分析算法设计

### 4.1 统计单词次数

我选择了字典和循环来自行计数，也可以使用`collections.Counter`类来自动计数

### 4.2 统计频率

只要统计所有单词个数，与上一小题的结果结合即可

# 五、测试用例

- [words.txt](words.txt)
- [shakespeare.txt](shakespeare.txt)

# 六、收获与体会

`set`、`list`等不同集合类型对于不同的操作有着不同的效率，按需选择