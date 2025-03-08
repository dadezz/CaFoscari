import requests

s=requests.Session()
response = s.get("http://web-03.challs.olicyber.it/flag", headers={"X-Password":"admin"})

print(response.text)