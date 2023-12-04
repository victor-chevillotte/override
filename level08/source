void log_wrapper(FILE *param_1,char *param_2,char *param_3)
{
  char cVar1;
  size_t sVar2;
  ulong uVar3;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  undefined8 local_120;
  char local_118 [264];
  long local_10;
  
  bVar6 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_120 = param_1;
  strcpy(local_118,param_2);
  uVar3 = 0xffffffffffffffff;
  pcVar5 = local_118;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  uVar4 = 0xffffffffffffffff;
  pcVar5 = local_118;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  snprintf(local_118 + (~uVar4 - 1),0xfe - (~uVar3 - 1),param_3);
  sVar2 = strcspn(local_118,"\n");
  local_118[sVar2] = '\0';
  fprintf(local_120,"LOG: %s\n",local_118);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


int main(int ac,char **av)
{
  int __fd;
  int iVar1;
  FILE *log_file;
  FILE *__stream;
  ulong uVar2;
  undefined8 *puVar3;
  long in_FS_OFFSET;
  byte bVar4;
  char d;
  undefined8 backup_str;
  undefined2 local_70;
  char local_6e;
  long local_10;
  char c;
  
  bVar4 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  d = -1;
  if (ac != 2) {
    printf("Usage: %s filename\n",*av);
  }
  log_file = fopen("./backups/.log","w");
  if (log_file == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n","./backups/.log");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  log_wrapper(log_file,"Starting back up: ",av[1]);
  __stream = fopen(av[1],"r");
  if (__stream == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n",av[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  backup_str._0_1_ = '.';
  backup_str._1_1_ = '/';
  backup_str._2_1_ = 'b';
  backup_str._3_1_ = 'a';
  backup_str._4_1_ = 'c';
  backup_str._5_1_ = 'k';
  backup_str._6_1_ = 'u';
  backup_str._7_1_ = 'p';
  local_70._0_1_ = 's';
  local_70._1_1_ = '/';
  local_6e = '\0';
  uVar2 = 0xffffffffffffffff;
  puVar3 = &backup_str;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    c = *(char *)puVar3;
    puVar3 = (undefined8 *)((long)puVar3 + (ulong)bVar4 * -2 + 1);
  } while (c != '\0');
  strncat((char *)&backup_str,av[1],99 - (~uVar2 - 1));
  __fd = open((char *)&backup_str,0xc1,0x1b0);
  if (__fd < 0) {
    printf("ERROR: Failed to open %s%s\n","./backups/",av[1]);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  while( true ) {
    iVar1 = fgetc(__stream);
    d = (char)iVar1;
    if (d == -1) break;
    write(__fd,&d,1);
  }
  log_wrapper(log_file,"Finished back up ",av[1]);
  fclose(__stream);
  close(__fd);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}