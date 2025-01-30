-- attori(codice_att, nome, cognome, anno_nascita)
-- PK(codice_att) 
--
-- film(codice_film, titolo, anno_produzione, regista, totale_incasso)
-- PK(codice_film)
-- 
-- attori_film(codice_film, codice_att, compenso)
-- PK(codice_film, codice_att), codice_film FK(film), codice_att FK(attori) 









--Trovare il nome, cognome degli attori che hanno recitato in un film del regista
-- Win Wenders prodotto dopo il 1970.
SELECT DISTINCT a.codice_att, a.nome, a.cognome
FROM attori a NATURAL JOIN attori_film af NATURAL JOIN film f
WHERE f.regista = 'Win Wenders' AND f.anno_produzione > 1970;

-- Trovare il numero di film in cui hanno recitato insieme Paola Cortellesi e Antonio Albanese.
SELECT COUNT(*) AS num_film
FROM (attori a1 NATURAL JOIN attori_film af1) 
	JOIN 
	(attori_film af2 ON af1.codice_film = af2.codice_film) 
	JOIN attori a2 ON af2.codice_att = a2.codice_att
WHERE a1.nome = 'Paola' AND a1.cognome = 'Cortellesi' AND a2.nome = 'Antonio' AND a2.cognome = 'Albanese';

-- Per ogni attore, restituire il numero di film in cui ha recitato, il numero di registi differenti con cui ha lavorato e la somma degli incassi dei film. Se un attore non ha lavorato in nessun film si deve restituire 0 film, 0 registi e 0 incasso.
SELECT a.codice_att, COUNT(f.codice_film) AS numero_film, COUNT(DISTINCT f.regista), COALESCE(SUM(f.totale_incasso), 0) AS incassi  
FROM attori a NATURAL LEFT JOIN (attori_film af NATURAL JOIN film f)
GROUP BY a.codice_att;


-- Per ogni regista, trovare il titolo e l'anno di produzione del film 
-- che ha avuto il massimo incasso e restituire anche il numero di attori che hanno recitato in quel film.
WITH num_attori_film(codice_film, titolo, regista, totale_incasso, anno_produzione, num_attori)
AS (SELECT f.codice_film, f.titolo, f.regista, f.totale_incasso, f.anno_produzione, COUNT(*)
    FROM film f NATURAL JOIN attori_film af 
    GROUP BY f.codice_film, f.titolo, f.regista, f.totale_incasso, f.anno_produzione)
SELECT naf.regista, naf.titolo, naf.anno_produzione, naf.num_attori
FROM num_attori_film naf
WHERE naf.totale_incasso = (SELECT MAX(totale_incasso)
      			   FROM num_attori_film naf2
			   WHERE naf.regista = naf2.regista);

-- Rimuovere il film/i film che hanno avuto il minimo incasso nell'anno di produzione 1984 e le relative tuple della tabella attori_film.
CREATE VIEW film_fiasco(codice_film)
AS SELECT f.codice_film
    FROM film f
    WHERE f.anno_produzione = 1984 AND NOT EXISTS (SELECT *
    	  		     	      	      FROM film f1
					      WHERE f1.anno_produzione = 1984 AND f1.totale_incasso < f.totale_incasso);

DELETE FROM attori_film
WHERE codice_film IN (SELECT *
      		     FROM film_fiasco);

DELETE FROM film
WHERE codice_film IN (SELECT *
      		     FROM film_fiasco);

		      
