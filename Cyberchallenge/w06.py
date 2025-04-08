import requests

s=requests.Session()
response = s.get("http://web-06.challs.olicyber.it/token ")

print(response.text)