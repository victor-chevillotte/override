void    decrypt(int nb)
{
    int     index;
    long    len;
    char    *str;
    
    char *str = (char *)(int [4]){ 1971092817, 1734767456, 2070311806, 862026877 };

    len = strlen((char *)str);
    while (0 < len) {
        str += index;
        str += index;
        index += 1;
    }

    if (strncmp("Congratulations", str, 17) == 0)
        system("/bin/sh");
    else
        puts("\nInvalid Password");

    return ;
}

void     test(int nbr, int constant)
{
    unsigned long nb = constant - nbr;

    if (nb <= 21)
    {
        nb = nb << 2;
        nb += 134515184;
        nb = *(nb);
        void (*nb)();
        return 0;
    }

    decrypt(rand());
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