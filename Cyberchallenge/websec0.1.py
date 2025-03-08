import requests

s=requests.Session()
response = s.get("http://web-01.challs.olicyber.it/")

print(response.text)