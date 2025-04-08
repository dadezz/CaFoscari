import requests
from bs4 import BeautifulSoup
import re
from urllib.parse import urljoin


base_url = "http://web-15.challs.olicyber.it/"
res = requests.get(base_url)

soup = BeautifulSoup(res.text, 'html.parser')

# Lista per contenere tutti i link alle risorse esterne
resource_urls = []

# Trova link <link href="..."> (es. CSS)
for link in soup.find_all("link", href=True):
    resource_urls.append(urljoin(base_url, link["href"]))

# Trova script <script src="...">
for script in soup.find_all("script", src=True):
    resource_urls.append(urljoin(base_url, script["src"]))

# Scarica ogni risorsa e cerca la flag
for url in resource_urls:
    print(f"[~] Controllo: {url}")
    r = requests.get(url)
    match = re.search(r'flag\{.*?\}', r.text)
    if match:
        print(f"FLAG: {match.group()}")
        break
else:
    print("Nessuna flag")
