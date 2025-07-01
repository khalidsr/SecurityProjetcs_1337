## Step 1:
 Hidden email input in the forget password page, 
we change the value of the email that the recovery pass sent to . then we click on the button submit.

## Prevention:

- Never trust or rely on client-side hidden inputs for critical actions like password recovery.

- Send recovery emails only to the email address associated with the authenticated account on the server.

- Use one-time, expiring tokens for password reset instead of direct email input.


