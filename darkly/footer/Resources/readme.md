## Step 1 : 

Clicking the link '@borntosec' in the footer, after inspecting the page, we get useful informations as comments in html code.

## Step2 :

using burp suite we send this url 'http://10.14.59.10/?page=b7e44c7a40c5f80139f0a50f3650fb2bd8d00b0d24667c4c2ca32c88e13b758f'  to repiter then we put User-Agent: ft_bornToSec
Referer: https://www.nsa.gov/ to get the flag.

## Prevention:

- Do not expose sensitive hints or access details in HTML comments or metadata.

- Avoid using User-Agent or Referer headers as security mechanisms—they are easily spoofed.

- Implement proper authentication and authorization on the server side.
