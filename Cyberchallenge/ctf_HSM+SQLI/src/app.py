import os
from flask import Flask, request, jsonify
from secure_db import SecureSQL
from hsm_core import VaultEngine

app = Flask(__name__)
db = SecureSQL()
hsm = VaultEngine()

_F = os.getenv("FLAG", "flag{REDACTED}")
_STD = "0123456789012345"
_ADM_PAN = os.getenv("ADMIN_PAN", "1111111111111111")

@app.route('/api/v1/users/check', methods=['POST'])
def u_check():
    d = request.get_json(silent=True)
    if not d or 'f' not in d or 'v' not in d:
        return jsonify({"e": 1}), 400

    q = "SELECT username, role FROM users WHERE `{}` = '{}'"
    r = db.query(q, [d['f']], [d['v']])
    
    return jsonify({"data": r})

@app.route('/api/v1/auth/verify', methods=['POST'])
def a_verify():
    d = request.get_json(silent=True)
    if not d or not all(k in d for k in ('pan', 'pin')):
        return jsonify({"e": 2}), 400

    pan = d['pan']
    pin = d['pin']
    tab = d.get('tab', _STD)

    rows = db.query("SELECT role FROM users WHERE pan = '{}'", [], [pan])
    if not rows or rows[0][0] != 'sysadmin':
        return jsonify({"s": "DENIED"}), 403

    calc = hsm.sign(pan, tab)
    if not calc:
        return jsonify({"e": 3}), 400

    if calc == pin:
        if pan == _ADM_PAN and tab == _STD:
            return jsonify({"s": "GRANTED", "secret": _F})
        return jsonify({"s": "VALID"})
    
    return jsonify({"s": "INVALID"}), 403

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=1337)