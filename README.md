# Software-filecopy
基于QT的数据备份软件
一、实现功能
1.数据备份与还原
2.压缩解压
3.打包解包
4.特殊文件支持、元数据支持：管道文件、硬链接、软链接
5.用户管理
二、数据库
MYSQL
1.表information：
  id(int)、name(varchar、unique)、password(char)
2.表history：
  h_id(int)、user(varchar、外键)、time(char)、size(int)、oldpath(char)、path(char)
三、实现效果
1.用户管理与开始界面
<img width="391" alt="登录1" src="https://user-images.githubusercontent.com/63855793/202439786-51e3ba13-2798-417a-b3ac-729315d56bb0.png">
2.用户注册
<img width="393" alt="账号注册" src="https://user-images.githubusercontent.com/63855793/202439848-01c5b4ee-56b5-4c21-adaf-7737975d45a5.png">
3.备份与恢复
![img_v2_eda29d4a-d693-45ca-92e2-823fd724d05g](https://user-images.githubusercontent.com/63855793/202439899-db3cc198-63fc-407f-93c4-3b13c17addb8.jpg)
四、
备份目录：/home/fancy/packup/用户名

