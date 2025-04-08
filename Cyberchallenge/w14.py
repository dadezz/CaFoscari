import requests
from bs4 import BeautifulSoup, Comment

url = "http://web-14.challs.olicyber.it/"
res = requests.get(url)

soup = BeautifulSoup(res.text, 'html.parser')

comments = soup.find_all(string=lambda text: isinstance(text, Comment))

for comment in comments:
    print("[+] Commento trovato:")
    print(comment.strip())
