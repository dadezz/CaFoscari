/*Trovare quante pizze non contengono mozzarella:
query universale: tutti gli ingredienti della pizza sono diversi da mozzarella*/
SELECT COUNT(*)
FROM 
	pizze P
WHERE
	p.codpizza NOT IN (
		SELECT R.codpizza
		FROM 
			ingredienti i 
			NATURAL JOIN ricette r
		WHERE 
			I.nome = 'mozzarella'
	)
/*
cosa mi dice la sottoselect? Non esiste un ingrediente di quella pizza il cui
nome è mozzarella.
È la negazione di ciò che mi serve.

QUINDI, cosa fa sta query?
prende ogni pizza e verifica la condizione, lasciandola nella tabella se
è verificata e togliendola altrimenti
*/
		
