---
marp: true
paginate: true
---

# 读者-写者问题

> 第十四组

---

# 简介

所谓“读者-写者问题”是指保证一个 Writer 进程必须与其他进程互斥地访问共享对象的同步问题。为实现 Reader 与 Writer 进程间在读或写时的互斥而设置了一个互斥信号量 `Wmutex`。另外，再设置一个整型变量 `Readcount` 表示正在读的进程数目。由于只要有一个 Reader 进程在读，便不允许 Writer 进程去写。因此，仅当 `Readcount=0`, 表示尚无Reader 进程在读时，Reader 进程才需要执行 `P(Wmutex)` 操作。若 `P(Wmutex)` 操作成功，Reader进程便可去读，相应地，做 `Readcount+1` 操作。同理，仅当Reader进程在执行了 `Readcount` 减 1 操作后其值为 0 时，才须执行 `V(Wmutex)` 操作，以便让 Writer 进程写。又因为 `Readcount` 是一个可被多个 Reader 进程访问的临界资源，因此，应该为它设置一个互斥信号量 `rmutex`。

---

# 基本规则

1. 多个读者可以同时读取共享资源，但它们不能与写者线程同时访问共享资源。
2. 当写者线程正在修改共享资源时，不允许其他读者或写者线程进入，以确保数据的一致性。
3. 写者线程具有高优先级，以确保写入操作不会被长时间阻塞。
4. 如果有多个写者线程等待写入共享资源，它们必须按顺序访问，以避免竞态条件和数据不一致性。

---

# 名词解释

- 记录区（Record Section）
   - 记录区用以记录当前有多少读者和写者在访问共享对象。在本问题中，记录区用于同步读者和写者之间的访问，以及保证某一类进程的互斥。
- 临界区（Critical Section）
   - 临界区在本问题中就是实际的读或写共享对象的代码段。在进入临界区之前，进程必须获得相应的信号量（记录区中的信号量），以确保互斥访问。
- 退出区（Exit Section）
   - 退出区是在临界区执行完毕后的代码段，用于释放资源、信号量或做一些清理工作。在本问题中，退出区可以用于减少读者或写者的计数，并释放相应的信号量。
- 剩余区（Remainder Section）
   - 剩余区是在退出临界区之后，但在进程完全结束之前执行的代码段。这个区域用于处理非共享资源或其他不需要互斥的任务。

---

# 解题思路

1. 初始化记录型信号量：
   - 创建两个记录型信号量，一个记录读者数量，一个记录写者数量，初始值都为1。
2. Reader 进程进入读操作：
   - 在进入读操作之前，首先尝试获取读者信号量。如果写者正在访问共享对象或有写者等待，会被阻塞。如果可以获取读者信号量，读者数量加1，表示有一个读者正在读。读者完成读操作后，读者数量减1，释放读者信号量。

---

# 解题思路

3. Writer 进程进入写操作：
   - 在进入写操作之前，首先尝试获取写者信号量。如果有其他读者或写者正在访问共享对象，会被阻塞。如果可以获取写者信号量，写者数量加1，表示有一个写者正在写。写者完成写操作后，写者数量减1，释放写者信号量。
    
这种方法确保了写者和读者之间的互斥访问，并且允许多个读者同时读。

---

# 代码

---

# 共享内存

在读者-写者问题中，存在读者和写者这两种进程。根据题意，不同读者进程都需要读写 `read_count`。因此在这个问题中， `read_count` 是临界资源。

对于 `fork()` 函数，创建出来的进程与原来的进程相互独立，因此对于 `read_count` 变量，不同进程读写的变量是不同的。这时候就需要共享内存来保存这一变量。

此外，两个信号量同样需要共享。

<!-- 共享内存相关的函数就在 `sys/shm.h` 头文件中。 -->

---

# 信号量（集）

需要读者和写者两个信号量，因此使用信号量集来实现。

<!-- 有关信号量的函数在 `sys/sem.h` 头文件中。 -->

---

# POSIX 实现

> 代码见 [operating_system_1/seminar2/src/posix.c](https://github.com/wangyw15/study/blob/main/operating_system_1/seminar2/src/posix.c)

---

# 跨进程共享内存

> `unistd.h`
>
> `sys/mman.h`

```c
// allocate
if ((read_count = mmap(NULL, sizeof(int), 
    PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0)) < 0)
{
    perror("mmap for read_count failed\n");
    exit(1);   
}
// release
munmap(read_count, sizeof(int));
```

此处为匿名，保存在内存中，易失

也有以文件为基础的共享内存，因此可以跨机器使用

---

# 信号量

> `semaphore.h`

```c
sem_init(wmutex, 1, 1); // initialization
sem_wait(rmutex); // P
sem_post(rmutex); // V
sem_close(rmutex); // just close without release
sem_destroy(rmutex); // close and release
```

[释放资源](#释放资源)

---

# SystemV 实现

> 代码见 [operating_system_1/seminar2/src/systemv.c](https://github.com/wangyw15/study/blob/main/operating_system_1/seminar2/src/systemv.c)

共享内存使用 `sys/shm.h`

信号量使用 `sys/sem.h`

---

# `sys/shm.h` 主要函数

> `/usr/include/x86_64-linux-gnu/sys/shm.h`

- `extern int shmget (key_t __key, size_t __size, int __shmflg) __THROW;`
   - 开辟一块共享内存空间
- `extern void *shmat (int __shmid, const void *__shmaddr, int __shmflg) __THROW;`
   - 挂载共享内存
- `extern int shmdt (const void *__shmaddr) __THROW;`
   - 解除挂载
- `extern int shmctl (int __shmid, int __cmd, struct shmid_ds *__buf) __THROW;`
   - 控制共享内存（可以用于销毁）

---

# `sys/sem.h`

> `/usr/include/x86_64-linux-gnu/sys/sem.h`

- `extern int semget (key_t __key, int __nsems, int __semflg) __THROW;`
   - 新建信号量
- `extern int semctl (int __semid, int __semnum, int __cmd, ...) __THROW;`
   - 控制信号量
- `extern int semop (int __semid, struct sembuf *__sops, size_t __nsops) __THROW;`
   - 操作信号量

--- 

# `key_t __key`

| 内容 | 效果 |
| :-: | :-: |
| `IPC_PRIVATE` | 只有自身和子进程能访问 |
| `ftok()` | 无关联进程间可用 |

```c
#define IPC_PRIVATE ((__kernel_key_t) 0)
```

---

# `__shmflg` / `__semflg`

```c
/* resource get request flags */
#define IPC_CREAT  00001000   /* create if key is nonexistent */
#define IPC_EXCL   00002000   /* fail if key exists */
#define IPC_NOWAIT 00004000   /* return error on wait */
```

---

# `int __cmd`

```c
#define IPC_RMID 0     /* remove resource */
#define IPC_SET  1     /* set ipc_perm options */
#define IPC_STAT 2     /* get ipc_perm options */
#define IPC_INFO 3     /* see ipcs */
```

---

# `sembuf`

```c
/* Structure used for argument to `semop' to describe operations.  */
struct sembuf
{
  unsigned short int sem_num;   /* semaphore number */
  short int sem_op;             /* semaphore operation */
  short int sem_flg;            /* operation flag */
};
```
