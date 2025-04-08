import requests
from bs4 import BeautifulSoup

url = "http://web-13.challs.olicyber.it/"
res = requests.get(url)

soup = BeautifulSoup(res.text, 'html.parser')


highlighted = soup.find_all("span", class_="red")

flag = "".join([tag.text for tag in highlighted])

print("flag{" + flag + "}")
