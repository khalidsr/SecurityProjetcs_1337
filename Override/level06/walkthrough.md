level06@OverRide:~$ python -c "
> username = 'abcdef'
> serial = (ord(username[3]) ^ 0x1337) + 0x5eeded
> for c in username:
>     serial += (ord(c) ^ serial) % 0x539
> print 'Username:', username
> print 'Serial:', serial
> "
Username: abcdef
Serial: 6232802

# Level 06

## Overview

This level implements a login authentication system with a custom serial verification algorithm. The program prompts for a username and serial number, then performs a deterministic calculation on the username to validate the serial. If the serial matches the calculated value, a shell is spawned.

Unlike previous levels, no memory corruption vulnerability exists — this is a reverse engineering / algorithm cracking challenge.

### The Challenge

Key vulnerability: The serial is mathematically derived from the username. If we can reverse the algorithm, we can generate a valid serial for any username > 5 characters.

# The Algorithm
The hash is calculated as follows:

1. Start with:
    hash = (login[3] ^ 0x1337) + 0x5eeded

2. For each character in login:
    hash += (login[i] ^ hash) % 0x539

3. Compare result with input serial


# Step 1: Understand the Constants
Constant	Value	Meaning
0x1337	4919	XOR mask
0x5eeded	6222317	Initial additive constant
0x539	1337	Modulus for hash update

# Step 2: Generate a Valid Serial

We can implement the algorithm in Python to generate a serial for any username:

```python
def generate_serial(username):
    if len(username) <= 5:
        return None
    
    # Start with initial value
    serial = (ord(username[3]) ^ 0x1337) + 0x5eeded
    
    # Loop through each character
    for c in username:
        serial += (ord(c) ^ serial) % 0x539
    
    return serial
```

# Step 3: Execute the Exploit

```bash
level06@OverRide:~$ ./level06 
***********************************
*		level06		  *
***********************************
-> Enter Login: abcdef
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6232802
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass 
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
$ 
```

