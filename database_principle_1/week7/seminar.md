---
marp: true
---


# 1. 用关系代数完成下列查询

## (1) 查询至少播放两部电影的座位数大于300的影院名

$$
\Pi_2(\sigma_{6>'300'}(\mathbf{C}\bowtie\Pi_3(\sigma_{3=9 \wedge 2 \ne 8}(\mathbf{S} \times \mathbf{S}))))
$$

## (2) 查询放映过张艺谋导演的全部影片的影院名

$$
\Pi_{CNAME}(\mathbf{C}\bowtie(\Pi_{CID,FID}(\mathbf{S})\div \Pi_{FID}(\sigma_{DIRECTOR='张艺谋'}(\mathbf{F}))))
$$

---

# 2. 用关系代数完成下列查询

## (3) 查询万达影院没有播放的影片编号

$$
\Pi_{FID}(\mathbf{F})-\Pi_{FID}(\sigma_{CNAME='万达影院'}(\mathbf{S}\bowtie\mathbf{C}))
$$

## (4) 查询放映过所有贺岁片的影院名

$$
\Pi_{CNAME}(\mathbf{C}\bowtie(\Pi_{FID,CID}(S)\div\Pi_{FID}(\mathbf{F})))
$$

---

# 3. 游戏数据库中有如下表

| 表名 | PID | NICKNAME | EMAIL | PASSWORD | SCORE | RANK | WIN | LOST |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Players<br/>玩家 | 玩家 ID | 昵称 | 邮箱 | 密码 | 积分 | 等级 | 赢的次数 | 输的次数 |

| 表名 | GID | GNAME | VALUE | CID | DEVELOPER | EDITION |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Games<br/>游戏 | ID | 游戏名 | 分值 | 游戏类别 | 开发者 | 版本 |

| 表名 | CID | CNAME | DESCRIPTION |
| :-: | :-: | :-: | :-: |
| Category<br/>游戏类别 | 游戏 ID | 类别名称 | 描述 |

---

| 表名 | GID | PLAYER1 | PLAYER2 | WINNER | STATUS | TIME | DUR |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Battle<br/>对战 | 游戏 ID | 玩家 1 | 玩家 2 | 胜者 | 状态 | 开始时间 | 时长 |

| 表名 | RID | RNAME | SCORE | UP_SCORE | DESCRIPTION |
| :-: | :-: | :-: | :-: | :-: | :-: |
| Rank<br/>等级 | 等级 ID | 等级名 | 等级分 | 升级分 | 描述 |

---

# 用关系代数实现下列操作

## (5) 查询胜率大于50%的玩家玩过的由“盛大公司”开发的游戏的名称和分值

$$
\Pi_{GNAME,VALUE}(\sigma_{PID=WINNER}((\Pi_{PID}(\sigma_{WIN>LOST}(Players))\times(\Pi_{GID,WINNER}(Battle)\bowtie\Pi_{GNAME,GID,VALUE}(\sigma_{DEVELOPER='盛大公司'}(Games))))))
$$

## (6) 查询至少在“B01(王者荣耀)”和“B02(帝国时代)”两个游戏中都获胜过的游戏玩家的昵称、手机和等级名

$$
\Pi_{2,6}(Players\bowtie(\Pi_4(\sigma_{4=11\wedge 1='B01'\wedge8='B02'}(Battle\times Battle))))
$$
