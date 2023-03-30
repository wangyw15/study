# UML

```mermaid
classDiagram

class 职工

class 干部

class 工人 {
    工种
    学历
    技能级别
}

class 经理 {
    +收件()
    +指派快递员()
    +结算()
}

class 快递员 {
    +驾驶证
    +驾驶()
    +递送()
    +取回执()
}

class 邮件 {
    +申请人
    +邮件编号
    +收件人
    +收件地址
    +时间
    +申请登记()
    +收件验收()
}

class 公司

class 收件人

class 回执

工人 --|> 职工
干部 --|> 职工
经理 --|> 干部
快递员 --|> 工人

经理 --o 公司
快递员 --o 公司

经理 --> 快递员 : 指派
经理 --> 邮件 : 登记
经理 --> 邮件 : 接受

快递员 --> 邮件 : 派送
收件人 --> 邮件 : 接收
快递员 --> 回执 : 取得
经理 --> 回执 : 结算
```

---

# 思考题

- SDK
  - 全称 Software Development Kit
  - 流行 Java, Golang, NodeJS 等
- IDE
  - 全称 Integrated Development Environment
  - 流行 Visual Studio, JetBrains IntelliJ IDEA, Android Studio 等
SDK更偏向于底层，用于辅助某一类软件；IDE是用于程序开发环境的应用程序，包括了代码编辑器、编译器、调试器、图形界面等工具。

---

- CLS
  - 全称 Common Language Specification
  - 公共语言规范
- CLR
  - 全称 Common Language Runtime
  - 公共语言运行库
- 核心是CLR
- 是，因为CLS规定了语言需要支持的特性，以便于同其他语言的互操作性

---

- Framework 是一套工具，支持之上的语言编译与运行等；Programming Language 是代码，需要框架来编译和运行
  - 主要框架 NodeJS Java 等

---

- 最熟悉
  - 语言 C#, Python, JavaScript
  - IDE  Visual Studio, IntelliJ IDEA

---

- 目的：学到dotnet更为底层的原理
