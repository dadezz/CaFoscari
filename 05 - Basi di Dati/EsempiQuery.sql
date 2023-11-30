/*
Tabelle:
Pizze(CodPizza PK, nome, tempoPrep, prezzo)
Ingredienti(codIngrediente PK, nome, quantitaMagazzino, costoBase)
Ricette(CodPizza PK FK{PIZZE}, CodIngrediente PK FK{INGREDIENTI}, quantita)
Ordini(CodOrdine PK, nomeCliente, indirizzoCliente, oraConsegna, CodPizza FK{PIZZE})
*/


/*
Trovare il nome delle pizze in cui almeno un ingrediente ha quantitaMagazzino = 0
*/

SELECT p.nome
FROM Pizze p JOIN Ricette r USING (CodPizza) JOIN Ingredienti i USING (CodIngrediente)
WHERE i.quantitaMagazzino = 0

/*
Trovare il nome e il prezzo delle pizze che contengono sia rucola che pomodori freschi
*/

SELECT p.nome, p.prezzo
FROM Pizze p JOIN Ricette r USING (CodPizza) JOIN Ingredienti i USING (CodIngrediente) 
    JOIN ricette r2 USING (CodPizza) JOIN Ingredienti i2 ON r2.CodIngrediente = i2.CodIngrediente
WHERE i.nome = "Rucola" AND i2.nome = "Pomodori freschi"

/*
Per ogni pizza, trovare il nome e quante volte è stat ordinata da Leo Ortolani
*/

SELECT p.nome, COUNT()
FROM Pizze p LEFT JOIN Ordini o ON P.CodPizza = o.CodPizza AND o.nomeCliente = "Leo Ortolani"
GROUP BY p.CodPizza, p.nome