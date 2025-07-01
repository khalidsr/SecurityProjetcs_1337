# XSS (Cross-Site Scripting)
## Walk-Through
- Injecting a malicious script `<script>alert('hello')</script>` in the src tag of the link.

- Encoding the script into base64 to prevent the block of characters like `> ' " <` by applications.

- Becames something like: `data:text/html;base64,PHNjcmlwdD5hbGVydCgnaGVsbG8nKTwvc2NyaXB0Pg==`. Then plcaed in the src tag to get the flag.

## Prevention
- Applying a Content Security Policy (CSP) that blocks inline scripts and untrusted sources. Even if an attacker managed to slip in a `<script>` tag, the browser would refuse to load or execute it.