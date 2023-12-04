### step 1: Decompile with Ghidra

We get the c source code of the program  

### step 2: Code analysis

- The main function takes a number as an input with scanf then calls the test function
- The test function compares the input value and then calls a decrypt function 
- test() calls decrypt: with the result if it's less than 21, else with a random number.
- The function decrypt() then passes a crypt over the parameter.
- If the initial user-inputed password is correct, decrypt() prints "Congratulations!" and calls system("/bin/sh").

### step 3: Test with one number

Programatic approach :  
To do a test with a number, it should be inputed into the executable, accompanied by a shell command. The command to be used is:

```
( echo 10 ; sleep .1 ; echo 'cat /home/users/level04/.pass' ) | ./level03
```

The purpose of the `sleep` command here is to provide enough time for the execution of the `system()` command.

As a result we have :

```***********************************
*               level03         **
***********************************
Password:
Invalid Password
```

### step 4: Calculate range of possible values of input

We need to calculate the range of values possible for n :

We have :
```
unsigned long nb = constant - password;
```

And  `nb <= 21`

Constant = 322424845

322424845 - password <= 21
password >= 21 - 322424845 = 322424824
password > 322424824

Also if password < 0  nb > 21

So the range of password is 322424824 to 322424845

### step 5: Loop to test all values of nbr

We can iterate through the range of numbers found before with a loop. We wrap our command in a `bash for` :

```
for i in {322424824..322424845} ; do echo $i ; ( echo $i ; sleep .1 ; echo 'cat /home/users/level04/.pass'; ) | ./level03 ; done
```

And in the output we get the flag :
```
***********************************
*               level03         **
***********************************
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
Password:322424828
***********************************
*               level03         **
***********************************
Password:
Invalid Password
322424829
***********************************
*               level03         **
***********************************
```

The correct input number is 322424827 !
