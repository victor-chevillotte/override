int get_unum(void)

{
  int int_tab [3];
  
  int_tab[0] = 0;
  fflush(stdout);
  __isoc99_scanf(&DAT_08048ad0,int_tab);
  clear_stdin();
  return int_tab[0];
}


int read_number(int n)

{
  uint input_nbr;
  
  printf(" Index: ");
  input_nbr = get_unum();
  printf(" Number at data[%u] is %u\n",input_nbr,*(uint *)(input_nbr * 4 + n));
  return 0;
}


int store_number(int n)

{
  uint input_nbr;
  uint input_index;
  int res;
  
  printf(" Number: ");
  input_nbr = get_unum();
  printf(" Index: ");
  input_index = get_unum();
  if ((input_index % 3 == 0) || (input_nbr >> 0x18 == 0xb7)) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    res = 1;
  }
  else {
    *(uint *)(input_index * 4 + n) = input_nbr;
    res = 0;
  }
  return res;
}


int main(int ac,char **av,char **env)
{
  int p;
  byte *pbVar1;
  int offset;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  byte offset2;
  char **envp;
  char **argv;
  int int_tab [100];
  int i;
  int j;
  int k;
  int l;
  int m;
  int n;
  int local_14;
  char c;
  uint count;
  int *int_ptr;
  char *str_ptr;
  
  offset2 = 0;
  argv = av;
  envp = env;
  local_14 = *(int *)(offset + 20);
  i = 0;
  j = 0;
  k = 0;
  l = 0;
  m = 0;
  n = 0;
  int_ptr = int_tab;
  for (p = 100; p != 0; p = p + -1) {
    *int_ptr = 0;
    int_ptr = int_ptr + 1;
  }
  for (; *argv != (char *)0x0; argv = argv + 1) {
    count = 0xffffffff;
    str_ptr = *argv;
    do {
      if (count == 0) break;
      count = count - 1;
      c = *str_ptr;
      str_ptr = str_ptr + (uint)offset2 * -2 + 1;
    } while (c != '\0');
    memset(*argv,0,~count - 1);
  }
  for (; *envp != (cbVar5
      if (count == 0) break;
      count = count - 1;
      c = *str_ptr;
      str_ptr = str_ptr + (uint)offset2 * -2 + 1;
    } while (c != '\0');
    memset(*envp,0,~count - 1);
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number stora ge service!   \n----------------------------------------------------\n Commands:                                           \n    store - store a number into the data storage    \n    read   - read a number from the data storage     \n    quit  - exit the program                         \n----------------------------------------------------\n   wil has reserved some storage :>                  \n----------------------------------------------------\n"
      );
  do {
    printf("Input command: ");
    i = 1;
    fgets((char *)&j,0x14,stdin);
    count = 0xffffffff;
    int_ptr = &j;
    do {
      if (count == 0) break;
      count = count - 1;
      c = *(char *)int_ptr;
      int_ptr = (int *)((int)int_ptr + (uint)offset2 * -2 + 1);
    } while (c != '\0');
    count = ~count;
    bVar2 = count == 1;
    bVar4 = count == 2;
    *(undefined *)((int)&i + count + 2) = 0;
    p = 5;
    int_ptr = &j;
    pbVar1 = (byte *)"store";
    do {
      if (p == 0) break;
      p = p + -1;
      bVar2 = *(byte *)int_ptr < *pbVar1;
      bVar4 = *(byte *)int_ptr == *pbVar1;
      int_ptr = (int *)((int)int_ptr + (uint)offset2 * -2 + 1);
      pbVar1 = pbVar1 + (uint)offset2 * -2 + 1;
    } while (bVar4);
    bVar3 = false;
    bVar2 = (!bVar2 && !bVar4) == bVar2;
    if (bVar2) {
      i = store_number((int)int_tab);
    }
    else {
      p = 4;
      int_ptr = &j;
      pbVar1 = &DAT_08048d61;
      do {
        if (p == 0) break;
        p = p + -1;
        bVar3 = *(byte *)int_ptr < *pbVar1;
        bVar2 = *(byte *)int_ptr == *pbVar1;
        int_ptr = (int *)((int)int_ptr + (uint)offset2 * -2 + 1);
        pbVar1 = pbVar1 + (uint)offset2 * -2 + 1;
      } while (bVar2);
      bVar4 = false;
      bVar2 = (!bVar3 && !bVar2) == bVar3;
      if (bVar2) {
        i = read_number((int)int_tab);
      }
      else {
        p = 4;
        int_ptr = &j;
        pbVar1 = &DAT_08048d66;
        do {
          if (p == 0) break;
          p = p + -1;
          bVar4 = *(byte *)int_ptr < *pbVar1;
          bVar2 = *(byte *)int_ptr == *pbVar1;
          int_ptr = (int *)((int)int_ptr + (uint)offset2 * -2 + 1);
          pbVar1 = pbVar1 + (uint)offset2 * -2 + 1;
        } while (bVar2);
        if ((!bVar4 && !bVar2) == bVar4) {
          if (local_14 == *(int *)(offset + 0x14)) {
            return 0;
          }
                    /* WARNING: Subroutine does not return */
          __stack_chk_fail();
        }
      }
    }
    if (i == 0) {
      printf(" Completed %s command successfully\n",(char *)&j);
    }
    else {
      printf(" Failed to do %s command\n",(char *)&j);
    }
    j = 0;
    k = 0;
    l = 0;
    m = 0;
    n = 0;
  } while( true );
}