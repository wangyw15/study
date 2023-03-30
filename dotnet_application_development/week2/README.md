# 第2周实验

## 实验1 单步调试技术

以下为执行`foreach`语句时每一步执行的内容

```csharp
int s in arrInt
Console.WriteLine(s)
```

## 实验2 使用断点调试技术

### 第1部分

步骤4的输出为`北京上海`

步骤5的输出为`0123456789`

在步骤5中，因为`TextBox.Text`属性的类型为`string`类型，`+`代表拼接两个字符串，不会自动把字符串转换为整数类型

如果要得到两数之和，需要将代码改为如下所示

```csharp
textBox3.Text = (int.Parse(textBox1.Text) + int.Parse(textBox2.Text)).ToString();
```

### 第2部分

单击“联接”按钮后命中断点，程序暂停运行，所以`textBox3.Text`的值没有改变

- 自动窗口
  - 显示当前断点周围使用的变量
- 局部变量窗口
  - 显示在当前局部范围内定义的变量，通常是当前函数或方法内
- 监视窗口
  - 显示自己添加的要监视的变量或表达式

### 第3部分

执行步骤2前`textBox3.Text`的值为空，执行后变为`北京广州`

步骤5

- `textBox1.Text`
  - 北京
- `textBox2.Text`
  - 广州
- `textBox3.Text`
  - 京广线：北京到广州

步骤

- `textBox1.Text`
  - 保持`北京`不变
- `textBox2.Text`
  - 保持`广州`不变
- `textBox3.Text`
  - 从空字符串变为`北京广州`

## 实验3 使用“堆栈调用”窗口