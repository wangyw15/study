# 第三周实验报告

1. 查询每门课程中分数最高的学生学号和学生姓名。

```sql
select xm, xh from s where xh in 
(
    select xh from (
        select max(zpcj), xh from e
            where zpcj is not null group by kh
    )
);
```

| xm  |  xh  |
| :-: | :-: |
| 刘晓明 | 1102 |
| 张颖  | 1103 |
| 张晓峰 | 1107 |

2. 求年龄大于所有女同学年龄的男学生姓名和年龄。

```sql
select xm as name, 2023-(cast(substr(csrq, 1, 4) as int)) as age from s where cast(substr(csrq, 1, 4) as int) < (select cast(substr(csrq, 1, 4) as int) as year from s where xb == '女');
```

| name | age |
| :-: | :-: |
| 刘晓明  | 31  |
| 刘成刚  | 32  |
| 张晓峰  | 31  |

3. 查询上了马小红老师开的所有课的学生学号和课号及成绩。

```sql
select xh, kh, pscj, kscj, zpcj from e where xh == (
    select distinct xh from e as p1 where not exists
    (
        select * from o where gh == (
            select gh from t where xm == '马小红'
        )
        and not exists (
            select * from e as p2 
                where p2.kh == o.kh and p2.xh == p1.xh
        )
    )
);
```

|  xh  |    kh    | pscj | kscj | zpcj |
| :-: | :-: | :-: | :-: | :-: |
| 1103 | 08305001 | 56.0 | 56.0 | 56.0 |
| 1103 | 08305002 | 75.0 | 75.0 | 75.0 |
| 1103 | 08305003 | 84.0 | 84.0 | 84.0 |
| 1103 | 08305001 |      |      |      |
| 1103 | 08305004 |      |      |      |

4. 查询计算机学院男生选修本学院教授开设的课不及格的且还未重修的课，输出学生的学期，学号，课号，按学期升序，学期相同按学号升序排列。

```sql
select xq, xh, kh from e as failed where xh == (
    select xh from s where yxh == (
            select yxh from d where mc == '计算机学院'
        ) and xb == '男'
) 
and kh in (
    select kh from c where yxh == (
        select yxh from d where mc == '计算机学院'
    )
)
and zpcj < 60 
and not exists (
    select * from e where xq == failed.xq
)
order by xq asc, xh asc;
```

数据库中不存在要求查询的数据
