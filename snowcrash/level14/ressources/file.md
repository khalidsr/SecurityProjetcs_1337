
## step 1
Logged in as `level14`. The home directory contains:

No obvious files or SUID binaries owned by flag14 were found using find.
```
level14@SnowCrash:~$ ls -la

```
## step 2

Since no useful files are present in the home directory, we analyze the system binary /bin/getflag.
```
gdb /bin/getflag
```
* Disassembly Partial:
```
call ptrace@plt     ; anti-debugging check
call getuid@plt     ; identity check
cmp  eax, 3014      ; compare UID to required one (flag14)
```
If getuid() doesn’t return 3014, getflag refuses to run like the level13 .

## step 3

 - Exploit Strategy

But should  Bypass ptrace anti-debugging
Use a syscall catchpoint in GDB:
```
(gdb) catch syscall ptrace
(gdb) commands
> set $eax = 0
> continue
> end
```
This simulates a successful ptrace call (return value 0), allowing GDB debugging to proceed.

- Spoof getuid() Return Value
After bypassing ptrace, break on getuid():

```
(gdb) break getuid
(gdb) run
```

When the breakpoint is hit:

```
(gdb) step
(gdb) print $eax        # Actual UID = 2014
(gdb) set $eax = 3014   # Spoof UID to that of flag14
You can confirm the target UID by running:
```
- Let the binary continue:
```
(gdb) step 
```
This tricks /bin/getflag into thinking it is being run by flag14.
```
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```