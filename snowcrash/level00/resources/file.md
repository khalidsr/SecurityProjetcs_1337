## Objective
Find and decrypt the password for user `flag00` to progress to the next level.

## Step 1

You start as the user `level00`. Listing the home directory shows only typical shell configuration files:

```
level00@SnowCrash:~$ ls -la
total 12
dr-xr-x---+ 1 level00 level00  100 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-xr-x---+ 1 level00 level00  220 Apr  3  2012 .bash_logout
-r-xr-x---+ 1 level00 level00 3518 Aug 30  2015 .bashrc
-r-xr-x---+ 1 level00 level00  675 Apr  3  2012 .profile
```

1. **Finding flag00 files**:
 - Searching for files owned by `flag00` reveals an interesting file:
   ```
   find / -user flag00 2> /dev/null
   /usr/sbin/john
   /rofs/usr/sbin/john
   ```
 - Both files contain the same encrypted string: `cdiiddwpgswtgt`

2. **Attempting to use the password**:
 - Directly using `getflag` as level00 doesn't work:
   ```
   Check flag.Here is your token : 
   Nope there is no token here for you sorry. Try again :)
   ```
 - Trying to switch user to `flag00` with the found string fails initially.

### Decryption
- The string `cdiiddwpgswtgt` appears to be encoded.
- Using decode.f and after testing various cipher techniques, **ROT15 decryption** reveals the correct password:
- Decrypted: `nottoohardhere`

### Solution
1. Switch to user `flag00` using the decrypted password:
``` su flag00
Password: nottoohardhere
``` 
2. Execute `getflag` to receive the token:
``` flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```
