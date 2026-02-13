# Level 00

## Overview

This level presents a basic password authentication challenge that requires reversing a simple integer comparison.

## The Challenge

The program prompts for a password and compares it against a hardcoded value before granting access to a shell.

## Analysis

```c
__isoc99_scanf(&DAT_08048636, local_14);
if (local_14[0] != 0x149c) 
{
    puts("\nInvalid Password!");
}
else 
{
    puts("\nAuthenticated!");
    system("/bin/sh");
}
```

### Finding the Password
The program checks if the input equals `0x149c` (hexadecimal). Converting to decimal:
- `0x149c` = 5276

The password is simply the decimal representation of this hex value.

## Solution
```
    level00@OverRide:~$ ./level00 
    ***********************************
    * 	     -Level00 -		  *
    ***********************************
    Password:5421

    Invalid Password!
    level00@OverRide:~$ ./level00 
    ***********************************
    * 	     -Level00 -		  *
    ***********************************
    Password:5276

    Authenticated!
    $ whoami 
    level01
    $ 
```
- Simple integer comparison for authentication
- Hex to decimal conversion: `0x149c` → `5276`
- Basic reverse engineering of compiled C code