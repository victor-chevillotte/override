void secret_backdoor(void)
{
  char buffer [128];
  
  fgets(buffer,128,_stdin);
  system(buffer);
  return;
}

void set_msg(char *msg)
{
  long lVar1;
  undefined8 *ptr;
  undefined8 buffer [128];
  
  ptr = buffer;
  for (lVar1 = 0x80; lVar1 != 0; lVar1 = lVar1 + -1) {
    *ptr = 0;
    ptr = ptr + 1;
  }
  puts(">: Msg @Unix-Dude");
  printf(">>: ");
  fgets((char *)buffer,1024,_stdin);
  strncpy(msg,(char *)buffer,(long)*(int *)(msg + 180));
  return;
}

void set_username(long username)
{
  long n;
  undefined8 *ptr;
  undefined8 buffer [17];
  int i;
  
  ptr = buffer;
  for (n = 0x10; n != 0; n = n + -1) {
    *ptr = 0;
    ptr = ptr + 1;
  }
  puts(">: Enter your username");
  printf(">>: ");
  fgets((char *)buffer,128,_stdin);
  for (i = 0; (i < 0x29 && (*(char *)((long)buffer + (long)i) != '\0')); i = i + 1) {
    *(undefined *)(username + 0x8c + (long)i) = *(undefined *)((long)buffer + (long)i);
  }
  printf(">: Welcome, %s",(char *)(username + 0x8c));
  return;
}

void handle_msg(void)
{
  char buffer [140];
  undefined8 local_3c;
  undefined8 local_34;
  undefined8 local_2c;
  undefined8 local_24;
  undefined8 local_1c;
  undefined4 local_14;
  
  local_3c = 0;
  local_34 = 0;
  local_2c = 0;
  local_24 = 0;
  local_1c = 0;
  local_14 = 0x8c;
  set_username((long)buffer);
  set_msg(buffer);
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
