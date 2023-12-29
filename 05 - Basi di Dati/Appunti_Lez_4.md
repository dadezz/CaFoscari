SQUADRE (Nazione, Allenatore)
PARTITE (idP, Squadra1*, Squadra2*)
RETI (idR, idG (FKGiocatori), idP (FK Partite), Autog)
GIOCATORI (idG, Nome, Nazione*, Nascita)

# Esercizi

## 1
rimuovere i giocatori che non hanno segnato alcun goal oppure che hanno segnato solo autogoal

```SQL
DELETE FROM Giocatori
WHERE idG NOT IN (
    SELECT idG
    FROM Reti
    WHERE NOT Autog
)
```

elimina i giocatori che non stanno nella sottoquery "seleziona i giocatori che hanno fatto gol ma non autogol", perché la sottoquery usa la tabella reti, quindi per forza gli idG in essa contenuti hanno fatto gol. Se poi si cavano quelli che hanno fatto autogol rimangono tutti i giocatori che hanno fatto gol "giusti". Da qui, elimino tutti quelli che NON rispondono a questa descrizione, ovvero elimino solo quelli che non hanno fatto goal o hanno fatto autogoal.

Prima però vanno eliminate anche le reti stesse, perché senno rimane incosistente la BD: ci sarebbero reti che hanno idg che punta a un giocatore che non esiste più. Il controllo non andrebbe fatto se ci fosse scritto che la politica di cancellazione è cascade

```SQL
DELETE FROM Reti
WHERE idG NOT IN (
    SELECT idG
    FROM Reti
    WHERE NOT Autog
)
```

## 2
Trovare per ogni squadra quanti gioactori hanno segnato un goal escludendo gli autogoal.. Se una squadra ha segnato 0 goal deve ritornare 0 giocatori. 


La prefsenza dello zero suggerisce sempre la presenza di un left/right join

```SQL
SELECT g.Nazione, Count(DISTINCT r.Idg) /*distinct xk prendo giocatori diversi, e calcolo il count su r.idg, perché è solo r he si annulla, non g. Deve restituirmi 0. Devo scegliere un attributo che si annulla, sennò non conto gli zeri. Perché distinct: voglio contare quanti giocatori. se non lo mettessi, conterei quanti valori diversi da null sono resenti in quella colonna -> quanti goal sono fatti, non quanti giocatori diversi.*/
FROM Giocatori g LEFT JOIN Reti r ON g.idG = r.idG AND NOT r.Autog
GROUP BY g.Nazione
```

## 3
Trovare la partita in cui sono stati realizzati più goal e restituire le sqauadre e il numero dei goal segnati da ciascuna squadra (cioè il risultato della paritta). Se ci sono più partirte con il numero massimo di goal restituirile tutte.

Inizio cno la creazione di una vista
```SQL
CREATE VIEW RisultatoPartite(idP, sq1, numG1, sq2, Numg2)
AS
    SELECT p.idP, p.Squadra1, SUM(
        CASE WHEN (NOT r.Autog AND g.Nazione = p.Squadra1) OR (r.autog AND g.Nazione = p.Squadra1) THEN 1
        ELSE 0
        END
    ), P.Squadra2, SUM(
        CASE WHEN (NOT r.Autog AND g.Nazione = p.Squadra2) OR (r.autog AND g.Nazione = p.Squadra2) THEN 1
        ELSE 0
        END
    )
    FROM Partite p NATURAL LEFT JOIN (Reti r NATURAL JOIN Giocatori g)
    GROUP BY p.idP, p.Squadra1, p.Squadra2
```
Poi faccio la ricerca di un massimo
```SQL
SELECT 
FROM RisultatoPartite
WHERE NumG1 + Numg2 = (
    SELECT MAX(NumG1 + NumG2)
    FROM RisultatoPartite
)
```

## 4
Trovare le squadre che gli allenatori che hanno giocato il max numero di partite

```SQL
CREATE VIEW PartiteGiocate(Squadre, Allenatore, NumPartiteGiocate)
AS
    SELECT s.Nazione, s.Allenatore, COUNT(*)
    FROM Squadre s JOIN Partite p ON (s.Nazione = p.Squadra1 OR s.Nazione = p.Squadra2)
    GROUP BY s.Nazione , s.Allenatore

/*ora ricerca del max assoluto*/
SELECT Squadra, llenatore
FROM PartiteGiocate
WHERE NumpPartiteGiocate = (
    SELECT MAX(Numpartiteiocate)
    FROM PartiteGiocate
)
```

# 5
Trovare le squadre contro cui ha giocato l'italia. ANche in algebra relazionale

```SQL
SELECT Squadra2 AS Squadra
FROM  Partite p
WHERE Squadra1 = 'Italia' 

UNION

SELECT Squadra1 AS Squadra
FROM Partite
WHERE Squadra2 = 'Italia'
```

in algebra: ro{squadra1 <- squadra} (pi{squadra1}sigma{squadra2='italia'}(Partite)) UNION ro{squadra2 <- squadra} (pi{squadra2}sigma{squadra1='italia'}(Partite))