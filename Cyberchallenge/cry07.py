from Crypto.Cipher import DES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

# Parametri
key = bytes.fromhex('c47249e3d90861a3')
plaintext = 'La lunghezza di questa frase non è divisibile per 8'

# Aggiungere il padding x923
padded_data = pad(plaintext.encode(), DES.block_size, style='x923')

# Creare un IV casuale
iv = get_random_bytes(DES.block_size)

# Cifrare con DES in modalità CBC
cipher = DES.new(key, DES.MODE_CBC, iv)
ciphertext = cipher.encrypt(padded_data)

# Il risultato in esadecimale
ciphertext.hex()

#########################################################################


# Genera una chiave casuale di 32 byte per AES256
key = get_random_bytes(32)

# Testo in chiaro
plaintext = 'Mi chiedo cosa significhi il numero nel nome di questo algoritmo.'

# Padding PKCS7 (block size = 16)
padded_data = pad(plaintext.encode(), AES.block_size)

# Genera un IV casuale di 16 byte
iv = get_random_bytes(AES.block_size)

# Cifrare con AES256 in modalità CFB (segment size = 24)
cipher = AES.new(key, AES.MODE_CFB, iv, segment_size=24)
ciphertext = cipher.encrypt(padded_data)

# Mostra la chiave e il testo cifrato in esadecimale
key.hex(), ciphertext.hex()
