#ifndef DTO
#define DTO

// 排序结果
typedef struct sort_result
{
    // 比较次数
    unsigned long long compare;
    // 赋值次数
    unsigned long long assign;
} sort_result;

// 测试结果
typedef struct test_result
{
    // 比较次数
    unsigned long long compare;
    // 赋值次数
    unsigned long long assign;
    // 运行时间 (ms)
    double time;
    // 正确性
    bool correct;
} test_result;

#endif
