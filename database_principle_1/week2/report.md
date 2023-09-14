# 第二周实验报告

# 1. 验证在1000万个以上记录时在索引和不索引时的查询时间区别。

有索引时查询时间比无索引查询时间更快。

# 2. 查询2011年进校年龄大于20岁的男学生的学号与姓名。

|  xh  | xm  | xb |    csrq    | jg |    sjhm     | yxh |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 1101 | 李明  | 男  | 1993-03-06 | 上海 | 13613005486 | 2   |
| 1102 | 刘晓明 | 男  | 1992-12-08 | 安徽 | 18913457890 | 1   |
| 1103 | 张颖  | 女  | 1993-01-05 | 江苏 | 18826490423 | 1   |
| 1104 | 刘晶晶 | 女  | 1994-11-06 | 上海 | 13331934111 | 1   |
| 1105 | 刘成刚 | 男  | 1991-06-07 | 上海 | 18015872567 | 1   |
| 1106 | 李二丽 | 女  | 1993-05-04 | 江苏 | 18107620945 | 1   |
| 1107 | 张晓峰 | 男  | 1992-08-16 | 浙江 | 13912341078 | 1   |

在以上表中没有一个人在2011年时年龄大于20岁，因此将条件改为2023年时年龄大于30岁

```sql
select xh, xm from s where xb == '男' and 2023-cast(substr(csrq, 1, 4) as int) > 30;
```

运行结果如下

|  xh  | xm  |
| :-: | :-: |
| 1102 | 刘晓明 |
| 1105 | 刘成刚 |
| 1107 | 张晓峰 |

# 3. 检索刘晓明不学的课程的课程号。

```sql
select distinct(kh) from c where kh not in (select kh from e where xh in (select xh from s where xm == '刘晓明'));
```

运行结果如下

|    kh    |
| :-: |
| 08301001 |
| 08302001 |
| 08305003 

# 4. 查询计算机学院男生成绩及格、教授开设的课程的课程号、课名、开课教师姓名，按开课教师升序，课程号降序排序。

```sql
with temp as (select * from e where (select xb from s where s.xh == e.xh) == '男' and zpcj >= 60), temp2 as (select distinct(temp.kh), c.km, temp.gh from temp inner join c on temp.kh == c.kh) select temp2.kh, temp2.km, t.xm from temp2 inner join t on t.gh == temp2.gh order by t.xm asc, cast(temp2.kh as int) desc;
```

运行结果如下

|    kh    |  km   | xm  |
| :-: | :-: | :-: |
| 08305001 | 离散数学  | 吴宝钢 |
| 08305002 | 数据库原理 | 陈迪茂 |
| 08305003 | 数据结构  | 马小红 |

# 5. 检索学号比张颖同学大，年龄比张颖同学小的同学学号、姓名。

```sql
select xh, xm from s where cast(xh as int) > (select cast(xh as int) from s where xm == '张颖') and cast(substr(csrq, 1, 4) as int) > (select cast(substr(csrq, 1, 4) as int) from s where xm == '张颖');
```

运行结果如下

|  xh  | xm  |
| :-: | :-: |
| 1104 | 刘晶晶 |
