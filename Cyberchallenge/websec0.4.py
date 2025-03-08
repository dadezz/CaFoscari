import requests

s=requests.Session()
response = s.get(" http://web-04.challs.olicyber.it/users", headers={"Accept":"application/xml"})

print(response.text)