#import "content/content.typ": *

#set page(paper: "a4", margin: (x: 3.18cm, y: 2.54cm))
#set heading(numbering: "一、")

#set text(font: "SimHei", weight: "bold")

#align(center, text(size: 18pt)[
  #heading(numbering: none)[上海大学 计算机学院 \ 《计算机组成原理实验》报告#number]
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
#show heading: h => block[
  #if h.level == 3 [
    #text(size: 12pt)[#counter(heading).display()#h.body]
  ] else [
    #text(size: 14pt)[#counter(heading).display()#h.body]
  ]
]
#show: rest => text(size: 12pt)[#rest]
#set par(first-line-indent: 2em, justify: true)

#par()[
  #set text(size: 16pt)
  实验名称：#box(width: 50%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, name))
]

= 实验目的
#enum(
  ..purpose
)

= 实验原理
#par(principle)

= 实验内容
#set heading(numbering: (..nums) => if nums.pos().len() == 3 [\(#nums.pos().last()\)] else [#nums.pos().last().])
#for item in tasks [
  == #item.name
  === 实验步骤
  #item.steps
  === 实验现象
  #item.phenomena
  === 数据记录、分析与处理
  #item.data
  === 实验结论
  #item.conclusion
]
#set heading(numbering: "一、")

= 建议和体会
#experience
= 思考题
#thinking
