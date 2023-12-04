void decrypt(nb)
{
	char *crypt = "Q}|u`sfg~sf{}|a3";
	size_t len;
	size_t i;
	
	len = strlen(crypt);
	i = 0;
	
	while (i < len) {
		crypt[i] = crypt[i] ^ nb;
		i++;
	}
	
	if (strncmp(crypt, "Congratulations", 17) == 0) {
    	system("/bin/sh");
	}
	else {
		puts("\nInvalid Password");
	}

	return ;
}


void     test(int nbr, int constant)
{
    unsigned long nb = constant - nbr;

	if (nb > 21) {
		decrypt(rand());
	}
	decrypt(nb);
}


int     main(void)
{
    int nbr;

    srand(time(0));

    puts("***********************************");
    puts("*               level03         **");
    puts("***********************************");
    printf("Password:");

    scanf("%d", &nbr);
    test(nbr, 322424845);

    return 0;
}