## Step 1: 
Analyze the Login Request

We inspect the sign-in page to understand how the login request is sent . This helps us identify the parameters (like username and password) and the URL endpoint used for authentication.

## Step 2: 
Set Up Burp Suite Intruder

Using Burp Suite, we intercept a login attempt and send the request to Intruder. We then:

    - Highlight the username and password fields.

    -  Mark them as payload positions using §.

    -  Load a wordlist (rockyou.txt) to test multiple passwords dynamically.

## Step 3: 
Perform the Brute-Force Attack

We run the attack in Burp Suite, simulating multiple login attempts by iterating through the wordlist. Once the correct password is found, we successfully authenticate and retrieve the flag or target information.
## Prevention:

- Implement account lockout or rate limiting after several failed login attempts.

- Use CAPTCHAs to block automated login attempts.

- Monitor and log suspicious login activity (e.g., repeated failed attempts).

- Enforce strong password policies and two-factor authentication (2FA).

- Use progressive delays or IP blocking to slow down brute-force tools.
