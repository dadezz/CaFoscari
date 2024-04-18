import sqlite3

con = sqlite3.connect("tennis.db") #database locale

con.execute('''CREATE TABLE IF NOT EXISTS event(
    atp integer,
    location text,
    other_fields type
)''')

