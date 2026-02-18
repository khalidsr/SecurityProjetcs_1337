#include "out.h"



undefined4 get_unum(void)

{
  undefined4 local_10 [3];
  
  local_10[0] = 0;
  fflush(stdout);
  __isoc99_scanf(&DAT_08048ad0,local_10);
  clear_stdin();
  return local_10[0];
}



void prog_timeout(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x80);
  (*pcVar1)();
  return;
}



undefined4 store_number(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  printf(" Number: ");
  uVar1 = get_unum();
  printf(" Index: ");
  uVar2 = get_unum();
  if ((uVar2 % 3 == 0) || (uVar1 >> 0x18 == 0xb7)) {
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    uVar3 = 1;
  }
  else {
    *(uint *)(uVar2 * 4 + param_1) = uVar1;
    uVar3 = 0;
  }
  return uVar3;
}



undefined4 read_number(int param_1)

{
  int iVar1;
  
  printf(" Index: ");
  iVar1 = get_unum();
  printf(" Number at data[%u] is %u\n",iVar1,*(undefined4 *)(iVar1 * 4 + param_1));
  return 0;
}



undefined4 main(undefined4 param_1,int *param_2,int *param_3)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  char *pcVar7;
  byte *pbVar8;
  int in_GS_OFFSET;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  byte bVar12;
  int *local_1c8;
  int *local_1c4;
  undefined4 local_1bc [100];
  undefined4 local_2c;
  byte local_28 [20];
  int local_14;
  
  bVar12 = 0;
  local_1c4 = param_2;
  local_1c8 = param_3;
  local_14 = *(int *)(in_GS_OFFSET + 0x14);
  local_2c = 0;
  local_28[0] = 0;
  local_28[1] = 0;
  local_28[2] = 0;
  local_28[3] = 0;
  local_28[4] = 0;
  local_28[5] = 0;
  local_28[6] = 0;
  local_28[7] = 0;
  local_28[8] = 0;
  local_28[9] = 0;
  local_28[10] = 0;
  local_28[0xb] = 0;
  local_28[0xc] = 0;
  local_28[0xd] = 0;
  local_28[0xe] = 0;
  local_28[0xf] = 0;
  local_28[0x10] = 0;
  local_28[0x11] = 0;
  local_28[0x12] = 0;
  local_28[0x13] = 0;
  puVar6 = local_1bc;
  for (iVar3 = 100; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  for (; *local_1c4 != 0; local_1c4 = local_1c4 + 1) {
    uVar4 = 0xffffffff;
    pcVar7 = (char *)*local_1c4;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + (uint)bVar12 * -2 + 1;
    } while (cVar1 != '\0');
    memset((void *)*local_1c4,0,~uVar4 - 1);
  }
  for (; *local_1c8 != 0; local_1c8 = local_1c8 + 1) {
    uVar4 = 0xffffffff;
    pcVar7 = (char *)*local_1c8;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + (uint)bVar12 * -2 + 1;
    } while (cVar1 != '\0');
    memset((void *)*local_1c8,0,~uVar4 - 1);
  }
  puts(
      "----------------------------------------------------\n  Welcome to wil\'s crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------------------------\n"
      );
  do {
    printf("Input command: ");
    local_2c = 1;
    fgets((char *)local_28,0x14,stdin);
    uVar4 = 0xffffffff;
    pbVar5 = local_28;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      bVar2 = *pbVar5;
      pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
    } while (bVar2 != 0);
    uVar4 = ~uVar4;
    bVar9 = uVar4 == 1;
    bVar11 = uVar4 == 2;
    *(undefined1 *)((int)&local_2c + uVar4 + 2) = 0;
    iVar3 = 5;
    pbVar5 = local_28;
    pbVar8 = (byte *)"store";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar9 = *pbVar5 < *pbVar8;
      bVar11 = *pbVar5 == *pbVar8;
      pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
      pbVar8 = pbVar8 + (uint)bVar12 * -2 + 1;
    } while (bVar11);
    bVar10 = false;
    bVar9 = (!bVar9 && !bVar11) == bVar9;
    if (bVar9) {
      local_2c = store_number(local_1bc);
    }
    else {
      iVar3 = 4;
      pbVar5 = local_28;
      pbVar8 = &DAT_08048d61;
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        bVar10 = *pbVar5 < *pbVar8;
        bVar9 = *pbVar5 == *pbVar8;
        pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
        pbVar8 = pbVar8 + (uint)bVar12 * -2 + 1;
      } while (bVar9);
      bVar11 = false;
      bVar9 = (!bVar10 && !bVar9) == bVar10;
      if (bVar9) {
        local_2c = read_number(local_1bc);
      }
      else {
        iVar3 = 4;
        pbVar5 = local_28;
        pbVar8 = &DAT_08048d66;
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar11 = *pbVar5 < *pbVar8;
          bVar9 = *pbVar5 == *pbVar8;
          pbVar5 = pbVar5 + (uint)bVar12 * -2 + 1;
          pbVar8 = pbVar8 + (uint)bVar12 * -2 + 1;
        } while (bVar9);
        if ((!bVar11 && !bVar9) == bVar11) {
          if (local_14 == *(int *)(in_GS_OFFSET + 0x14)) {
            return 0;
          }
                    // WARNING: Subroutine does not return
          __stack_chk_fail();
        }
      }
    }
    if (local_2c == 0) {
      printf(" Completed %s command successfully\n",local_28);
    }
    else {
      printf(" Failed to do %s command\n",local_28);
    }
    local_28[0] = 0;
    local_28[1] = 0;
    local_28[2] = 0;
    local_28[3] = 0;
    local_28[4] = 0;
    local_28[5] = 0;
    local_28[6] = 0;
    local_28[7] = 0;
    local_28[8] = 0;
    local_28[9] = 0;
    local_28[10] = 0;
    local_28[0xb] = 0;
    local_28[0xc] = 0;
    local_28[0xd] = 0;
    local_28[0xe] = 0;
    local_28[0xf] = 0;
    local_28[0x10] = 0;
    local_28[0x11] = 0;
    local_28[0x12] = 0;
    local_28[0x13] = 0;
  } while( true );
}


///////// binary ninja




int32_t store_number(int32_t arg1)
{
    int32_t var_14 = 0;
    int32_t var_10 = 0;
    printf(" Number: ");
    int32_t eax = get_unum();
    printf(" Index: ");
    int32_t eax_1 = get_unum();
    
    if (eax_1 % 3 && eax >> 0x18 != 0xb7)
    {
        *((eax_1 << 2) + arg1) = eax;
        return 0;
    }
    
    puts(" *** ERROR! ***");
    puts("   This index is reserved for wil!");
    puts(" *** ERROR! ***");
    return 1;
}

int32_t read_number(int32_t arg1)
{
    int32_t var_10 = 0;
    printf(" Index: ");
    int32_t eax = get_unum();
    printf(" Number at data[%u] is %u\n", eax, *((eax << 2) + arg1));
    return 0;
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    char** argv_1 = argv;
    char** envp_1 = envp;
    void* gsbase;
    int32_t eax_2 = *(gsbase + 0x14);
    int32_t var_2c_1;
    __builtin_memset(&var_2c_1, 0, 0x18);
    void var_1bc;
    __builtin_memset(&var_1bc, 0, 0x190);
    int32_t var_1dc;
    size_t fp;
    
    while (*argv_1)
    {
        int32_t i = 0xffffffff;
        char* edi_1 = *argv_1;
        
        while (i)
        {
            bool cond:0_1 = 0 != *edi_1;
            edi_1 = &edi_1[1];
            i -= 1;
            
            if (!cond:0_1)
                break;
        }
        
        fp = ~i - 1;
        var_1dc = 0;
        memset(*argv_1, var_1dc, fp);
        argv_1 = &argv_1[1];
    }
    
    while (*envp_1)
    {
        int32_t i_1 = 0xffffffff;
        char* edi_2 = *envp_1;
        
        while (i_1)
        {
            bool cond:1_1 = 0 != *edi_2;
            edi_2 = &edi_2[1];
            i_1 -= 1;
            
            if (!cond:1_1)
                break;
        }
        
        fp = ~i_1 - 1;
        var_1dc = 0;
        memset(*envp_1, var_1dc, fp);
        envp_1 = &envp_1[1];
    }
    
    puts("----------------------------------------------------\n  Welcome to wil's crappy number "
    "storage service!   \n----------------------------------------------------\n Commands:                                          "
    "    store - store a number into the data storage    \n    read  - read a number from the data "
    "storage     \n    quit  ");
    
    while (true)
    {
        printf("Input command: ", var_1dc, fp);
        int32_t var_2c_2 = 1;
        fp = stdin;
        int32_t buf;
        fgets(&buf, 0x14, fp);
        int32_t i_2 = 0xffffffff;
        int32_t* edi_3 = &buf;
        
        while (i_2)
        {
            bool cond:6_1 = 0 != *edi_3;
            edi_3 += 1;
            i_2 -= 1;
            
            if (!cond:6_1)
                break;
        }
        
        bool c_1 = ~i_2 - 1 < 1;
        bool z_1 = ~i_2 == 2;
        *(&buf + ~i_2 - 2) = 0;
        int32_t i_3 = 5;
        int32_t* esi_1 = &buf;
        char* edi_4 = "store";
        
        while (i_3)
        {
            char temp1_1 = *esi_1;
            char temp2_1 = *edi_4;
            c_1 = temp1_1 < temp2_1;
            z_1 = temp1_1 == temp2_1;
            esi_1 += 1;
            edi_4 = &edi_4[1];
            i_3 -= 1;
            
            if (!z_1)
                break;
        }
        
        bool c_2 = false;
        bool z_2 = !((!z_1 && !c_1) - c_1);
        
        if (!z_2)
        {
            int32_t i_4 = 4;
            int32_t* esi_2 = &buf;
            char* edi_5 = "read";
            
            while (i_4)
            {
                char temp3_1 = *esi_2;
                char temp4_1 = *edi_5;
                c_2 = temp3_1 < temp4_1;
                z_2 = temp3_1 == temp4_1;
                esi_2 += 1;
                edi_5 = &edi_5[1];
                i_4 -= 1;
                
                if (!z_2)
                    break;
            }
            
            bool c_3 = false;
            bool z_3 = !((!z_2 && !c_2) - c_2);
            
            if (!z_3)
            {
                int32_t i_5 = 4;
                int32_t* esi_3 = &buf;
                char* edi_6 = "quit";
                
                while (i_5)
                {
                    char temp5_1 = *esi_3;
                    char temp6_1 = *edi_6;
                    c_3 = temp5_1 < temp6_1;
                    z_3 = temp5_1 == temp6_1;
                    esi_3 += 1;
                    edi_6 = &edi_6[1];
                    i_5 -= 1;
                    
                    if (!z_3)
                        break;
                }
                
                if (!((!z_3 && !c_3) - c_3))
                {
                    if (eax_2 == *(gsbase + 0x14))
                        return 0;
                    
                    __stack_chk_fail();
                    /* no return */
                }
            }
            else
            {
                read_number(&var_1bc);
                var_2c_2 = 0;
            }
        }
        else
            var_2c_2 = store_number(&var_1bc);
        
        if (!var_2c_2)
        {
            var_1dc = &buf;
            printf(" Completed %s command successfully\n", var_1dc);
        }
        else
        {
            var_1dc = &buf;
            printf(" Failed to do %s command\n", var_1dc);
        }
        
        __builtin_memset(&buf, 0, 0x14);
    }
}
 ////// Simplified code 

 int buffer[100];  // Actually 100 * 4 = 400 bytes at &var_1bc

int store_number(int *buffer) {
    printf(" Number: ");
    int number = get_unum(); 
    printf(" Index: ");
    int index = get_unum();   
    
    // CRITICAL CHECK: index % 3 != 0 AND number >> 24 != 0xb7
    if ((index % 3 != 0) && ((number >> 24) != 0xb7)) {
        buffer[index] = number; 
        return 0;
    } else {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        return 1;
    }
}

int read_number(int *buffer) {
    printf(" Index: ");
    int index = get_unum();
    printf(" Number at data[%u] is %u\n", index, buffer[index]);  // READ ANYWHERE!
    return 0;
}

int main() {
    int buffer[100];  // Data storage array
    memset(buffer, 0, 400);  // Clear buffer
    

    
    puts("Welcome to wil's crappy number storage service!");
    puts("Commands: store, read, quit");
    
    while (1) {
        printf("Input command: ");
        char cmd[20];
        fgets(cmd, 20, stdin);
        cmd[strcspn(cmd, "\n")] = 0;
        
        if (strcmp(cmd, "store") == 0) {
            store_number(buffer);
        } else if (strcmp(cmd, "read") == 0) {
            read_number(buffer);
        } else if (strcmp(cmd, "quit") == 0) {
            return 0;
        } else {
            printf("Invalid command\n");
        }
    }
}