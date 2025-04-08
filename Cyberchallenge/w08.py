import requests

s=requests.Session()
response = s.post("http://web-08.challs.olicyber.it/login", data={"username": "admin", "password": "admin"})

print(response.text)