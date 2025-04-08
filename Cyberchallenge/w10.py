

import requests

response = requests.put("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.get("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.post("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.head("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.delete("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.options("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.put("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.options("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)

response = requests.patch("http://web-10.challs.olicyber.it/")
print(response)
print(response.text)
print(response.content)
print(response.headers)