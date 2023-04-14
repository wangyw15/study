#import "content/info.typ": *
#import "content/overview.typ": *
#import "content/conclusion.typ": *

#set page(paper: "a4", margin: (x: 3.18cm, y: 2.54cm))
#set heading(numbering: "一、")

#set text(font: "SimHei", weight: "bold")

#align(center, text(size: 18pt)[
  #heading(numbering: none)[上海大学 计算机学院 \ 《计算机组成原理实验》报告#num]
])

#set text(size: 15pt)
#grid(columns: (auto, 1fr, auto, 1fr),
  box(width: auto, inset: 2pt, stroke: none)[姓名],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, name)),
  box(width: auto, inset: 2pt, stroke: none)[学号],
  box(width: 80%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, id))
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
#show: rest => text(size: 12pt)[#rest]
#show heading.where(level: 1): h => block()[
  #set text(size: 14pt, weight: "bold")
  #counter(heading.where(level: 1)).display()#h.body
]
#show heading.where(level: 3): h => block()[
  #set text(size: 12pt, weight: "bold")
  #h.body
]
#set par(first-line-indent: 2em, justify: true)

#par(justify: true)[
  #set text(size: 16pt)
  实验名称：#box(width: 50%, inset: 2pt, stroke: (bottom: 1pt + black), align(center, exp_name))
]

= 实验目的

#enum(
  ..purpose.map(p => text[#p])
)

= 实验原理

#par(justify: true)[#principle]

= 实验内容

#set heading(numbering: none)
#include "content/experiment_content.typ"
#set heading(numbering: "一、")

= 建议和体会

#experience

= 思考题

#thinking