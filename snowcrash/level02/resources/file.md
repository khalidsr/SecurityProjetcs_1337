
## Steps
```
level02@SnowCrash:~$ ls
level02.pcap
```
The file is a .pcap, which typically contains network packet capture data.


We transfer the .pcap file to our host machine for deeper analysis:
```
scp -P 4242 level02@10.11.45.238:/home/user/level02/level02.pcap .
```

Open in Wireshark
Open level02.pcap in Wireshark.

Locate packet 43, which contains the word "Password".

Right-click the packet and choose "Follow TCP Stream".

This reveals a stream of characters, including:
Password: ft_wandr...NDRel.L0L

However, the dots . represent non-printable characters, likely Delete/Backspace or control characters.
To decode the full password:

Switch the data view in Wireshark to "Hex Dump + ASCII".

Analyze the hexadecimal content and ASCII translations around the key region:

Final Reconstructed Password:
```
ft_waNDReL0L
```
level02@SnowCrash:~$ su flag02
Password: 
Don't forget to launch getflag !
flag02@SnowCrash:~$ getflag
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq

