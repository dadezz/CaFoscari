import sqlite3
import unicodedata

class SecureSQL:
    def __init__(self, db_path=':memory:'):
        self.conn = sqlite3.connect(db_path, check_same_thread=False)
        self._init_schema()

    def _init_schema(self):
        real_admin_pan = os.getenv("ADMIN_PAN", "1111111111111111")
        
        c = self.conn.cursor()
        c.execute("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, pan TEXT, role TEXT)")
        c.execute("INSERT OR IGNORE INTO users (id, username, pan, role) VALUES (1, 'admin', ?, 'sysadmin')", (real_admin_pan,))
        c.execute("INSERT OR IGNORE INTO users (id, username, pan, role) VALUES (2, 'guest', '0000000000000000', 'visitor')")
        self.conn.commit()

    def _escape_id(self, val):
        return str(val).replace("`", "``")

    def _escape_val(self, val):
        return str(val).replace("'", "''")

    def query(self, tpl, ids=None, vals=None):
        if ids is None: ids = []
        if vals is None: vals = []

        c_ids = [self._escape_id(i) for i in ids]
        c_vals = [self._escape_val(v) for v in vals]

        raw = tpl.format(*c_ids, *c_vals)
        final = unicodedata.normalize('NFKC', raw)

        cur = self.conn.cursor()
        try:
            cur.execute(final)
            return cur.fetchall()
        except Exception:
            return []