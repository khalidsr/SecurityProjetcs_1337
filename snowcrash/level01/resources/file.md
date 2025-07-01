## Objective

Gain access to the `flag01` user account and retrieve the flag using the `getflag` command.

---

## Step1

Logged in as `level01`. No flag or obvious credentials in the home directory.

Check `/etc/passwd` to view system users and confirm that `flag01` exists:

```
    cat /etc/passwd
    flag00:x:3000:3000::/home/flag/flag00:/bin/bash
    flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

We save the hashed password line to a file called pass: 42hDRfypTqqnw
Then use john (John the Ripper) to crack the password:
john pass.txt

```
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 128/128 SSE2])
...
abcdefg          (?)
```
to Confirm :
john --show pass
``` Output:
    ?:abcdefg
```
Execute getflag to receive the token:
flag01@SnowCrash:~$ getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf


     
