#include "out.h"



int decrypt(EVP_PKEY_CTX *ctx,uchar *out,size_t *outlen,uchar *in,size_t inlen)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  int in_GS_OFFSET;
  bool bVar6;
  bool bVar7;
  uint local_2c;
  byte local_21 [17];
  int local_10;
  
  local_10 = *(int *)(in_GS_OFFSET + 0x14);
  local_21[0] = 0x51;
  local_21[1] = 0x7d;
  local_21[2] = 0x7c;
  local_21[3] = 0x75;
  local_21[4] = 0x60;
  local_21[5] = 0x73;
  local_21[6] = 0x66;
  local_21[7] = 0x67;
  local_21[8] = 0x7e;
  local_21[9] = 0x73;
  local_21[10] = 0x66;
  local_21[0xb] = 0x7b;
  local_21[0xc] = 0x7d;
  local_21[0xd] = 0x7c;
  local_21[0xe] = 0x61;
  local_21[0xf] = 0x33;
  local_21[0x10] = 0;
  uVar2 = 0xffffffff;
  pbVar4 = local_21;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
  } while (bVar1 != 0);
  local_2c = 0;
  while( true ) {
    bVar6 = local_2c < ~uVar2 - 1;
    bVar7 = local_2c == ~uVar2 - 1;
    if (!bVar6) break;
    local_21[local_2c] = (byte)ctx ^ local_21[local_2c];
    local_2c = local_2c + 1;
  }
  iVar3 = 0x11;
  pbVar4 = local_21;
  pbVar5 = (byte *)"Congratulations!";
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *pbVar4 < *pbVar5;
    bVar7 = *pbVar4 == *pbVar5;
    pbVar4 = pbVar4 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar7);
  if ((!bVar6 && !bVar7) == bVar6) {
    iVar3 = system("/bin/sh");
  }
  else {
    iVar3 = puts("\nInvalid Password");
  }
  if (local_10 == *(int *)(in_GS_OFFSET + 0x14)) {
    return iVar3;
  }
                    // WARNING: Subroutine does not return
  __stack_chk_fail();
}



void test(int param_1,int param_2)

{
  EVP_PKEY_CTX *pEVar1;
  uchar *in_stack_ffffffd8;
  size_t *in_stack_ffffffdc;
  uchar *in_stack_ffffffe0;
  size_t in_stack_ffffffe4;
  
  pEVar1 = (EVP_PKEY_CTX *)(param_2 - param_1);
  switch(pEVar1) {
  default:
    pEVar1 = (EVP_PKEY_CTX *)rand();
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x1:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x2:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x3:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x4:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x5:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x6:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x7:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x8:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x9:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x10:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x11:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x12:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x13:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x14:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    break;
  case (EVP_PKEY_CTX *)0x15:
    decrypt(pEVar1,in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
  }
  return;
}



// WARNING: Removing unreachable block (ram,0x08048868)

undefined4 main(void)

{
  uint __seed;
  
  __seed = time((time_t *)0x0);
  srand(__seed);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf();
  test();
  return 0;
}



// ninja

int32_t decrypt(char arg1)
{
    int32_t ebp;
    int32_t var_4 = ebp;
    int32_t edi;
    int32_t var_8 = edi;
    int32_t esi;
    int32_t var_c = esi;
    void* gsbase;
    int32_t eax = *(gsbase + 0x14);
    int32_t var_21;
    __builtin_strncpy(&var_21, "Q}|u`sfg~sf{}|a3", 0x11);
    int32_t var_50 = 0;
    int32_t* esp_1 = &var_50;
    int32_t var_30 = 0xffffffff;
    int32_t i = 0xffffffff;
    int32_t* edi_1 = &var_21;
    
    while (i)
    {
        bool cond:0_1 = 0 != *edi_1;
        edi_1 += 1;
        i -= 1;
        
        if (!cond:0_1)
            break;
    }
    
    int32_t var_2c = 0;
    bool c_1;
    bool z_1;
    
    while (true)
    {
        c_1 = var_2c < ~i - 1;
        z_1 = var_2c == ~i - 1;
        
        if (!c_1)
            break;
        
        *(&var_21 + var_2c) ^= arg1;
        var_2c += 1;
    }
    
    int32_t i_1 = 0x11;
    int32_t* esi_1 = &var_21;
    char* edi_2 = "Congratulations!";
    
    while (i_1)
    {
        char temp1_1 = *esi_1;
        char temp2_1 = *edi_2;
        c_1 = temp1_1 < temp2_1;
        z_1 = temp1_1 == temp2_1;
        esi_1 += 1;
        edi_2 = &edi_2[1];
        i_1 -= 1;
        
        if (!z_1)
            break;
    }
    
    int32_t result;
    
    if ((!z_1 && !c_1) - c_1)
    {
        esp_1[1] = "\nInvalid Password";
        result = puts();
    }
    else
    {
        esp_1[1] = "/bin/sh";
        result = system();
    }
    
    if (eax != *(gsbase + 0x14))
    {
        __stack_chk_fail();
    }
    
    esp_1[0x11];
    esp_1[0x12];
    esp_1[0x13];
    return result;
}

int32_t test(int32_t arg1, int32_t arg2)
{
    int32_t ecx_1 = arg2 - arg1;
    
    switch (ecx_1)
    {
        case 1:
        {
            return decrypt(ecx_1);
            break;
        }
        case 2:
        {
            return decrypt(ecx_1);
            break;
        }
        case 3:
        {
            return decrypt(ecx_1);
            break;
        }
        case 4:
        {
            return decrypt(ecx_1);
            break;
        }
        case 5:
        {
            return decrypt(ecx_1);
            break;
        }
        case 6:
        {
            return decrypt(ecx_1);
            break;
        }
        case 7:
        {
            return decrypt(ecx_1);
            break;
        }
        case 8:
        {
            return decrypt(ecx_1);
            break;
        }
        case 9:
        {
            return decrypt(ecx_1);
            break;
        }
        case 0x10:
        {
            return decrypt(ecx_1);
            break;
        }
        case 0x11:
        {
            return decrypt(ecx_1);
            break;
        }
        case 0x12:
        {
            return decrypt(ecx_1);
            break;
        }
        case 0x13:
        {
            return decrypt(ecx_1);
            break;
        }
        case 0x14:
        {
            return decrypt(ecx_1);
            break;
        }
        case 0x15:
        {
            return decrypt(ecx_1);
            break;
        }
    }
    
    return decrypt(rand());
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    int32_t __saved_ebp_1;
    int32_t __saved_ebp = __saved_ebp_1;
    int32_t entry_eax;
    int32_t var_34 = entry_eax;
    int32_t* esp_1 = &var_34;
    *esp_1;
    esp_1[1] = 0;
    esp_1[1] = time();
    srand();
    esp_1[1] = "***********************************";
    puts();
    esp_1[1] = "*\t\tlevel03\t\t**";
    puts();
    esp_1[1] = "***********************************";
    puts();
    esp_1[1] = "Password:";
    printf();
    esp_1[2] = &esp_1[8];
    esp_1[1] = &data_8048a85;
    __isoc99_scanf();
    int32_t eax_2 = esp_1[8];
    esp_1[2] = 0x1337d00d;
    esp_1[1] = eax_2;
    test();
    return 0;
}



void decrypt(int key) 
{
    char str[] = "Q}|u`sfg~sf{}|a3";  
    
    // XOR decrypt each character with the key
    for (int i = 0; i < strlen(str); i++) {
        str[i] = str[i] ^ key;
    }
    

    if (strcmp(str, "Congratulations!") == 0) {
        system("/bin/sh"); 
    } else {
        puts("Invalid Password");  
    }
}

void test(int user_input, int magic_number) 
{
    int diff = magic_number - user_input;
    
    if (diff >= 1 && diff <= 9 || diff >= 16 && diff <= 21) 
    {
        decrypt(diff);
    } 
    else 
    {
        decrypt(rand()); 
    }
}

int main() 
{
    srand(time(0));  
    
    printf("Password:");
    int user_input;
    scanf("%d", &user_input); 
    
    test(user_input, 0x1337d00d);
    return 0;
}