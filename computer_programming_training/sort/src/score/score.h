// Score.h
#ifndef SCORE
#define SCORE

struct score
{
    // 学号，最多存放8个字符
    char id[9];
    // 5门课程成绩及总分
    int Chinese, Math, English, Physics, Chemistry, Total;
    /*
    重载6个关系运算符函数
    使得两个结构体变量之间可以直接进行比较
    从这6个函数体可见，实际上是比较总分Total
    */
    bool operator< (const score &s) const { return Total <  s.Total; }
    bool operator<=(const score &s) const { return Total <= s.Total; }
    bool operator> (const score &s) const { return Total >  s.Total; }
    bool operator>=(const score &s) const { return Total >= s.Total; }
    bool operator==(const score &s) const { return Total == s.Total; }
    bool operator!=(const score &s) const { return Total != s.Total; }
};

// 设置原始数据
void init_score(score *data, int n);

#endif
