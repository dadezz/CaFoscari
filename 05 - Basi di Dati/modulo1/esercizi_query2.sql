-- Libri(id, titolo, genere, nomeEditore, annoPubblicazione)
-- AutoriLibro(idLibro*, nomeAutore)
-- idLibro FK(Libri)
-- Prestiti(idP, idLibro*, numTessera*, dataDiPrestito, dataDiRiconsegna)
-- idLibro FK(Libri) numTessera FK(Utenti)
-- Utenti(numTessera, nome, indirizzo, telefono)

-- considerare l'ipotesi che non ci siano autori di libri aventi lo stesso nome

-- Restituire il titolo dei libri che non sono mai stati in prestito.
SELECT l.titolo, l.id
FROM Libri l
WHERE l.id NOT IN (
    SELECT l1.id
    FROM Libri l1 JOIN Prestiti p ON l1.id = p.idLibro)

-- oppure
SELECT l.titolo, l,id
FROM Libri l LEFT JOIN Prestiti p ON l.id = p.idLibro
WHERE p.idLibro IS NULL

--Per ogni autore, restituire il numero di libri che ha scritto e il numero di editori distinti per cui
--ha pubblicato.
SELECT al.NomeAutore, COUNT(al.idLibro), COUNT(DISTINCT l.nomeEditore)
FROM Libri l JOIN AutoriLibro al ON l.id = al.idLibro
GROUP BY al.nomeAutore

-- Restituire il nome degli utenti che hanno preso in prestito almeno due libri diversi dello stesso autore.
SELECT DISTINCT u1.nome, u1.NumTessera
FROM  Utenti u1 JOIN Prestiti p1 USING (numTessera) 
                JOIN Autorilibro al1 USING(IdLibro)
                JOIN Prestiti p2 USING (numTessera) 
                JOIN Autorilibro al2 USING(IdLibro)
WHERE p1.idP <> p2.idP AND al1.nomeAutore = al2.nomeAutore AND p1.idLibro <> p2.idLibro;

-- per ogni editore restituire oltre al nome dell’editore, il titolo del libro/libri pubblicato/i fra il
-- 1950 e il 2024 che ha/nno il massimo numero di autori.
WITH numero_di_autori(editore, idLIbro, titolo, nautori) AS
    SELECT l.nomeEditore, l.id,  l.Titolo, COUNT(al.NomeAutore)
    FROM Libri l JOIN AutoriLibro ON l.id = al.idLibro
    WHERE l.annoPubblicazione BETWEEN 1950 AND 2024
    GROUP BY l.editore, l.id, l.Titolo

SELECT ndu.editore, ndu.idLibro, ndu.Titolo
FROM numero_di_autori ndu
WHERE ndu.nautori = (
    SELECT MAX(ndu1.nautori)
    FROM numero_di_autori ndu1
    WHERE ndu1.editore = ndu.editore
)

-- Per ogni utente restituire il nome dell’utente, il numero di libri di genere giallo, il numero di
-- libri di genere fantasy e il numero di libri di genere avventura che ha preso in prestito. Se un
-- utente non ha preso alcun libro per quel genere restituire 0.
SELECT u.NumTessera, u.nome,
    COUNT(CASE WHEN genere='giallo' THEN 1 ELSE NULL END) AS gialli,
    COUNT(CASE WHEN genere='fantasy' THEN 1 ELSE NULL END) AS fantasy,
    COUNT(CASE WHEN genere='avventura' THEN 1 ELSE NULL END) AS avventura
FROM utenti u LEFT 
    LEFT JOIN prestiti p USING (NumTessera) 
    JOIN Libri l ON l.id = p.idLibro
GROUP BY u.NumTessera