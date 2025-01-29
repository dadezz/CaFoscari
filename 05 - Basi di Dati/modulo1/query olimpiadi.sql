 -- atleti(idatleta, nome, cognome, nazione*, sesso, annonascita)
 -- PK(idatleta), nazione FK(nazioni)
 --
 --  medaglie(codice, tipo, sport, disciplina, idatleta*, anno, edizione)
 -- PK(codice), idatleta FK(atleti)
 --
 -- nazioni(nome, estensione, numabitanti)
 -- PK(nome)

-- 7) Trovare gli atleti che hanno vinto meno di 4 medaglie e restituire il nome, cognome e 
-- la nazione e il numero di medaglie vinte
SELECT a.nome, a.cognome, a.nazione, COUNT(m.codice) AS num_medaglie
FROM atleti a NATURAL LEFT JOIN medaglie m 
GROUP BY a.idatleta, a.nome, a.cognome, a.nazione
HAVING COUNT(m.codice) < 4

-- 7bis) Trovare gli atleti che hanno vinto meno di 4 medaglie
-- e restituire il nome, cognome e la nazione
SELECT a.nome, a.cognome, a.nazione 
FROM atleti a
WHERE 4 > ( SELECT COUNT(*) FROM medaglie m WHERE m.idatleta=a.idatleta);

-- 8) Trovare per ogni nazione che ha vinto almeno una medaglia l'atleta/i più giovane
-- che ha vinto una  medaglia e restituire anche l'età di tale atleta/i.
-- L'età deve essere calcolata rispetto all'anno in cui ha vinto la medaglia.
SELECT DISTINCT a.nazione, a.idatleta, a.nome, a.cognome, m.anno - a.annonascita AS eta
FROM atleti a NATURAL JOIN medaglie m 
WHERE m.anno - a.annonascita = (SELECT MIN(m1.anno - a1.annonascita)
			        FROM atleti a1 NATURAL JOIN medaglie m1
				WHERE a1.nazione = a.nazione);


-- In alternativa
SELECT DISTINCT a.nazione, a.nome, a.cognome, m.anno - a.annonascita AS eta
FROM atleti a NATURAL JOIN medaglie m 
WHERE m.anno - a.annonascita <=ALL (SELECT m1.anno - a1.annonascita
				    FROM atleti a1 NATURAL JOIN medaglie m1
				    WHERE a1.nazione = a.nazione);


-- 9) Trovare il nome e cognome dell'atleta che ha vinto piu' medaglie
-- e restituire il numero di medaglie vinte */

WITH medaglie_atleta(idatleta, num_med)
AS (SELECT idatleta, COUNT(*)
    FROM medaglie
    GROUP BY idatleta)
SELECT a.nome, a.cognome, m.num_med
FROM medaglie_atleta m NATURAL JOIN atleti a
WHERE m.num_med = (SELECT MAX(m2.num_med)
      		   FROM medaglie_atleta m2);


-- 10) Per ogni edizione, trovare l'id dell'atleta che ha vinto piu' medaglie e
-- restituire anche il numero di medaglie vinte */

WITH medaglie_edizione_atleta(edizione, idatleta, num_med)
AS (SELECT edizione, idatleta, COUNT(*)
    FROM medaglie
    GROUP BY edizione, idatleta)
SELECT m.edizione, m.idatleta, m.num_med
FROM medaglie_edizione_atleta m
WHERE m.num_med = (SELECT MAX(m2.num_med)
      		   FROM medaglie_edizione_atleta m2
		   WHERE m2.edizione = m.edizione);

-- 11) Inserire l'atleta spagnola Queralt Castellet
-- nata il 17 giugno 1989 con idatleta 26 che ha vinto
-- una medaglia d'argento nello sport Snowboard,
-- disciplina Halfpipe F a Pechino 2022
-- nell'edizione 24 (codice medaglia 134) */
INSERT INTO atleti
VALUES (26, 'Queralt', 'Castellet', 'Spagna', 'F', 1989);

INSERT INTO medaglie
VALUES (134, 'Argento', 'Snowboard', 'Halfpipe F', 26, 2022, 24);


-- 12) Per ogni nazione restituire il numero di medaglie d'oro vinte dagli uomini e
-- il numero di medaglie d'oro  vinte dalle donne nello sport 'Sci Alpino'.
-- Se in una nazione nessun uomo o/e nessuna donna ha vinto medaglie 
-- d’oro deve essere riportato il valore 0 per gli uomini e/o per le donne.
-- Si assuma che ci sia almeno un atleta o un'atleta per nazione. 
SELECT a.nazione,
    SUM(CASE WHEN a.sesso = 'M' AND m.sport = 'Sci Alpino' AND m.tipo = 'Oro' THEN 1 ELSE 0 END) AS med_uomini,
    SUM(CASE WHEN a.sesso = 'F' AND m.sport = 'Sci Alpino' AND m.tipo = 'Oro' THEN 1 ELSE 0 END) AS med_donne
FROM atleti a LEFT JOIN medaglie m ON a.idatleta = m.idatleta 
GROUP BY a.nazione;


-- 13) Inserire l'atleta William Flaherty nato il 9 maggio 2004 con idatleta 25 che e' un atleta del Porto Rico. Il Porto Rico ha un'estensione di 8868 km2 e numabitanti 3205691
INSERT INTO nazioni
VALUES ('Porto Rico', 8868, 3205691);

INSERT INTO atleti
VALUES (25, 'William', 'Flaherty', 'Porto Rico', 'M', 2004);


-- 14) Restituire gli atleti (tutte le informazioni) che non hanno vinto alcuna medaglia
SELECT *
FROM atleti
WHERE idatleta NOT IN (SELECT idatleta
      	       	       FROM medaglie);


-- 15) Per ogni nazione restituire il numero di medaglie vinte. Se non ha vinto alcuna medaglia restituire 0.
-- Si assuma che ci sia almeno un atleta o un'atleta per nazione.
-- Il risutato deve essere ordinato in modo non decrescente ripetto al numero di medaglie vinte.
SELECT a.nazione, COUNT(m.codice) AS num_med_vinte
FROM atleti a NATURAL LEFT JOIN medaglie m
GROUP BY a.nazione
ORDER BY num_med_vinte;


-- 16) Cancellare le nazioni che non hanno mai vinto alcuna medaglia e 
-- cancellare anche gli atleti di quella nazione.
-- Si assuma che ci sia almeno un atleta o un'atleta per nazione. 
DELETE FROM atleti
WHERE nazione NOT IN (SELECT a.nazione
      	      	      FROM atleti a NATURAL JOIN medaglie m);

DELETE FROM nazioni
WHERE nome NOT IN (SELECT a.nazione
      	      	      FROM atleti a NATURAL JOIN medaglie m);


