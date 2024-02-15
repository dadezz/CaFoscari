/*
Trovare nome e tempo di prep delle pizze che contengono
almeno tre ingredienti e non hanno la cipolla
*/
SELECT 
	P.nome, p.tempoprep
FROM 	
	pizze p
	NATURAL JOIN ricette r 
WHERE
	p.codpizza NOT IN (
		SELECT r.codpizza
		FROM 
			ricette r
			NATURAL JOIN ingredienti i
		WHERE
			i.nome = 'cipolla'
	)
GROUP BY p.codpizza, p.nome, p.tempoprep
HAVING COUNT (*) >= 3
