import os
import binascii
from Crypto.Cipher import DES3

_K = os.getenv("PVK", "00000000000000000000000000000000")

class VaultEngine:
    def __init__(self):
        try:
            self.msk = binascii.unhexlify(_K)
        except:
            self.msk = _K.encode()[:16]

    def _idx_shift(self, p):
        d = [int(c) for c in p if c.isdigit()]
        return sum(d) % 16

    def sign(self, pan, dtab):
        if len(dtab) != 16: return None
        if len(set(dtab)) < 8: return None

        b_pan = binascii.unhexlify(pan)
        c = DES3.new(self.msk, DES3.MODE_ECB)
        
        s1 = c.encrypt(b_pan).hex().upper()
        s2 = c.encrypt(bytes([b ^ 0xFF for b in b_pan])).hex().upper()
        stream = s1 + s2

        shift = self._idx_shift(pan)
        res = ""

        for i in range(32):
            raw = int(stream[i % len(stream)], 16)
            ptr = (raw + shift) % 16
            res += dtab[ptr]
        
        return res