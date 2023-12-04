void secret_backdoor(void)
{
  char buffer [128];
  
  fgets(buffer,128,_stdin);// we must set /bin/sh or cat pass
  system(buffer);
  return;
}

void set_msg(char *ref)
{
  long count;
  undefined8 *ptr;
  undefined8 buffer [128]; // 1024
  
  ptr = buffer;
  for (count = 128; count != 0; count = count - 1) {// init buffer with zeros
    *ptr = 0;
    ptr = ptr + 1;
  }
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets((char *)buffer,1024,_stdin);
  strncpy(ref,(char *)buffer,(long)*(int *)(ref + 180));
  return;
}

void set_username(long ref)
{
  long n;
  undefined8 *ptr;
  undefined8 buffer [17]; //136
  int i;
  
  ptr = buffer;
  for (n = 16; n != 0; n = n + -1) {
    *ptr = 0;
    ptr = ptr + 1;
  }
  puts(">: Enter your username");
  printf(">>: ");
  fgets((char *)buffer,128,_stdin);
  for (i = 0; (i < 41 && (*(char *)((long)buffer + (long)i) != '\0')); i = i + 1) {
    *(undefined *)(ref + 140 + (long)i) = *(undefined *)((long)buffer + (long)i);
  }
  printf(">: Welcome, %s",(char *)(ref + 140));
  return;
}

void handle_msg(void)
{
  char ref [140];
  set_username((long)ref);
  set_msg(ref);
  puts(">: Msg sent!");
  return;
}

int main(void)
{
  puts(
      "--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------"
      );
  handle_msg();
  return 0;
}
