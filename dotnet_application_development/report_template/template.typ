#import "content.typ": *

#set page(paper: "a4", margin: (x: 3.18cm, y: 2.54cm))
#set par(first-line-indent: 0em)
#set text(font: ("Times New Roman", "SimSun"), lang: "zh", fallback: true)

#align(center)[
  #set par(leading: 2.41em)
  = #text(size: 22pt)[第 #week 周 C\#作业] \ #text(size: 18pt)[上机实践 #week]
]

#show heading.where(level: 2): h => block(height: 1.73em, text(size: 16pt, h.body))
#show heading.where(level: 3): h => block(height: 1.73em, text(size: 15pt, h.body))

#let i = 1
#for item in experiments [
  #set text(size: 10.5pt)
  == 实验 #i #item.name
  #(i += 1)
  === 实验目的：
  #item.purpose
  === 实验要求：
  #item.requirement
  === 实验效果：
  #item.result
  === 实验源代码：（以项目代码形式另外附录）
]
