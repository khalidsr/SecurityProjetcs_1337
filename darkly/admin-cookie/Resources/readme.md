## Step 1: 
Decode the MD5 Hash Use an MD5 decrypter like dCode, CrackStation or MD5Decrypt:

Hash: 68934a3e9455fa72420237eb05902327

result false 

## Step2 :
Exploit the Cookie use the hash of true https://www.md5hashgenerator.com/

I_am_admin=b326b5062b2f0e69046810717534cb09

### Step 3: 
Send the Modified Cookie
using Burp Suite

Intercept a request → Modify the cookie → Forward.

Browser:

Open DevTools → Application → Cookies → Edit the value.

##step 4 it pop up the flag
### Prevention:

Never store admin status or sensitive data in client-side cookies.

Avoid weak hashes like MD5—use HMAC with SHA-256 or stronger.
