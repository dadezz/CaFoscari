/*
Eliminare gli ordini delle pizze per le quali un ingrediente ha
quantitamagazzino = 0
*/
DELETE FROM ordini
WHERE codpizza IN (
	SELECT r.codpizza
	FROM 
		ricette r
		NATURAL JOIN ingredienti i
		WHERE i.quantitamagazzino = 0)