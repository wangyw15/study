# 主题二 进程管理

所谓“读者-写者问题”是指保证一个 Writer 进程必须与其他进程互斥地访问共享对象的同步问题。为实现 Reader 与 Writer 进程间在读或写时的互斥而设置了一个互斥信号量 `Wmutex`。另外，再设置一个整型变量 `Readcount` 表示正在读的进程数目。由于只要有一个 Reader 进程在读，便不允许 Writer 进程去写。因此，仅当 `Readcount=0`, 表示尚无Reader 进程在读时，Reader 进程才需要执行 `P(Wmutex)` 操作。若 `P(Wmutex)` 操作成功，Reader进程便可去读，相应地，做 `Readcount+1` 操作。同理，仅当Reader进程在执行了 `Readcount` 减 1 操作后其值为 0 时，才须执行 `V(Wmutex)` 操作，以便让 Writer 进程写。又因为 `Readcount` 是一个可被多个 Reader 进程访问的临界资源，因此，应该为它设置一个互斥信号量 `rmutex`。

- “读者-写者问题”扩展一：利用记录型信号量集解决读者-写者问题。
- “读者-写者问题”扩展二：利用记录型信号量分别给出“读写无优先、写者优先”问题的同步算法；
- “读者-写者问题”扩展三：利用记录型信号量集分别给出“读写无优先、写者优先”问题的同步算法。