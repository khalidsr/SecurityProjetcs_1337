## step 1
Logged in as `level13`. The home directory contains:

```
-rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
```
./level13
UID 2013 started us but we we expect 4242

The program checks if the UID of the user running it is 4242. If not, it exits.

Using strings level13, we see:

UID %d started us but we we expect %d
your token is %s


## step 2

* Exploit with GDB
The binary is SUID, which means it runs with flag13's privileges, but we must fool the program into thinking our UID is 4242.

- Launch GDB
```
gdb ./level13
```
-  Break on getuid
```
(gdb) break getuid
```
- Force return value of getuid to 4242
```
(gdb) commands
> return (unsigned int)4242
> continue
> end
```
- Run the binary
```
(gdb) run
```
- output 
```
your token is 2A31L79asukciNyi8uppkEuSx

```