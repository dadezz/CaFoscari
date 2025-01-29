Product(maker, model, type)
PC(model*, speed, ram, hd, price)
Laptop(model*, speed, ram, hd, screen, price)
Printer(model*, color, type, price)

-- nessun produttore di pc può produrre anche laptop

-- il problema può essere dato da insert o update su product

-- il mantenimento dell'invariante va controllato per ogni riga

-- bisogna bloccare l'operazione

CREATE TRIGGER NoPcLaptop BEFORE INSERT OR UPDATE 
ON Product
FOR EACH ROW
EXECUTE FUNCTION nopclaptop()


CREATE FUNCTION nopclaptop RETURN TRIGGER AS $$
BEGIN
    IF (NEW.type = 'PC' and EXISTS (
        SELECT 1 
        FROM Product p
        WHERE p.maker = NEW.maker AND p.type  = 'Laptop'
        )
        OR 
        NEW.type = 'Laptop' and EXISTS (
        SELECT 1 
        FROM Product p
        WHERE p.maker = NEW.maker AND p.type  = 'PC'
        )
    ) 
    THEN
        RETURN NULL;
    END IF;
    RETURN NEW;
END;    
$$ LANGUAGE plpgsql


-- Se un laptop ha pi`u memoria di un PC, allora deve anche costare di più
-- di tale PC

-- il problema è in caso di insert o update in laptop e pc.
-- va bene per riga
-- bisogna bloccare l'operazione

CREATE TRIGGER laptopMemoria BEFORE INSERT OR UPDATE 
ON Laptop
FOR EACH ROW
EXECUTE FUNCTION laptop_memoria()

CREATE FUNCTION laptop_memoria() RETURN TRIGGER AS $$
BEGIN
    IF EXISTS (
        SELECT 1
        FROM pc p
        WHERE p.ram < NEW.ram AND p.price >= NEW.price
    )
    THEN RETURN NULL;
END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- da fare uguale per l'altra tavbella

----------------------------------------------------------

-- il modello di un prodotto deve anche essere il moello di un pc, di un laptop o di una stampante

-- insert o update su product, ma anche delete sulle altre 3 tabelle (ne scrivo solo 1, le altre 2 sono analoghe)
CREATE TRIGGER ModelloProdotto BEFORE UPDATE OR INSERT 
ON Product
FOR EACH ROW
EXECUTE FUNCTION modelloprodotto()

CREATE FUNCTION modelloprodotto() RETURN TRIGGER AS $$
BEGIN 
    IF (
        NOT EXISTS (
            SELECT 1
            FROM PC p
            WHERE NEW.model = p.model
        )
        AND NOT EXISTS (
            SELECT 1
            FROM Laptop p
            WHERE NEW.model = p.model
        )
        AND NOT EXISTS (
            SELECT 1
            FROM Printer p
            WHERE NEW.model = p.model
        )
    ) THEN
    RETURN NULL;
END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql


CREATE TRIGGER ModelloProdotto2 BEFORE DELETE ON Laptop
FOR EACH ROW
EXECUTE FUNCTION modelloprodotto2()

CREATE FUNCTION modelloprodotto2() RETURN TRIGGER AS $$
BEGIN
    IF (
        OLD.model IN (
            SELECT model 
            FROM Product
        )
    ) 
    THEN
        RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- HO SBAGLIATO, DEVO PROPAGARE LA CANCELLAZIONE SULLA TABELLA PRODUCT

CREATE TRIGGER ModelloProdotto3 AFTER DELETE ON Laptop
FOR EACH STATEMENT 
EXECUTE FUNCTION modelloprodotto3()

CREATE FUNCTION modelloprodotto3()  RETURN TRIGGER AS $$
BEGIN
    DELETE FROM Product WHERE model = OLD.model;
END;
$$ LANGUAGE plpgsql
------------------------------------------------------------------------
-- Quando il prezzo di un PC viene alzato, verificare che non vi sia gi`a
-- un laptop pi`u veloce di prezzo inferiore o uguale.

CREATE TRIGGER PrezzoMigliore BEFORE UPDATE ON PC 
FOR EACH STATEMENT EXECUTE FUNCTION prezzomigliore()

CREATE FUNCTION prezzomigliore() RETURN TRIGGER AS $$
BEGIN
    IF (
        NEW.price >= (
            SELECT MAX(price)
            FROM Laptop
            WHERE speed > NEW.speed
        )
    ) THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-------------------------------------------------------------------------
-- Quando vengono inseriti dei nuovi laptop, controllare che il prezzo
-- medio dei laptop per ciascun produttore sia almeno 1500.
CREATE TRIGGER prezzoMedio AFTER INSERT ON Laptop
FOR EACH STATEMENT 
EXECUTE FUNCTION prezzomedio()

CREATE FUNCTION prezzomedio() RETURN TRIGGER AS $$
BEGIN 
    IF (
        1500 > (
            SELECT AVG(l.price)
            FROM Laptop l JOIN Product p ON l.model = p.model
            WHERE p.maker = (
                SELECT maker
                FROM Product pr
                WHERE pr.model = NEW.model
            )
        )
    ) THEN
        DELETE FROM laptop WHERE model IN (
            SELECT model FROM NEW
        )
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql

--------------------------------------------------------------------------
-- Quando viene inserita una nuova stampante a colori, essa deve
-- costare di pi`u di qualsiasi stampante in bianco e nero.
CREATE TRIGGER Sttampante BEFORE INSERT ON Printer
FOR EACH ROW
EXECUTE FUNCTION Stampante() 

CREATE FUNCTION Stampante() RETURN TRIGGER AS $$
BEGIN
    IF NEW.color = TRUE and NEW.price < ANY (
        SELECT price
        FROM Printer
        WHERE color = FALSE
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-----------------------------------------------------------------------------
-- – Attori(CodiceAtt, Nome, Cognome, AnnoNascita)
-- – Film(CodiceFilm, Titolo, AnnoProduzione, Regista, TotaleIncasso)
-- – AttoriFilm(CodiceFilm, CodiceAtt, Compenso)
-- CodiceFilm FK(Film) CodiceAtt FK(Attori)

-- gni film deve aver incassato pi`u di 500 mila euro se precedente al 2000 
-- e 1 milione se successivo (incluso il 2000)

CREATE TRIGGER Incasso BEFORE UPDATE OR INSERT ON Film
FOR EACH ROW
EXECUTE FUNCTION incasso();

CREATE FUNCTION incasso() RETURNS TRIGGER AS $$
BEGIN
    IF ((NEW.AnnoProduzione < 2000 AND NEW.TotaleIncasso <= 500000) OR
        (NEW.AnnoProduzione >= 2000 AND NEW.TotaleIncasso <= 1000000))
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- eventualmente  esprimibile tramite check:
ALTER TABLE Film
ADD CONSTRAINT check_incasso CHECK ((NEW.AnnoProduzione < 2000 AND NEW.TotaleIncasso > 500000) OR
        (NEW.AnnoProduzione >= 2000 AND NEW.TotaleIncasso > 1000000))

------------------------------------------------------------------------------
-- Non devono esserci due film con lo stesso titolo a distanza di meno di cinque anni.

CREATE TRIGGER StessoTitolo BEFORE INSERT OR UPDATE ON Film
FOR EACH ROW
EXECUTE FUNCTION stessotitolo();

CREATE FUNCTION stessotitolo() RETURNS TRIGGER AS $$
BEGIN
    IF EXISTS (
        SELECT 1
        FROM film f
        WHERE f.titolo = NEW.titolo AND ABS(f.AnnoProduzione - NEW.AnnoProduzione) <= 5
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-----------------------------------------------------------------------------------
-- Un film deve avere minimo 5 attori
CREATE TRIGGER Minimo5 AFTER DELETE AttoriFilm
FOR EACH STATEMENT
EXECUTE FUNCTION minimo5();

CREATE FUNCTION minimo5() RETURNS TRIGGER AS $$
BEGIN
    IF  (
        SELECT COUNT(*)
        FROM Film JOIN AttoriFilm USING CodiceFilm
        WHERE CodiceFilm = OLD.CodiceFilm
    ) < 5
    THEN
        INSERT INTO AttoriFilm (SELECT * FROM OLD TABLE);
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql

CREATE TRIGGER Minimo5_ BEFORE UPDATE OR INSERT ON Film
FOR EACH 
-- usa la stessa funzione, ma al posto di old usa new e c'è retur null e return null