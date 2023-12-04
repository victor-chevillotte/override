int main(void)
{
  uint nbr;
  char *ptr;
  char buffer [100];
  uint j;
  char c;

  fgets(buffer,100,stdin);
  j = 0;
  do {
    nbr = 0xffffffff;
    ptr = buffer;
    do {
      if (nbr == 0) break;
      nbr = nbr - 1;
      c = *ptr;
      ptr = ptr + 1;
    } while (c != '\0');
    if (!nbr - 1 <= j) { //~ = NOT
      printf(buffer);
      exit(0);
    }
    if (('@' < buffer[j]) && (buffer[j] < '[')) {
      buffer[j] = buffer[j] ^ 32; // ^ = XOR
    }
    j = j + 1;
  } while( true );
}