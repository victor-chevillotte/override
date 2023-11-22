int auth(char *param_1,uint param_2)
{
  size_t len;
  int res;
  long ptrace;
  int i;
  uint target;
  
  len = strcspn(param_1,"\n");
  param_1[len] = '\0';
  len = strnlen(param_1,0x20);
  if ((int)len < 6) {
    res = 1;
  }
  else {
    ptrace = ::ptrace(PTRACE_TRACEME);
    if (ptrace == -1) {
      puts("\x1b[32m.---------------------------.");
      puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
      puts("\x1b[32m\'---------------------------\'");
      res = 1;
    }
    else {
      target = ((int)param_1[3] ^ 0x1337U) + 0x5eeded;
      for (i = 0; i < (int)len; i = i + 1) {
        if (param_1[i] < ' ') {
          return 1;
        }
        target = target + ((int)param_1[i] ^ target) % 0x539;
      }
      if (param_2 == target) {
        res = 0;
      }
      else {
        res = 1;
      }
    }
  }
  return res;
}


int main(int ac,char **av)
{
  int res;
  int offset;
  uint param2;
  char buffer [32];
  int i;
  
  i = *(int *)(offset + 0x14);
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(buffer,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  __isoc99_scanf();
  res = auth(buffer,param2);
  if (res == 0) {
    puts("Authenticated!");
    system("/bin/sh");
  }
  if (i != *(int *)(offset + 0x14)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return (uint)(res != 0);
}