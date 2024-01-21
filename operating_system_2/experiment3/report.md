# 实验（三）请求页式存储管理

# 运行配置

物理块大小为4-32，虚拟块大小固定为32

指令组成：50%顺序访问，25%前半随机访问，25%后半随机访问

# 运行结果

```
Physical size: 4
OPT: 0.28600000000000003
LRU: 0.128

Physical size: 5
OPT: 0.33499999999999996
LRU: 0.15300000000000002

Physical size: 6
OPT: 0.382
LRU: 0.18200000000000005

Physical size: 7
OPT: 0.42700000000000005
LRU: 0.21299999999999997

Physical size: 8
OPT: 0.469
LRU: 0.236

Physical size: 9
OPT: 0.507
LRU: 0.261

Physical size: 10
OPT: 0.5409999999999999
LRU: 0.29300000000000004

Physical size: 11
OPT: 0.5740000000000001
LRU: 0.32199999999999995

Physical size: 12
OPT: 0.604
LRU: 0.347

Physical size: 13
OPT: 0.634
LRU: 0.386

Physical size: 14
OPT: 0.6619999999999999
LRU: 0.41800000000000004

Physical size: 15
OPT: 0.6859999999999999
LRU: 0.45199999999999996

Physical size: 16
OPT: 0.708
LRU: 0.473

Physical size: 17
OPT: 0.725
LRU: 0.473

Physical size: 18
OPT: 0.742
LRU: 0.475

Physical size: 19
OPT: 0.759
LRU: 0.48

Physical size: 20
OPT: 0.776
LRU: 0.486

Physical size: 21
OPT: 0.792
LRU: 0.486

Physical size: 22
OPT: 0.808
LRU: 0.486

Physical size: 23
OPT: 0.8240000000000001
LRU: 0.487

Physical size: 24
OPT: 0.84
LRU: 0.487

Physical size: 25
OPT: 0.856
LRU: 0.488

Physical size: 26
OPT: 0.872
LRU: 0.488

Physical size: 27
OPT: 0.888
LRU: 0.488

Physical size: 28
OPT: 0.904
LRU: 0.491

Physical size: 29
OPT: 0.92
LRU: 0.494

Physical size: 30
OPT: 0.9359999999999999
LRU: 0.496

Physical size: 31
OPT: 0.952
LRU: 0.499

Physical size: 32
OPT: 0.968
LRU: 0.968
```

# 实验结论

OPT作为最佳算法，只能在预知所有访问的时候才能够使用，因此一般作为性能基准，LRU性能在物理块和虚拟块大小相同时性能最好
