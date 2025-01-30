-- Aereoporti(Citta, Nazione, NumPiste)
-- Voli(codVolo, GiornoSett, CittaPart*, OraPart, CittaArr*, OraArr, TipoAereo*)
--                   CittaPart FK(Aereoporti) CittaArr FK(Aereoporti) TipoAereo FK(Aerei)
-- Aerei(TipoAereo, NumPasseggeri, QtaMerci)


-- trovare il numero di voli internazionali che partono il giovedì da Napoli
SELECT COUNT(*)
FROM Voli v JOIN aeroporti a ON a.citta = v.cittaArr
WHERE CittaPart = Napoli AND GiornoSett = 'giovedì' AND n.nazione <> 'italia'

-- Cancellare gli aereoporti di cui non si conosce il numero delle piste e i voli che hanno come
-- partenza o arrivo tali aereoporti.
WITH aeroporti_senza_pista(citta) AS 
SELECT citta 
FROM Aereoporti
WHERE NumPiste IS NULL

DELETE FROM Voli
WHERE cittaPart IN (SELECT * FROM aeroporti_senza_pista)
OR   cittaArr IN (SELECT * FROM aeroporti_senza_pista)

DELETE FROM Aereoporti
WHERE citta IN (SELECT * FROM aeroporti_senza_pista)

--  Restituire le città francesi da cui partono più di venti voli alla settimana diretti in Italia.
SELECT a1.citta
FROM Aeroporti a1 JOIN Voli v ON a1.citta = v.cittaPart
    JOIN Aeroporti a2 ON a2.citta = v.cittaArr
WHERE a1.nazione = 'francia' AND a2.nazione = 'italia'
GROUP BY a1.citta
HAVING count(v.codVolo) > 20

-- Restituire gli aereoporti italiani che hanno solo voli interni. Risolvere questa query in due modi
-- diversi: (i) utilizzando operatori insiemistici (ii) con una sottoselect.
SELECT a1.citta
FROM Aeroporti a1 JOIN Voli v ON a1.citta = v.cittaPart
    JOIN Aeroporti a2 ON a2.citta = v.cittaArr
WHERE a1.nazione = 'italia' AND a2.nazione = 'italia' AND
    NOT EXISTS (
        SELECT 1
        FROM Aeroporti a1 JOIN Voli v ON a1.citta = v.cittaPart
        JOIN Aeroporti a2 ON a2.citta = v.cittaArr
        WHERE a1.nazione = 'italia' AND a2.nazione <> 'italia' 
    )
-- OPPURE 
SELECT DISTINCT a1.citta
FROM Aeroporti a1 JOIN Voli v ON a1.citta = v.cittaPart
    JOIN Aeroporti a2 ON a2.citta = v.cittaArr
WHERE a1.nazione = 'italia' AND a2.nazione = 'italia'
EXCEPT
SELECT a1.citta
FROM Aeroporti a1 JOIN Voli v ON a1.citta = v.cittaPart
    JOIN Aeroporti a2 ON a2.citta = v.cittaArr
WHERE a1.nazione = 'italia' AND a2.nazione <> 'italia'

-- Per ogni aereoporto per cui c’`e un volo, trovare il giorno della settimana da cui partono il massimo
-- numero di voli e restituire anche il numero di passeggeri complessivi.
WITH numero_di_voli_per_giorno(citta, giorno, numero_volo, numero_passeggeri) AS
SELECT a.citta, v.GiornoSett, COUNT(v.codVolo), COALESCE(SUM(aa.NumPasseggeri), 0)
FROM aeroporti a JOIN voli v ON a.citta = v.cittaPart
    JOIN aerei aa USING (TipoAereo)
GROUP BY a.citta, v.GiornoSett

SELECT n.citta, n.giorno, n.numero_passeggeri
FROM numero_di_voli_per_giorno n
WHERE n.numero_voli = (
    SELECT MAX(n2.numero_voli)
    FROM numero_di_voli_per_giorno n2
    WHERE n.citta = n2.citta
)