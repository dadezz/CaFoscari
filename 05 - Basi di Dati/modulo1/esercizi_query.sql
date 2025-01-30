-- Attori(CodiceAtt PK, Nome, Cognome, AnnoNascita)
-- Film(CodiceFilm PK, Titolo, AnnoProduzione, Regista, TotaleIncasso)
-- AttoriFilm(CodiceFilm PK, CodiceAtt, Compenso)
-- CodiceFilm FK(Film) CodiceAtt FK(Attori)

-- Trovare il nome e cognome degli attori che hanno recitato in un film del regista Win Wenders
-- prodotto dopo il 2000;
SELECT DISTINCT a.CodiceAtt, a.Nome, a.Cognome
FROM Attori a NATURAL JOIN AttoriFilm af NATURAL JOIN Film f
WHERE f.AnnoProduzione > 2000 AND f.Regista = 'Win Wenders';

-- Trovare il numero di film in cui hanno recitato insieme Paola Cortellesi e Antonio Albanese;
SELECT COUNT(DISTINCT cf.CodiceFilm) as numero_film
FROM (Attori a1 NATURAL JOIN AttoriFilm af1) JOIN
    (Attori a2 NATURAL JOIN AttoriFilm af2)
WHERE a1.Nome = 'Paola' AND a1.cognome = 'Cortellesi' AND a2.Nome = 'Antonio' AND a2.Cognome = 'Albanese'

-- Per ogni attore, restituire il numero di film in cui ha recitato, il numero di registi differenti con
-- cui ha lavorato e la somma degli incassi dei film. Se un attore non ha lavorato in nessun film
-- si deve restituire 0 film, 0 registi e 0 incasso;
SELECT a.codice_att, COUNT(af.codice_film) as numero_film, 
        COUNT(DISTINCT f.regista) as numero_registi COALESCE(SUM(f.TotaleIncasso), 0) as incasso
FROM attori a NATURAL LEFT JOIN attori_film af JOIN Film f USING (codice_film)
GROUP BY a.codice_att

-- Per ogni regista, trovare il titolo e l’anno di produzione del film che ha avuto il massimo
-- incasso e restituire anche il numero di attori che hanno recitato in quel film;
WITH numero_attori(codice_film, titolo, regista, totale_incasso, anno_produzione, num_attori) AS
SELECT f.regista, f.codice_film, f.titolo, f.anno, f.TotaleIncasso, COUNT(af.codice_att)
FROM Film f NATURAL JOIN AttoriFilm af
GROUP BY f.regista f.codice_film, f.titolo, f.anno, f.TotaleIncasso

SELECT na.titolo, na.anno, na.incasso, na.numero_attori
FROM numero_attori na
WHERE na.incasso = (
    SELECT MAX(na2.incasso)
    FROM numero_attori na2
    WHERE na2.regista = na.regista
) 

-- Rimuovere il film/i film che hanno avuto il minimo incasso nell’anno di produzione 2020 e le
-- relative tuple della tabella AttoriFilm.
DELETE FROM Film
WHERE codice_film IN (
    SELECT f.codice_film
    FROM film f
    WHERE f.anno = 2020 AND f.TotaleIncasso <= ALL(
        SELECT f2.TotaleIncasso
        FROM film f2
        WHERE F2.AnnoProduzione = 2020
    )
)

DELETE FROM AttoriFilm
WHERE codice_film IN (
    SELECT f.codice_film
    FROM film f
    WHERE f.anno = 2020 AND f.TotaleIncasso <= ALL(
        SELECT f2.TotaleIncasso
        FROM film f2
        WHERE F2.AnnoProduzione = 2020
    )
)