import requests

s=requests.Session()
response = s.head("http://web-07.challs.olicyber.it/")

print(response.headers)