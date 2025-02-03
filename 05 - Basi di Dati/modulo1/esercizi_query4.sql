-- Dottorandi(IdDott, Nome, Disciplina, Relatore*)
--      Relatore FK(Professore)
-- Professori(CF, Nome, Disciplina)
-- Corsi(Codice, Titolo, Professore*)
--      Professore FK(Professori)
-- Esami(IdStud*, CodiceCorso*, Data)
--      IdStud FK(Dottorandi) CodiceCorso FK(Corsi)

-- Restituire il titolo dei corsi e il codice fiscale dei docenti degli esami sostenuti da Chiara Pugliesi.
SELECT c.Titolo, p.Professore
FROM Corsi c JOIN Esami e ON c.Codice = e.CodiceCorso 
    JOIN Dottorandi d ON d.IdDott = e.IdStud
WHERE d.Nome = 'Chiara Pugliesi'

-- Trovare il numero di dottorandi che hanno sostenuto sia l’esame di Intelligenza Artificale che
-- l’esame di Sicurezza.
SELECT count(e1.IdStud)
FROM (Esami e1 JOIN Corsi c1 ON e1.CodiceCorso = c1.Codice) JOIN
     (Esami e2 JOIN Corsi c2 ON e2.CodiceCorso = c2.Codice) ON e1.IdStud = e2.idStud
WHERE e1.Titolo = 'Intelligenza Artificiale' AND e2.Titolo = "Sicurezza"

-- Per ogni professore, restituire il nome del professore e il numero di dottorandi di cui è relatore che
-- sono della sua disciplina e il numero dei dottorandi di cui è relatore che non sono della sua disci-
-- plina. Se il professore non ha dottorandi in una delle due categorie o in nessuna si deve restituire 0.
SELECT p.Nome, 
    COUNT(CASE WHEN p.disciplina = d.disciplina THEN 1 ELSE NULL END) AS dottStessa
    COUNT(CASE WHEN p.disciplina <> d.disciplina THEN 1 ELSE NULL END) AS dottAltra
FROM dottorandi d JOIN Professori p ON D.Relatore
GROUP by p.CF, p.Nome


-- Per ogni docente che ha erogato almeno un esame, restituire il nome del docente, il titolo del corso
-- per il quale ha erogato pi`u esami e il numero di studenti che ha sostenuto l’esame per quel corso.
WITH esami_per_corso(Nome, Titolo, Esami, Studenti) AS
SELECT p.Nome, p.CF, c.Titolo, COUNT(*), COUNT(DISTINCT e.IdStud)
FROM Professori p JOIN Corsi c ON P.CF = c.Professore
    JOIN Esami e ON c.Codice = e.CodiceCorso
GROUP BY p.CF, p.CF, c.Titolo

SELECT *
FROM esami_per_corso e
WHERE e.esami = (
    SELECT MAX(e2.esami)
    FROM esami_per_corso e2
    WHERE e.nome = e2.nome
)

-- Modificare il relatore di un dottorando se il relatore non è della sua stessa disciplina e inserire come
-- nuovo relatore il primo docente avente la sua stessa disciplina con cui il dottorando ha sostenuto
-- un esame. Se non ha sostenuto nessun esame con professori della sua disciplina mettere il relatore
-- a NULL. Si assuma che un dottorando svolga al pi`u un esame in un giorno.
with lista_docenti (matricola, docente, E.Data) AS
SELECT e.idStud, c.Professore, e.data
FROM esami e join corsi c on ... JOIN dottrandi d ON ... JOIN Professori p ON ... 
WHERE d.disciplina = p.disciplina
ORDER BY e.data

UPDATE TABLE Dottorandi 
SET Relatore = (
    SELECT docente
    FROM lista_docenti ls
    WHERE ls.docente  IN (
        SELECT 1 
        FROM lista_docenti ls2
        WHERE ls.matricola = IdStud
    )
)
WHERE disciplina <> (
    SELECT disciplina
    FROM professori
    WHERE relatore = CF
)
--------------------------------
-- BOH SOLUZIONE DI CHATGPT:
WITH lista_docenti AS (
    SELECT e.IdStud, c.Professore, e.Data
    FROM Esami e
    JOIN Corsi c ON e.CodiceCorso = c.Codice
    JOIN Dottorandi d ON e.IdStud = d.IdDott
    JOIN Professori p ON c.Professore = p.CF
    WHERE d.Disciplina = p.Disciplina
    ORDER BY e.Data
)

UPDATE Dottorandi d
SET d.Relatore = (
    SELECT COALESCE(
        (SELECT TOP 1 docente
         FROM lista_docenti ls
         WHERE ls.IdStud = d.IdDott
         ORDER BY ls.Data),
        NULL
    )
)
WHERE d.Relatore <> (
    SELECT p.CF
    FROM Professori p
    WHERE p.CF = d.Relatore
    AND p.Disciplina = d.Disciplina
);
