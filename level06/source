int auth(char *str,uint serialnbr)
{
  size_t len;
  int res;
  long ptrace;
  int i;
  uint hash;
  
  len = strcspn(str,"\n");
  str[len] = '\0';


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
      hash = ((int)str[3] ^ 0x1337U) + 0x5eeded;
      for ( int i = 0 ; i < strnlen(str, 32) ; i++ ) {
        if (str[i] < ' ') {
          return 1;
        }
        hash = hash + ((int)str[i] ^ hash) % 0x539;
      }
      if (serialnbr == hash) {
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
  uint serialnbr;
  char login [32];
  int i;
  
  i = *(int *)(offset + 0x14);
  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(login,0x20,stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  __isoc99_scanf();
  res = auth(login,serialnbr);
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


