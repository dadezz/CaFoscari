-- Attori(CodiceAtt, Nome, Cognome, AnnoNascita)
-- Film(CodiceFilm, Titolo, AnnoProduzione, Regista, TotaleIncasso)
-- AttoriFilm(CodiceFilm, CodiceAtt, Compenso)
--      CodiceFilm FK(Film) CodiceAtt FK(Attori)

-- Ogni film deve aver incassato pi`u di 500 mila euro se precedente al 2000 e 1 milione se successivo
-- (incluso il 2000).
CREATE TRIGGER Incasso BEFORE UPDATE ON Film
FOR EACH ROW
EXECUTE FUNCTION incasso();

CREATE FUNCTION incasso() RETURNS TRIGGER AS $$
BEGIN 
    IF (NEW.TotaleIncasso < 500000 AND NEW.AnnoProduzione < 2000)
        OR (NEW.TotaleIncasso < 1000000 AND NEW.AnnoProduzione >= 2000)
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE  plpgsql

-- Non devono esserci due film con lo stesso titolo a distanza di meno di cinque anni.
CREATE TRIGGER StessoTitolo 