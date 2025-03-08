import requests

s=requests.Session()
response = s.get("http://web-02.challs.olicyber.it/server-records", params="id=flag")

print(response.text)