##Step1 :

We scrap the content of readme files located inside 'http://10.14.59.11/.hidden/' sub-directories.

One of the readme files contains the flag.
## Prevention:

- Disable directory listing on the web server .

- Avoid placing sensitive files (like readme, backups, or configs) in web-accessible paths.

- Configure .htaccess or server rules to deny access to hidden or sensitive folders.

