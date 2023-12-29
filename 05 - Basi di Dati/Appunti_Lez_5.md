# Viste
È importante usare le viste, si usa la parola AS per dar loro un nome
Una vista si interroga come unatablella qualunque, ma non tutte le viste sono modificabili.
SI usano perché vogliamo l'indipendenza logica (trasparenza alle app che usano questa BD), oltre ce offrire diverse visioni della db senza duplicazioni e ridondanza dei dati.
È anche utile per scrivere query più semplici o che addirittura sarebbe impossibile esprimere altrimenti:

Trovare la media dei voti massimi ottenuti nelle varie province.
Non si può usare una f di agregazione su un'altra f di aggregazione, quindi non si può scrivere
```SQL
SELECT AVG(MAX(e.Voto))
FROM Studenti s JOIN e ON s.Matricola = e.Candidato
GROUP BY s.Provincia
```
Dobbiamo scindere quel select uando una vista:
```SQL
CREATE VIEW ProvinciaMassima(Provincia, VotoMassimo)
AS 
    SELECT s.Provincia, MAX(e.Voto) AS VotoMassimo
    FROM Studenti s JOIN Esami e ON s.Matricola = e.candidato
    GROUP BY s.Provincia

SELECT AVG(VotoMassimo)
FROM ProvinciaMassimo
```
***
## Ricerca del massimo
Le province dove la media dei voti degli studenti è massima (ricerca del massimo). Restituire tale/i provincia/e e la media

```SQL
CREATE VIEW ProvinciaMedia(Provincia, Media)
AS
    SELECT s.Provincia, AVG(e.Voto) 
    FROM Studenti s JOIN Esami e ON s.Matricola = e.Candidato
    GROUP BY s.Provincia

SELECT Provincia
FROM ProvinciaMedia pm
WHERE Media = (
    SELECT MAX(Media)
    FROM ProvinciaMedia
)
```
è un errore fare una cosa del genere:
```SQL
SELECT Provincia, MAX(Media)
FROM ProvinciaMedia
```
perché si va ad unire attributo con funzione di aggregazione, e il DBSM non sa cosa andare a restituire come provincia in caso di conflittualità

***
### Viste e interrogazioni difficili   
È indispendsabile la vista per il max? si, ma è bello compliacto e si consiglia l'uso di una vista:

```SQL
SELECT s.Provincia
FROM Studenti s JOIN Esami e ON s.Matricola= e.Candidato
GROUP BY s.Provincia
HAVING AVG(e.Voto) >= ALL (
    SELECT AVG(e.voto)
    FROM Studenti s JOIN Esami e ON s.Matricola = e.Candicato
    GROUP BY s.Provincia
)
```

Altro esempio:
Dare il nome di ogni cane che ha entrambi i genitori e i nonni della sua stessa razza
```SQL
CREATE VIEW StessaRazza(Id, Padre, Madre)
AS 
    SELECT f.Id, m.Id, p.Id
    FROM Cani f, Cani p, Cani, m
    WHERE f.Padre = p.Id AND f.Madre = m.Id AND f.Razza = p.Razza AND f.razza = m.Razza

SELECT c.Nome
FROM StessaRazza f, StessaRazza m, StessaRazza p, Cani c
WHERE f.Padre = p.Id AND f.Madre = m.Id AND f.Id = c.Id
```
Con questo abbiamo concluso DDL.
***
# Sintassi aggiuntiva

## WITH
COstruzione tablele temporanee. Invece di una vista uso il with, tipo se la vista mi serve una sola volta e poi posso eliminarla, esiste solo per la query, poi si autoelimina

## CASE

Espressione condizionale che può essere usata in qualiasi contesto dove un'espresione è valida
```SQL
CASE WHEN condizione THEN risultato
    WHEN ...
    WHEN ...
    ELSE risultato
END
```
condizione è bool, se è vera restituisce il risultato, altrimenti vengono esaminate le varie clausole when (tipo switch-case), altrimenti viene restituito il risutlato dell'else. se esso non è presente, viene restituito NULL.
È impoetante "non è vera" e non "è falsa", percHé se il risultato è unknown, continua ugualmente con l'else o il when successivo

## Associazioni simmetriche
Poniamo tabella persone con fratelli (due chiavi esterne per persone). Ha senso mettere p1 è fratello di p2 E ANCHE p2 fratello di p1?
Poniamo di verli messi entrambe:
```sql
SELECT p1.*, p2.*
FROM Persone p1, Fratelli f, Persone p2
WHERE p1.Id = f.Id AND f.ID2=p2.ID
```

restituisce 2 nuple per ogni coppia. p1 e p2 sono interscambiabili e non vglio il doppio dei risultati. 
Posso complicare la query aggiungendo una condizione nel where, per esmpio `AND p1.ID < p2.ID`.

Se invece ci fosse una sola tupla?
```SQL
SELECT p.*
FROM Persone p, Fratelli f
WHERE f.Id 1= 21 AND p.ID = f.ID2
```

restituisce un insieme vuoto perhé non è detto che il 21 sia nel primo id e non nel secondo, quindi va aggiunta ugualmente la clausola nel where `OR (f.Id2 = 21 and p.Id = f.Id1)`.

Devo sempre stare attento a mettere un ordine o controllare la simmetria. Molti preferiscono evitare la ridondanza e scegliere quindi il secondo metodo, ma van bene entrambe.

## For all senza for all
Quantificazione universale senza sottoselect? Di solito si usa la negazione su un esistenziale.
Si può usare un except:
```SQL
SELECT s.*
FROM Studenti s
    EXCEPT
SELECT s.*
FROM Studenti s JOIN Esami e ON s.Matricola = e.Candicato
WHERE e.Voto <> 30
```

ALtra alternativa è il left join col controllo del null

```SQL
SELECT s.*
FROM Studenti s LEFT JOIN Esami e ON s.Matricola = e.Candidato AND e.Voto <> 30
WHERE e.Voto IS NULL
```

