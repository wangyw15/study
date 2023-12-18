# Experiment I

1. Launch two instances (i.e., instance A and instance B)in clouds;
2. SSH without password between two instances;
3. Install Mysql at two instances;
4. Create database and user in instance A;
5. Do remote connection at instances B and list the databases stored at instance A.

# Reference

> https://snapshooter.com/blog/how-to-configure-mysql-for-remote-connection-on-ubuntu-1804

Useful Command Lines in Instance A (Server):

1. `sudo apt-get update`
2. `sudo apt-get install vim`
3. `sudo apt-get install openssh-server`
4. `shh-keygen -t rsa -C “yangliu476730@yahoo.com"`
5. `cd .ssh`
6. `cat id_rsa.pub >> authorized_keys`
10. `scp id_rsa.pub ubuntu@[client_IP_address]:~/.ssh/id_rsa.pub`
11. `scp id_rsa ubuntu@[client_IP_address]:~/.ssh/id_rsa`
12. `sudo apt-get install mysql-server`
13. `sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf`
14. `sudo mysql -u root -p`
15. `CREATE DATABASE [name];`
16. `CREATE USER 'client'@'[client_IP_address]' IDENTIFIED BY 'password';`
17. `GRANT ALL ON *.* to 'client'@'[client_IP_address]';`
18. `FLUSH PRIVILEGES;`

Useful Command Lines in Instance B (Client):

7. `sudo apt-get update`
8. `sudo apt-get install vim`
9. `sudo apt-get install openssh-server`
12. `cat id_rsa.pub >> authorized_keys`
19. `sudo apt-get install mysql-server`
20. `mysql -h [server_IP_address] -u client -p`
