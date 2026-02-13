int32_t auth(char* arg1, int32_t arg2)
{
    int32_t __saved_ebp_1;
    int32_t __saved_ebp = __saved_ebp_1;
    char* var_28 = &data_8048a63;
    char* var_2c = arg1;
    arg1[strcspn(var_2c, var_28)] = 0;
    size_t var_28_1 = 0x20;
    var_2c = arg1;
    size_t eax_4 = strnlen(var_2c, var_28_1);
    size_t var_30 = eax_4;
    size_t* esp_1 = &var_30;
    *esp_1;
    
    if (eax_4 <= 5)
        return 1;
    
    esp_1[4] = 0;
    esp_1[3] = 1;
    esp_1[2] = 0;
    esp_1[1] = nullptr;
    
    if (ptrace() == 0xffffffff)
    {
        esp_1[1] = "\x1b[32m.---------------------------.";
        puts();
        esp_1[1] = "\x1b[31m| !! TAMPERING DETECTED !!  |";
        puts();
        esp_1[1] = "\x1b[32m'---------------------------'";
        puts();
        return 1;
    }
    
    int32_t var_14_1 = (arg1[3] ^ 0x1337) + 0x5eeded;
    
    for (void* i = nullptr; i < eax_4; i += 1)
    {
        if (*(i + arg1) <= 0x1f)
            return 1;
        
        var_14_1 += (*(i + arg1) ^ var_14_1) % 0x539;
    }
    
    if (arg2 == var_14_1)
        return 0;
    
    return 1;
}

int32_t main(int32_t argc, char** argv, char** envp)
{
    int32_t __saved_ebp_1;
    int32_t __saved_ebp = __saved_ebp_1;
    char** argv_1 = argv;
    void* gsbase;
    int32_t var_14 = *(gsbase + 0x14);
    int32_t var_64 = 0;
    int32_t* esp_1 = &var_64;
    *esp_1;
    esp_1[1] = "***********************************";
    puts();
    esp_1[1] = "*\t\tlevel06\t\t  *";
    puts();
    esp_1[1] = "***********************************";
    puts();
    esp_1[1] = "-> Enter Login: ";
    printf();
    esp_1[3] = stdin;
    esp_1[2] = 0x20;
    esp_1[1] = &esp_1[0xc];
    fgets();
    esp_1[1] = "***********************************";
    puts();
    esp_1[1] = "***** NEW ACCOUNT DETECTED ********";
    puts();
    esp_1[1] = "***********************************";
    puts();
    esp_1[1] = "-> Enter Serial: ";
    printf();
    esp_1[2] = &esp_1[0xb];
    esp_1[1] = &data_8048a60;
    __isoc99_scanf();
    esp_1[2] = esp_1[0xb];
    esp_1[1] = &esp_1[0xc];
    int32_t result;
    
    if (auth())
        result = 1;
    else
    {
        esp_1[1] = "Authenticated!";
        puts();
        esp_1[1] = "/bin/sh";
        system();
        result = 0;
    }
    
    if (esp_1[0x14] == *(gsbase + 0x14))
        return result;
    
    __stack_chk_fail();
    /* no return */
}


int32_t auth(char* login, int32_t serial)
{
    // Remove newline
    login[strcspn(login, "\n")] = 0;
    
    // Login must be > 5 characters
    if (strnlen(login, 32) <= 5)
        return 1;
    
    // Anti-debugging ptrace() check
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
    {
        puts("!! TAMPERING DETECTED !!");
        return 1;
    }
    

    int hash = (login[3] ^ 0x1337) + 0x5eeded;
    
    // Hash calculation loop
    for (int i = 0; i < strlen(login); i++)
    {
        if (login[i] <= 0x1f)  // No control characters
            return 1;
        
        hash += (login[i] ^ hash) % 0x539;  // 0x539 = 1337 decimal
    }
    
    if (serial == hash)
        return 0;
    
    return 1;
}

int main()
{
    char login[32];
    int serial;
    
    puts("-> Enter Login: ");
    fgets(login, 32, stdin);
    
    puts("-> Enter Serial: ");
    scanf("%d", &serial);
    
    if (auth(login, serial) == 0)
    {
        puts("Authenticated!");
        system("/bin/sh");
    }
    
    return 0;
}