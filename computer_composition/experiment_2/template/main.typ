#import "content.typ": *

#set page(paper: "a4", margin: (x: 3.18cm, y: 2.54cm))
#set text(lang: "zh", fallback: true)
#set heading(numbering: none)

// 标题
#set text(font: "SimHei", weight: "bold")
#align(center, text(size: 18pt)[
  = 上海大学#h(1em) 计算机学院 \ 《计算机组成原理实验》报告#number
])

#set text(size: 15pt)
#grid(columns: (auto, 1fr, auto, 1fr),
  box(width: auto, inset: 2pt, stroke: none)[姓名],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, student_name)),
  box(width: auto, inset: 2pt, stroke: none)[学号],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, student_id))
)
#grid(columns: (auto, 1fr, auto, 1fr, auto, 1fr),
  box(width: auto, inset: 2pt, stroke: none)[时间],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, time)),
  box(width: auto, inset: 2pt, stroke: none)[机位],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, seat)),
  box(width: auto, inset: 2pt, stroke: none)[指导教师],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, teacher)),
)

#line(length: 100%, stroke: 3.5pt)

#set text(font: "SimSun", weight: "regular")
#show heading: h => block(text(size: 14pt)[#h.body])
#show heading.where(level: 3): h => block(text(size: 12pt)[#h.body])
#set text(size: 12pt)

#text(size: 16pt, weight: "bold")[实验名称：#box(width: 50%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, name))]

// #set par(first-line-indent: 2em, justify: true)
#set figure(numbering: none)

= 一、实验目的
#enum(
  ..purpose
)

= 二、实验原理
#par(principle)

= 三、实验内容
#let i = 1
#for item in tasks [
  == #i\. #item.name
  #(i += 1)
  === （1）实验步骤
  #item.steps
  === （2）实验现象
  #item.phenomena
  === （3）数据记录、分析与处理
  #item.data
  === （4）实验结论
  #item.conclusion
]

= 四、建议和体会
#experience
= 五、思考题
#thinking
