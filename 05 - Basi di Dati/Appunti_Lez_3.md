# Errori Semantici
prendiamo la BD così strutturata:

## base dati
Persone (CF, Nome, AnnoNascita)
Animali (Codice, Nome, Padrone*, Specie, Razza, Sesso)

## query sbagliate
### 1 
Trovare le specie possedute da Mario Rossi
```SQL
SELECT a.Specie
FROM Persone p, Animali a
WHERE p.Nome = 'Mario Rossi'
```
* Manca la giunzione, in questo caso `join on p.CF = a.Padrone`
* manca il distinct: se mario rossi ha 2 cani, viene restituito due volte, vanno invece tolti i duplicati. Per essere del tutto prefcisi etogliere eventualiproblemi di omonimia, aggiungere il CF (in generale la chiave) per sicurezza

```SQL
SELECT a.Specie
FROM Persone p, Animali a
WHERE p.Nome = 'Mario Rossi'
GROUP BY a.Specie
```
Questa (col join) è semanticamente corretta, ma diciamo che il group by non è un costrutto che si usa per rimuovere i duplicati, sarebbe bene non usarlo e rimpiazzarlo col distinct

### 2
trovre il CF delle persone che possiedono un gatto

```SQL
SELECT DISTINCT p.CF
FROM Persone p JOIN Animali a ON p.CodiceFiscale = a.Padrone
WHERE a.Specie = 'gatto'
```

non è un errore ma un problema di efficienza: non serve il join, perché il padrone è già identificato dal codifce fiscale

### 3
trovre il nome e il CF delle persone che possiedono un gatto e un cane

```SQL
SELECT DISTINCT p.CodiceFiscale, p.Nome
FROM Persone p JOIN Animali a ON p.CF = a.Padrone
WHERE a.Specie = 'gatto' AND a.Specie = 'cane'
```

Sicuramente ritorna una tabella vuota, percheé una ennupla non avrà mai la specie uguale a cane e contemporaneamente uguale a gatto. [vincolo inconsistente]

Serve quindi un'altra join con animali, a2 USING (Padrone), poi nel where a1= gatto e a2 = cane

### 4 
Trovare quanti animali possiede per specie la persona con codice fiscale 'RFFLS'

```SQL
SELECT Specie, COUNT(Codice) AS Numero
FROM Animali
WHERE Padrone = 'RFFLS'
GROUP BY Specie
```

non è un errore ma inefficienza di nuovo: quando possibili non mettere un attributo dentro a count, ma usare stellina

### 5
Trovare CF delle persone che no possiedono criceti

```SQL
SELECT CF
FROM Persone
WHERE NOT EXISTS (
    SELECT * 
    FROM Animali
    WHERE Specie = 'criceto'
)
```

La sottoselect è completamente scorrelata dalla select principale. In presza di exist serve qualcosa che stabilisca una correlazione tra la query interna e quella esterna. Così scritta, se all'interno di animali c'è un criceto allora la query è sempre falsa, se invece non ce ne sono, allora è sempre vera.

serve quindi nella sottoselect mettere un vincolo nel where: `where specie= 'criceto' and p.cf = a.padrone`.

### 6
Restituire il nome degli animali

```SQL
SELECT Nome
FROM Animali
WHERE Codice IS NOT NULL
```

Codice è primary key, come fa a essere null? La condizione è tautologica, sempre vera. La tautologia è un errore

### 7
Restituire nome, cf di una persona e il nome e il codice di tutti gli animali che possiede

```SQL
SELECT DISTINCT p.CF, p.Nome, a.Codice, a.Nome
FROM Persne p JOIN Animali a ON p.CF = a. Padrone
```

again, efficienza: non serve fare il distinct (non ci possono essere nuple ripetute). distinct va evitato dove non è necessario usarlo.

### 8
Contare quanti cani sono presenti in animali

```SQL
SELECT COUNT(*)
FROM Animali
WHERE Specie = 'Cane'
GROUP BY Specie
```

è inutille il group by perché ho un solo gruppo
### 9
Restituire il nome, cf della (le) persona/e più giovane/i

```SQL
SELECT CF, Nome, MAX(2023-AnnoNascita)
FROM Persone
GROUP BY CF,Nome
```

il CF è la chiave prmaria, quindi raggruppare per quello significa fare tanti grupppi quante sono le nuple (gruppi con un asola entità).
Quel max agisce quindi solo su una persona alla volta (per ogni gruppo), e di conseguenza nonrestituisce altro che l'età della persona per ogni riga, non è una ricerca del massimo. Errore: cstruisco gruppi di un solo elemento

La ricerca del massimo si fa così:
```SQL
SELECT CF, Nome
FROM Persone
WHERE AnnoNascita = (
    SELECT MAX(AnnoNascita)
    FROM Persone
)
```

# ESERCIZI QUERY
## BD:
Fantini (Nome, Peso, AnnoNascita)
Cavalli (Nome, AnnoNascita, Scuderia)
Gare(Codice, Nome, Luogo, Giorno, MEse, Anno, CavalloVincente*, FantinoVincente*)

## Query

### 1
Trovare nome, luogo, giorno, mese delle gre vinte da cavalli della scuderia 'alfea' che si sono svolte nel 2021

```SQL
SELECT g.Nome, g.Luogo, g.Giorno, g.Mese
FROM Gare g JOIN Cavalli c ON g.CavalloVincente = c.Nome
WHERE g.Anno = 2021 AND c.Scuderia = 'Alfea'
```

### 2
Per ogni fantno, restituireil suo nome, la sua età, e il numero di gare che ha vinto da giugno a settembre e il numero di vavalli (differenti) che ha montato durante queste gare. Se non ha vinto alcuna gara in quel periodoo dell'anno restituire 0


SUGGERIMENTO: quando c'è scritot di retituire zero è da utilizzareuna left join. Divent sensibile dove va messa la condizione (se nel from o nel where).
"NUMERO DI GARE VINTE" -> Serve un raggruppamento per ottenere un numero -> group by

```SQL
SELECT f.Nome, 2021-f.AnnoNascita AS Eta, COUNT(g.Codice) AS NumGare /*non metto stellina xk per ritornare gli zeri mi serve un attributo della tabella coi null*/, COUNT(DISTINCT g.CavalloVincente) AS NumCavalli
FROM Fantini f LEFT JOIN Gare g ON g.FantinoVincente = f.Nome AND Mese BETWEEN 6 AND 9
/*LA condizione sulla adta della gara va messa sull'on, perché se la metto sul where, quando faccio la selezione tolgo via quelli che non hanno mai fatto la gara -> non posso restituire gli zeri*/
GROUP BY f.Nome, f.AnnoNascita
```

Trucchi: se richiesto 0 usa leftjoin; in presenza di leftjoin devo stare attento a cosa conto: attributo e non stellina; controllo il distinct (cavalli diversi); devo mettere condizione molto probabilmente in from e non in where sempre perché verrebbero eliminati i null e non potrei contarli di consguenza.

### 3
Trovare il nome de f he hanno vinto una stessa comp (gare con stesso nome) per almeno due anni consecutivi, restituire nome di quella conmpeti

```SQL
SELECT DISTINCT /*si perché potrebber aver vinto anche tante volte consecutivmente la stesa gara*/ g1.FantinoVincente, g1.Nome
FROM Gare g1 JOIN Gare g2 USING (nome, FantinoVincnte) /*mi servono 2 gare, joinandole con nome (devoon essere stessacompet e fantino vincente (nome del f che ha vinto al stessa comp -> il f è lo stesso)*/
WHERE g1.Anno = g2.Anno +1
```

### 4
Per ogni d, trovare anno/i in cui ha vinto il massimo numero di gare e restituirre inoltre il numero di gare vinte e l'età del dantino in quell'anno/i

TROVARE IL MASSIMO NUMERO DI GARE -> RICERCA DEL MASSIMO

```SQL
CREATE VIEW VittorePerAnno(Fantino, Anno, NumGare)
AS
    SELECT FantinoVincente, Anno, COUNT(*)
    FROM Gare
    GROUP BY FantinoVincente, Anno
    /*IL WHERE NON SERVE XK NON C'È RESTRIZIONE*/


SELECT v.Fantino, v.ANno, v.Anno-f.AnnoNascitat AS ETà, v. NUmgare
FROM VittorePerAnno v JOIN Fntini f ON v.Fantino =f.Nome
WHERE v.NumGare = (
    SELECT MAX(v2.NumGare)
    FROM VittorePerANno v2
    WHERE v2. Fantino = v.Fantino /*massimo relativo alfantino, non assoluto*/
)
```

### 5
Rimuovere i cavalli che hanno pià di 20 anni e hanno vinto meno di 4 gare. Si assuma che nella taella gare le chiavi esterne FantinoVinc e CavVinc siano state dichiarate ON DELETE CASCADE

cosa significa questa frase ultima? mi basta fare una delete sola percHé la consistenza è mantenuta in automatico, non è necessaria la delete preventiva sulla foreigner keys

```SQL
DELETE FROM Cavalli c
WHERE 2023 - AnnoNascita > 20 AND  4 > (
    SELECT  COunt(*)
    FROM GARE g
    WHERE g.cavalloVIncente = c.nome
)
```