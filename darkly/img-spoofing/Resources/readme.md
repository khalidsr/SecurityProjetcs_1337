## Step 1:
Visit the URL /index.php?page=upload using Burp Suite.

## Step 2:
Upload a .jpeg image file on this page. Then, intercept the request and send it to Repeater in Burp Suite.

## Step 3:
After the image is successfully uploaded, modify the filename extension in the request to .php (or any executable extension).
Also, change the Content-Type header to image/jpeg to bypass content validation.

## Prevention:

 - Strictly validate file extensions and MIME types on the server side.

- Use a whitelist of allowed file types (e.g., only .jpg, .png).

 - Block executable file types (.sh .php, .exe) regardless of Content-Type.

 - Use a secure file upload library that sanitizes and checks file content and headers.
