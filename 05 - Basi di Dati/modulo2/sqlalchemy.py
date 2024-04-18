import sqlalchemy as sq 

"""
si appoggia a 3 entità chiave: 
1. engine: astrazione del dbms sottostante, per esempio SQLite, MySQL, Postrge
2. metadata: un astrazione dello schema relazionae su cui operare, contenente tutte le relaizoini al suo interno
3. connessione: l'interfaccia di accesso all'engine tramite la quale eseguianmo le query desiderate. Può definire anche lo scope di una transazione
"""

# Connessione al DB

engine = sq.create_engine('sqlite://', echo = True) # la stringa iniziale definisce il DB echo = true è versione verbosa

# possibile stringa valida nel nostro caso:
s = 'postgresql://scott:tiger@localhost:5432/mydatabase'

with engine.connect() as conn:
    conn.execute(sq.text("CREATE TABLE some_table(x int, y int)"))
    conn.execute(sq.text("INSERT INTO some_table (x, y) VALUES (1,2)"))
    conn.commit() # !!! sqlalchemy di default non ha autocommit -> se mi dimentico viene rollbackato

# usando la sintassi with si può evitare di dover chiudere la connessione alla fine, percHé viene fatto in automatico all'uscita dello scope

"""
inserimento / modifica
"""

with engine.connect() as conn:
    conn.execute(
        sq.text("INSERT INTO some_table (x, y) VALUES (:X, :Y)"),
        {"X": 1, "Y": 1} # PREPARED STATEMENT
    )
    conn.commit()

# se al posto di connect scrivo begin, ho il commit automatico