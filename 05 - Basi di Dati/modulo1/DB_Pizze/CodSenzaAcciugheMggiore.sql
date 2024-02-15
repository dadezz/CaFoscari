/*
Per ogni cliente trovare il codice della pizza (delle pizze) che non ha acciunghe ordinata dal clinete il maggior numero di volte
*/

/*maggior numero di volte -> ricerca del massimo -> uso vista*/
/*tutte quelle che non contengono acciughe -> quantificazionen universale*/
CREATE VIEW PizzeNoAcciughe (NomeCliente, CodPizza, numeroDiOrdini)
AS
    SELECT NomeCliente, CodPizza, COUNT(*)
    FROM Ordini 
    WHERE CodPizza NOT IN (
        SELECT 
        FROM Ingredienti i NATURAL JOIN Ricette
        WHERE i.nome = 'acciuga'
    )
    GROUP BY NomeCliente, CodPizza 

SELECT pn.NomeCliente, pn.CodPizza
FROM PizzeNoAcciughe pn
WHERE pn.num = (
    /*è un masimo relativo, non assoluto*/
    SELECT MAX(pn2.num)
    FROM PizzeNoAcciughe pn2
    WHERE pn2.NomeCliente = pn.NomeCliente
)

/*la query va bene così, mancherebbe qualcosa: se il
 cliente non ha mai ordinato pizze senza acciughe non compare*/

UNION 

SELECT pn.NomeCliente, 'NESSUNA PIZZA'
FROM Ordini o LEFT JOIN PizzeNoAcciughe pn USING (NomeCliente)
WHERE pn.NomeCliente IS NULL

/*sta ultima qui non era contemplata in esame lol*/