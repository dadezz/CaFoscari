import requests

s=requests.Session()
response = s.post("http://web-09.challs.olicyber.it/login", json={"username": "admin", "password": "admin"})

print(response.text)