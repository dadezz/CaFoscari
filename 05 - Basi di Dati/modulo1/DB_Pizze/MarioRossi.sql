/*Trovare il codice delle pizze ordinate più di 3 volte da Mario Rossi
SELECT 
	O.codpizza 
FROM 
	ordini O 
WHERE 
	O.nomecliente = "Mario Rossi"
GROUP BY 
	codpizza
HAVING 
	COUNT(*)>3
*/

/*Trovare il codice delle pizze ordinate al più tre volte da Mario Rossi.

Mi basta modificare il count in <= ? 
no, perché che succede con le pizze mai ordinate? non verrebbero incluse.
una soluzione è fare l'unione tra la query sopra (col minore) e le pizze mai ordinate.
Oppure:
*/
SELECT 
	p.codpizza
FROM 
	pizze P
	LEFT JOIN ordini O ON P.codpizza = O.codpizza AND O.nomecliente = 'Mario Rossi'
	/*left join per includere le pzze mai ordinate*/
WHERE 
	1=1 /*se il nomecliente fosse qui nel where, la pizza mai ordinata scomparirebbe dalla tabella*/
GROUP BY 
	P.codpizza
HAVING
	COUNT(o.Codordine)<3

