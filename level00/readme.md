### step 1: Decompile with Ghidra

We get the c source code of the program  

### step 2: Code analysis

The main is simple :
- The `scanf` function reads stdin and store the result as a  int in the variable `int nbr[4]`
- The value of `nbr[0]` is then compared to `5276` and a shell is opened the it compares to `true`

### step 3: Exploit

1) Run the binary : `./level00`
2) Input the value `5376` when asked for a password
3) In the opened shell, input `cat /home/users/level01/.pass` to read the flag

```
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```