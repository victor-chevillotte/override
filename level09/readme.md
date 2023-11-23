### step 1: Decompile with Ghydra

- Binary in 64-bits

```
level09@OverRide:~$ file level09 
level09: setuid setgid ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0xa1a3a49786f29814c5abd4fc6d7a685800a3d454, not stripped
```

- Sources are available in `source.c`


### step 2: Code Analysis

- find secret backdoor function address : 
- find eip of set_username and set_msg
- find address of ref
- find offset between ref and eip address


dépasse sur message au 128 eme char dans username
final string : 
(python -c 'print("hhshs")' ; python -c 'print("hhshs")'; echo 'cat /home/users/end/.pass'; cat) | ./level09