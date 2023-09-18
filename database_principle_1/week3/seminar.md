---
marp: true
---

# 第3周研讨

---

# 聚集索引

聚集索引就是存放的物理顺序和列中的顺序一样。

一个没加主键的表，它的数据无序的放置在磁盘存储器上，一行一行的排列的很整齐。如果给表上了主键，那么表在磁盘上的存储结构就由整齐排列的结构转变成了树状结构，也就是平衡树结构，换句话说，就是整个表就变成了一个索引，也就是所谓的聚集索引。 这就是为什么一个表只能有一个主键， 一个表只能有一个聚集索引，因为主键的作用就是把表的数据格式转换成索引（平衡树）的格式放置。

---

# 非聚集索引

非聚集索引与聚集索引的区别在于非聚集索引的叶子节点不存储表中的数据，而是存储该列对应的主键，想要查找数据我们还需要根据主键再去聚集索引中进行查找，这个再根据聚集索引查找数据的过程称为回表。

---

# 索引的作用

索引是与表或视图关联的磁盘上结构，可以加快从表或视图中检索行的速度。

---

# 验证索引

TODO

---

# 查找有学生重修的课程，输出重修课的开课学期，课程名，教师工号

```sql
select o.xq, km, o.gh from c
inner join o on o.kh == c.kh
where c.kh in (
    select distinct kh from e as tmp where exists (
        select * from e where tmp.kh == e.kh and tmp.xq != e.xq
    )
);
```

|      xq      |    km    | gh  |
| :-: | :-: | :-: |
| 2012-2013 秋季 | 离散数学 | 103 |
| 2013-2014 秋季 | 离散数学 | 102 |

---

# 查询上了马小红老师开的所有课的学生学号和课号及成绩

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

---

# 查询上了马小红老师开的所有课的学生学号和课号及成绩

|  xh  |    kh    | pscj | kscj | zpcj |
| :-: | :-: | :-: | :-: | :-: |
| 1103 | 08305001 | 56.0 | 56.0 | 56.0 |
| 1103 | 08305002 | 75.0 | 75.0 | 75.0 |
| 1103 | 08305003 | 84.0 | 84.0 | 84.0 |
| 1103 | 08305001 |      |      |      |
| 1103 | 08305004 |      |      |      |

---

# 游戏数据库

| Players | PID | NICKNAME | EMAIL | PASSWORD | SCORE | RANK | WIN | LOST |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 玩家 | 玩家 ID | 昵称 | 邮箱 | 密码 | 积分 | 等级 | 赢的次数 | 输的次数 |

| Games | GID | GNAME | VALUE | CID | DEVELOPER | EDITION |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 游戏 | ID | 游戏名 | 分值 | 游戏类别 | 开发者 | 版本 |

| Category | CID | CNAME | DESCRIPTION |
| :-: | :-: | :-: | :-: |
| 游戏类别 | 游戏 ID | 类别名称 | 描述 |

---

# 游戏数据库

| Battle | GID | PLAYER1 | PLAYER2 | WINNER | STATUS | TIME | DUR |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 对战 | 游戏 ID | 玩家 1 | 玩家 2 | 胜者 | 状态 | 开始时间 | 时长 |

| Rank | RID | RNAME | SCORE | UP_SCORE | DESCRIPTION |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 等级 | 等级 ID | 等级名 | 等级分 | 升级分 | 描述 |

> 用 SQL 语言实现下列操作（提倡多种方法）

---

# 查询胜率大于 50% 的玩家玩过的由“盛大公司”开发的游戏的名称和分值

```sql
select GNAME, VALUE from Games where GID == 
(
    select GID from Battle 
    where PLAYER1 == (select pid from Players where WIN/LOST > 0.5) 
    or PLAYER2 == (select pid from Players where WIN/LOST > 0.5)
)
and DEVELOPER == "盛大公司";
```

---

# 查询玩过所有游戏并获胜过的游戏玩家的昵称、积分、等级名以及还差多少分可以升级

```sql
select NICKNAME, SCORE, Rank.RNAME, Rank.UP_SCORE from Players
inner join Rank on Rank.RID == Players.RANK
where not exists
(
    select * from Games where not exists
    (
        select * from Battle where WINNER == Players.PID
            and Games.GID == Battle.GID
    )
);
```

---

# 查询游戏玩家 P001 没有玩过的游戏名称及其类别 ID

```sql
select GID, CID from Games where not exists
(
    select * from Battle where 
        GID == Battle.GID and
        (Battle.PLAYER1 == 'P001' or Battle.PLAYER2 == 'P001')
);
```

---

# 查询至少在“B01(王者荣耀)”和“B02(帝国时代)”两个游戏中都获胜过的游戏玩家的昵称、手机和等级名

```sql
select NICKNAME, EMAIL, Rank.RNAME from Players
inner join Rank on Rank.RID == Players.RANK
where exists
(
    select * from Battle where Battle.WINNER == Players.PID 
        and Battle.GID == 'B01'
)
and exists
(
    select * from Battle where Battle.WINNER == Players.PID 
        and Battle.GID == 'B02'
);
```
