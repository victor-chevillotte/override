### step 1 : decompile binary with ghidra

### step 2 : Check all the functions availaible :

- We find a main function which takes to inputs : a string[32] `login` and an unsigned int `serialnbr`
- The main function then passes the two variable to a `auth` function
- If the `auth` function returns 0, a shell is launched !
- In the `auth` function the `login` is hashed and then compared to the `serialnbr`
- We also find that the `login` must be at least 6 char long.

Our strategy is to create a function that reproduces the auth function hash and then print the result of the hash. As a result will be able to input a `login` and the corresponding hash as the `serialnbr` to launch the shell.

### step 3 : Create the hash function :

We choose `aaaaaa` as login (must be at least 6 char long) and copy the code of the decompiled hash function.

You can find our hash function at `Ressources/hash.c`

We launch it :

```
gcc Ressources/hash.c && ./a.out
```

And we get `6231562` as a result

### step 4 : exploit :

We launch the binary and set as first input login `aaaaaa` and `6231562` for the second input (serial number).

```
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231562%
Authenticated!
$ whoami
level07
```

It works ! We get a shell and we can cat the pass :

```
cat /home/users/level07/.pass
```