#ifndef UTIL
#define UTIL

// 生成数据 0.降序 1.升序 2.均匀分布 3.正态分布
void init_data(int *data, int size, int flag);
// 等待一段时间
void wait(int milliseconds);
// 清屏
void clear_console();

#endif