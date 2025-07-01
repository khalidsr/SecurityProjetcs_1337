# XSS (Cross-Site Scripting)
## Walk-Through
- Injecting malicious link into a vulnerable social media links in the footer and changing the src attribute to some malicious URL.

## Prevention
- Preventing this injection by letting only trusted admins set footer links and check each URL matches a known good pattern (e.g. it really starts with https://…).