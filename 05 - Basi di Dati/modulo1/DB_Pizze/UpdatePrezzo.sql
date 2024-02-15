/*
Diminuire del 10% il prezzo della pizza se il costo di 
produzione è infreriore al 50% del prezzo della pizza
*/
UPDATE 
	pizze
SET 
	prezzo = prezzo * 0.9
WHERE 
	codpizza IN (
		SELECT 
		FROM
			pizze p
			JOIN ricette r USING (codipizza)
			JOIN ingredienti i USING (codingrediente)
		GROUP BY p.codpizza, p.prezzo
		HAVING SUM (i.costobase * rquantita)<p.prezzo*0.5
	)