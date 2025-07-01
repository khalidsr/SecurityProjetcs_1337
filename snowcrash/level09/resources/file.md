## step 1

Logged in as `level09`. The home directory contains:

```
-rwsr-sr-x 1 flag09  level09 7640 Mar  5  2016 level09
----r--r-- 1 flag09  level09   26 Mar  5  2016 token
```

The token file is readable but contains non-printable characters or garbage data.

The level09 binary is a setuid executable owned by flag09.

```
./level09 abcd
aceg
```
After testing this binary file shows that is transforming each character of the input in some way likely increasing the ASCII value by the index.

## step 2

Reversing the Token
The token file contents appear scrambled:

```
cat token
f4kmm6p|=�p�n��DB�Du{��
```
Creating a script python to decode the token

```
import sys

encoded = sys.argv[1]
decoded = ""
for i in range(len(encoded)):
    decoded += chr(ord(encoded[i]) - i)
print(decoded)
```

Execute:

```
python /tmp/script.py "$(cat token)"
f3iji1ju5yuevaus41q1afiuq
```