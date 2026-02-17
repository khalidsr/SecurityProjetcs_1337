


void prog_timeout(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x80);
  (*pcVar1)();
  return;
}



void enable_timeout_cons(void)

{
  signal(0xe,prog_timeout);
  alarm(0x3c);
  return;
}



undefined4 main(void)

{
  int iVar1;
  char *pcVar2;
  byte bVar3;
  uint local_a4;
  char local_a0 [128];
  uint local_20;
  uint local_1c;
  long local_18;
  int local_14;
  
  bVar3 = 0;
  local_14 = fork();
  pcVar2 = local_a0;
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + ((uint)bVar3 * -2 + 1) * 4;
  }
  local_18 = 0;
  local_a4 = 0;
  if (local_14 == 0) {
    prctl(1,1);
    ptrace(PTRACE_TRACEME,0,0,0);
    puts("Give me some shellcode, k");
    gets(local_a0);
  }
  else {
    do {
      wait(&local_a4);
      local_20 = local_a4;
      if (((local_a4 & 0x7f) == 0) ||
         (local_1c = local_a4, '\0' < (char)(((byte)local_a4 & 0x7f) + 1) >> 1)) {
        puts("child is exiting...");
        return 0;
      }
      local_18 = ptrace(PTRACE_PEEKUSER,local_14,0x2c,0);
    } while (local_18 != 0xb);
    puts("no exec() for you");
    kill(local_14,9);
  }
  return 0;
}


/// binary ninja

int32_t enable_timeout_cons()
{
    signal(0xe, prog_timeout);
    return alarm(0x3c);
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    pid_t eax = fork();
    char buf[0x80];
    __builtin_memset(&buf, 0, 0x80);
    int32_t var_18 = 0;
    int32_t stat_loc = 0;
    
    if (eax)
    {
        while (true)
        {
            wait(&stat_loc);
            
            if (!(stat_loc & 0x7f) || ((stat_loc & 0x7f) + 1) >> 1 > 0)
            {
                puts("child is exiting...");
                break;
            }
            
            if (ptrace(PTRACE_PEEKUSER, eax, 0x2c, 0) != 0xb)
                continue;
            
            puts("no exec() for you");
            kill(eax, 9);
            break;
        }
    }
    else
    {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(&buf);
    }
    
    return 0;
}



``c
int32_t main() {
    pid_t eax = fork();
    char buf[0x80];  // 128-byte buffer
    
    if (eax) {  // Parent process
        while (true) {
            wait(&stat_loc);
            
            // Kill child if it tries execve() (syscall 0xb)
            if (ptrace(PTRACE_PEEKUSER, eax, 0x2c, 0) == 0xb) {
                puts("no exec() for you");
                kill(eax, 9);
                break;
            }
        }
    }
    else {  // Child process
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(&buf);  //  Buffer overflow!
    }
}