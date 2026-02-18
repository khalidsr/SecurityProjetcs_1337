#include "out.h"


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
                    // WARNING: Subroutine does not return
    __stack_chk_fail();
  }
  return;
}



undefined8 main(int param_1,undefined8 *param_2)

{
  char cVar1;
  int __fd;
  int iVar2;
  FILE *pFVar3;
  FILE *__stream;
  ulong uVar4;
  char *pcVar5;
  long in_FS_OFFSET;
  byte bVar6;
  char local_79;
  char local_78 [104];
  long local_10;
  
  bVar6 = 0;
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_79 = -1;
  if (param_1 != 2) {
    printf("Usage: %s filename\n",*param_2);
  }
  pFVar3 = fopen("./backups/.log","w");
  if (pFVar3 == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n","./backups/.log");
                    // WARNING: Subroutine does not return
    exit(1);
  }
  log_wrapper(pFVar3,"Starting back up: ",param_2[1]);
  __stream = fopen((char *)param_2[1],"r");
  if (__stream == (FILE *)0x0) {
    printf("ERROR: Failed to open %s\n",param_2[1]);
                    // WARNING: Subroutine does not return
    exit(1);
  }
  builtin_strncpy(local_78,"./backups/",0xb);
  uVar4 = 0xffffffffffffffff;
  pcVar5 = local_78;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + (ulong)bVar6 * -2 + 1;
  } while (cVar1 != '\0');
  strncat(local_78,(char *)param_2[1],99 - (~uVar4 - 1));
  __fd = open(local_78,0xc1,0x1b0);
  if (__fd < 0) {
    printf("ERROR: Failed to open %s%s\n","./backups/",param_2[1]);
                    // WARNING: Subroutine does not return
    exit(1);
  }
  while( true ) {
    iVar2 = fgetc(__stream);
    local_79 = (char)iVar2;
    if (local_79 == -1) break;
    write(__fd,&local_79,1);
  }
  log_wrapper(pFVar3,"Finished back up ",param_2[1]);
  fclose(__stream);
  close(__fd);
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    // WARNING: Subroutine does not return
    __stack_chk_fail();
  }
  return 0;
}

/////////// ninja 

int64_t log_wrapper(FILE* arg1, char* arg2, char* arg3)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    char var_118[0x108];
    strcpy(&var_118, arg2);
    int64_t i = -1;
    char (* rdi_1)[0x108] = &var_118;
    
    while (i)
    {
        bool cond:0_1 = 0 != *rdi_1;
        rdi_1 = &(*rdi_1)[1];
        i -= 1;
        
        if (!cond:0_1)
            break;
    }
    
    int64_t i_1 = -1;
    char (* rdi_2)[0x108] = &var_118;
    
    while (i_1)
    {
        bool cond:1_1 = 0 != *rdi_2;
        rdi_2 = &(*rdi_2)[1];
        i_1 -= 1;
        
        if (!cond:1_1)
            break;
    }
    
    snprintf(&var_118[~i_1 - 1], 0xfe - (~i - 1), arg3);
    var_118[strcspn(&var_118, "\n")] = 0;
    fprintf(arg1, "LOG: %s\n", &var_118, "LOG: %s\n");
    int64_t result = rax ^ *(fsbase + 0x28);
    
    if (!result)
        return result;
    
    __stack_chk_fail();
    /* no return */
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    void* fsbase;
    int64_t rax = *(fsbase + 0x28);
    char buf = 0xff;
    int32_t var_80 = 0xffffffff;
    
    if (argc != 2)
        printf("Usage: %s filename\n", *argv);
    
    FILE* rax_4 = fopen("./backups/.log", "w");
    
    if (!rax_4)
    {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
        /* no return */
    }
    
    log_wrapper(rax_4, "Starting back up: ", argv[1]);
    FILE* fp = fopen(argv[1], "r");
    
    if (!fp)
    {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
        /* no return */
    }
    
    int64_t file;
    __builtin_strncpy(&file, "./backups/", 0xb);
    int64_t i = -1;
    int64_t* rdi_2 = &file;
    
    while (i)
    {
        bool cond:0_1 = 0 != *rdi_2;
        rdi_2 += 1;
        i -= 1;
        
        if (!cond:0_1)
            break;
    }
    
    strncat(&file, argv[1], 0x63 - (~i - 1));
    int32_t fd = open(&file, 0xc1, 0x1b0);
    
    if (fd < 0)
    {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
        /* no return */
    }
    
    while (true)
    {
        buf = fgetc(fp);
        
        if (buf == 0xff)
            break;
        
        write(fd, &buf, 1);
    }
    
    log_wrapper(rax_4, "Finished back up ", argv[1]);
    fclose(fp);
    close(fd);
    
    if (rax == *(fsbase + 0x28))
        return 0;
    
    __stack_chk_fail();
    /* no return */
}



///// simplified code 


void log_wrapper(FILE *logfile, char *msg, char *filename) {
    char buffer[264];  // 0x108 = 264 bytes
    strcpy(buffer, msg);  // BUFFER OVERFLOW!
    
    // Append filename to buffer
    strncat(buffer, filename, 254 - strlen(msg));
    
    // Remove newline if present
    buffer[strcspn(buffer, "\n")] = 0;
    
    // Write to log
    fprintf(logfile, "LOG: %s\n", buffer);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    
    // Open log file
    FILE *logfile = fopen("./backups/.log", "w");
    if (!logfile) {
        printf("ERROR: Failed to open ./backups/.log\n");
        return 1;
    }
    
    log_wrapper(logfile, "Starting back up: ", argv[1]);
    
    // Open source file
    FILE *source = fopen(argv[1], "r");
    if (!source) {
        printf("ERROR: Failed to open %s\n", argv[1]);
        return 1;
    }
    
    // Create backup path: "./backups/" + filename
    char backup_path[100];  // Actually defined as int64_t file (8 bytes?!)
    strncpy(backup_path, "./backups/", 11);
    strncat(backup_path, argv[1], 99 - strlen(backup_path));
    
    // Create backup file
    int fd = open(backup_path, O_CREAT | O_WRONLY, 0x1b0);  // 0xc1 = O_CREAT|O_WRONLY
    
    // Copy file byte by byte
    int c;
    while ((c = fgetc(source)) != EOF) {
        write(fd, &c, 1);
    }
    
    log_wrapper(logfile, "Finished back up ", argv[1]);
    fclose(source);
    close(fd);
    return 0;
}