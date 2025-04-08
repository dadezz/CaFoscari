import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin
import re

start_url = "http://web-16.challs.olicyber.it/"
visited = set()
to_visit = [start_url]

while to_visit:
    current_url = to_visit.pop()
    if current_url in visited:
        continue

    print(f"[~] Visiting: {current_url}")
    visited.add(current_url)

    try:
        res = requests.get(current_url)
        soup = BeautifulSoup(res.text, 'html.parser')

        # Cerca la flag in un <h1>
        h1 = soup.find('h1')
        if h1 and re.search(r'flag\{.*?\}', h1.text):
            print(f"FLAG: {h1.text.strip()}")
            break

        # Trova nuovi link da visitare
        for a in soup.find_all('a', href=True):
            next_url = urljoin(current_url, a['href'])
            if next_url not in visited:
                to_visit.append(next_url)

    except Exception as e:
        print(f"Errore su {current_url}: {e}")
