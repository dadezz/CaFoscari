
def xor(a, b):
    return bytes([x ^ b for x in a])

ciphertext_hex = "104e137f425954137f74107f525511457f5468134d7f146c4c"
ciphertext = bytes.fromhex(ciphertext_hex)

for key in range(256):
    decrypted_bytes = xor(ciphertext, key)
    decrypted_text = decrypted_bytes.decode('utf-8', errors='ignore')

    print(f"Testo decifrato: flag{{{decrypted_text}}}")
