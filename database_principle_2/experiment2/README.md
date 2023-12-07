# Experiment II

1. Launch tree instances (i.e., instance A & B in Zone 1, instance C in Zone 2) in clouds;
2. SSH without password across three instances;
3. Install JAVA and set environment path at three instances;
4. Install both pseudo-distributed-mode and distributed-mode Hadoop cluster;
5. Set the number of replica equal to 3 in HDFS;
6. Individually kill the slave and master instance and discuss the behavior of HDFS.


Reference

1. https://hadoop.apache.org/docs/r2.7.0/hadoop-project-dist/hadoop-common/SingleCluster.html
2. Download configuration: [slaves](https://www.aidac-shu.com/assets/slaves)
3. Download configuration: [core-site.xml](https://www.aidac-shu.com/assets/core-site.xml)
4. Download configuration: [hdfs-site.xml](https://www.aidac-shu.com/assets/hdfs-site.xml)
5. Download configuration: [mapred-site.xml](https://www.aidac-shu.com/assets/mapred-site.xml)
6. Download configuration: [yarn-site.xml](https://www.aidac-shu.com/assets/yarn-site.xml)

Useful Command Lines for Setup Distributed-Cluster-Mode Hadoop:

1. `sudo apt-get update`
2. `sudo apt-get install vim`
3. `sudo apt-get install openssh-server`
4. `shh-keygen -t rsa -C “yangliu476730@yahoo.com"`
5. `cd .ssh`
6. `cat id_rsa.pub >> authorized_keys`
7. `sudo apt-get install openjdk-8-jre openjdk-8-jdk`
8. `vim ~/.bashrc`
9. `source ~/.bashrc`
10. `sudo vim /etc/hostname`
11. `sudo hostname master`
12. `sudo vim /etc/hosts`
13. `sudo reboot`
14. `wget https://archive.apache.org/dist/hadoop/common/hadoop-2.7.0/hadoop-2.7.0.tar.gz`
15. `sudo tar -zxf hadoop-2.7.0.tar.gz -C /usr/local`
16. `cd /usr/local`
17. `sudo mv ./hadoop-2.7.0 ./hadoop`
18. `sudo chown -R ubuntu ./hadoop`
19. `./bin/hadoop version`
20. `vim /usr/local/hadoop/etc/hadoop/slaves`
21. `vim /usr/local/hadoop/etc/hadoop/core-site.xml`
22. `vim /usr/local/hadoop/etc/hadoop/hdfs-site.xml`
23. `vim /usr/local/hadoop/etc/hadoop/mapred-site.xml`
24. `vim /usr/local/hadoop/etc/hadoop/yarn-site.xml`
25. `bin/hdfs namenode -format`
26. `sbin/start-all.sh`
27. `bin/hdfs dfs -mkdir -p /user/ubuntu`
28. `bin/hdfs dfs -mkdir input`
29. `bin/hdfs dfs -put ./etc/hadoop/*.xml input`
30. `bin/hdfs dfs -get ./etc/hadoop/*.xml input`
