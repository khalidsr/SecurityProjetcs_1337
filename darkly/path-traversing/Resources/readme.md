# Path Traversal
## Walk-Through
- A path traversal attack aims to access files and directories that are stored outside the web root folder. By manipulating variables that reference files with “dot-dot-slash (../)” sequences and its variations or by using absolute file paths, it may be possible to access arbitrary files and directories stored on file system including application source code or configuration and critical system files.

- The passwd file is accessible via the path `VM_ip/?page=/../../../../../../../etc/passwd`.

## Prevention
- The access to files should be limited by system operational access control (such as in the case of locked or in-use files on the Microsoft Windows operating system).