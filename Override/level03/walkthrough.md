## Level 03

# Overview

This level implements a simple password‑checking mechanism. The program asks for an integer, performs a subtraction from a fixed magic number, and uses the difference as an XOR key to decrypt a hard‑coded string. If the decrypted string matches "Congratulations!", a shell is spawned.

# The Challenge

Key vulnerability: The program’s behaviour is entirely deterministic if we can supply a user_input that makes the difference diff fall into the allowed ranges. The correct diff is the one that, when used as an XOR key, transforms the obfuscated string into "Congratulations!".

## Exploitation Process

# Step 1: Determine the correct XOR key
The encrypted string is:
"Q}|usfg~sf{}|a3"`

The target plaintext is:
"Congratulations!"

Because XOR is reversible and commutative, the key can be obtained by XORing any character of the encrypted string with the corresponding character of the target.

'Q' (ASCII 81)

'C' (ASCII 67)

key = 81 XOR 67 = 18 (decimal)  = 0x12

We can verify with another character (e.g., '}' (125) XOR 'g' (103) = 18 as well).
Thus, the required XOR key is 18.

# Step 2: Find the input that yields diff = 18

From the test() function:
```
    diff = magic_number - user_input
    magic_number = 0x1337d00d  (decimal 322424845)
```

# Step 3: Execute the exploit
Run the program and supply this integer:
```
    level03@OverRide:~$ ./level03
    Password:322424827
    $ whoami
    level04
    $ cat /home/users/level04/.pass
    kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

