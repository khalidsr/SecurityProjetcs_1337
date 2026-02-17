#include "out.h"




void main(void)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  byte local_78 [100];
  uint local_14;
  
  bVar4 = 0;
  local_14 = 0;
  fgets((char *)local_78,100,stdin);
  local_14 = 0;
  do {
    uVar2 = 0xffffffff;
    pbVar3 = local_78;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + (uint)bVar4 * -2 + 1;
    } while (bVar1 != 0);
    if (~uVar2 - 1 <= local_14) {
      printf((char *)local_78);
                    // WARNING: Subroutine does not return
      exit(0);
    }
    if (('@' < (char)local_78[local_14]) && ((char)local_78[local_14] < '[')) {
      local_78[local_14] = local_78[local_14] ^ 0x20;
    }
    local_14 = local_14 + 1;
  } while( true );
}

//////// ninja


int32_t main(int32_t argc, char** argv, char** envp)
{
    int32_t var_14 = 0;
    char var_78[0x64];
    fgets(&var_78, 0x64, __bss_start);
    int32_t var_14_1 = 0;
    
    while (true)
    {
        int32_t i = 0xffffffff;
        char (* edi_1)[0x64] = &var_78;
        
        while (i)
        {
            bool cond:0_1 = 0 != *edi_1;
            edi_1 = &(*edi_1)[1];
            i -= 1;
            
            if (!cond:0_1)
                break;
        }
        
        if (var_14_1 >= ~i - 1)
            break;
        
        if (var_78[var_14_1] > 0x40 && var_78[var_14_1] <= 0x5a)
            var_78[var_14_1] ^= 0x20;
        
        var_14_1 += 1;
    }
    
    printf(&var_78);
    exit(0);
    /* no return */
}


int32_t main(int32_t argc, char** argv, char** envp)
{
    char var_78[0x64];              // 100 byte buffer
    fgets(&var_78, 0x64, __bss_start);  // stdin
    
    // Convert lowercase to uppercase? Actually toggles case of A-Z
    for (int i = 0; var_78[i]; i++) {
        if (var_78[i] > 0x40 && var_78[i] <= 0x5a)  // 'A'-'Z'
            var_78[i] ^= 0x20;  // Toggles case (A->a, Z->z)
    }
    
    printf(&var_78);  // <--- FORMAT STRING VULNERABILITY
    exit(0);
}

