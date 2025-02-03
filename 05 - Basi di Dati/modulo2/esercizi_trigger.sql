-- Impiegati(CF, nome, cognome, annoN, sesso, stipendio, supervisor*)
--      supervisor FK(Impiegati)
-- Progetti(numeroP, nome, numDip*, dataInizio, budget)
--      numpDip FK(Dipartimenti)
-- Dipartimenti(numDip, nome, indirizzo, direttore*, dataInizioDir)
--      direttore FK(Impiegati)
-- LavoraSu(CFImp*, numeroP*, ore)
--      CFImp FK(Impiegati) numeroP FK(Progetti)

-- Gli impiegati devono essere maggiorenni al momento dell’assunzione (che coincide con il loro inserimento nella base di dati). 
-- Per semplicità, consideriamo solo l’anno di nascita1.
CREATE TRIGGER annodinascita BEFORE INSERT ON Impiegati
FOR EACH ROW
EXECUTE FUNCTION Annodinascita();

CREATE FUNCTION Annodinascita() RETURNS TRIGGER AS $$
BEGIN
    IF (EXTRACT(YEAR FROM CURRENT_DATE) - NEW.annoN) < 18
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Ciascun impiegato deve avere uno stipendio maggiore di 2000 euro se ha pi`u di 35 anni, e
-- comunque mai inferiore a 1500 euro.
CREATE TRIGGER Stipendio BEFORE INSERT OR UPDATE
ON Impiegati
EXECUTE FUNCTION stipendio();

CREATE FUNCTION stipendio() RETURNS TRIGGER AS $$
BEGIN
    IF NEW.stipendio < 1500
    THEN RETURN NULL;
    END IF;
    IF NEW.stipendio < 2000 AND (EXTRACT(YEAR FROM CURRENT_DATE) - NEW.annoN) > 35
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
LANGUAGE plpgsql

-- Un impiegato deve avere lo stipendio superiore a quello degli impiegati di cui `e supervisore.
CREATE TRIGGER StipendioSupervisore BEFORE INSERT OR UPDATE 
ON Impiegati
FOR EACH ROW
EXECUTE FUNCTION stipendiosupervisore();

CREATE FUNCTION stipendio() RETURNS TRIGGER AS $$
BEGIN
    IF (
        NEW.stipendio < ANY (
            SELECT Stipendio 
            FROM Impiegati i
            WHERE i. supervisor = NEW.CF AND i.CF <> NEW.cf
        )
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql


-- Il direttore assegnato ad un dipartimento deve essere un impiegato che lavora su almeno un
-- progetto di quel dipartimento e non deve essere assegnato come direttore di un altro dipartimento.
CREATE TRIGGER Dipartimento BEFORE INSERT OR UPDATE
ON Dipartimenti 
FOR EACH ROW
EXECUTE FUNCTION dipartimento()

CREATE FUNCTION dipartimento() RETURNS TRIGGER AS $$
BEGIN
    IF NOT EXISTS (
        SELECT 1
        FROM LavoraSu ls JOIN Progetti p USING numeroP
        WHERE NEW.direttore = ls.CFImp AND p.numDip = NEW.numDip
    )
    OR EXISTS (
        SELECT 1
        FROM Dipartimenti d
        WHERE NEW.direttore = d.direttore  AND d.numDip <> NEW.numDip
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- Il costo degli impiegati assegnati ad un progetto non deve superare il budget del progetto stesso.
-- Consideriamo un costo orario medio di 50 euro
CREATE TRIGGER Budget BEFORE UPDATE ON Progetti
FOR EACH ROW 
EXECUTE FUNCTION budget();

CREATE FUNCTION budget() RETURNS TRIGGER AS $$
BEGIN 
    IF NEW.budget < 50 * (
        SELECT SUM(ls.ore)
        FROM LavoraSu ls
        WHERE ls.numeroP = NEW.numeroP
        GROUP BY ls.numeroP
    ) 
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER Ore 
BEFORE UPDATE ON LavoraSu
FOR EACH ROW 
EXECUTE FUNCTION ore();



CREATE FUNCTION ore() RETURNS TRIGGER AS $$
DECLARE
    budget INT;
    total_hours INT;
BEGIN 
    -- Ottenere il budget del progetto associato
    SELECT p.budget INTO budget 
    FROM Progetti p
    WHERE p.numeroP = NEW.numeroP;

    -- Calcolare il totale delle ore lavorate per il progetto
    SELECT COALESCE(SUM(ls.ore), 0) INTO total_hours
    FROM LavoraSu ls
    WHERE ls.numeroP = NEW.numeroP;

    -- Verifica se il costo totale supera il budget
    IF budget < (total_hours * 50) THEN
        RAISE NOTICE 'Aggiornamento annullato: il costo totale degli impiegati assegnati supera il budget del progetto.';
        RETURN NULL;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

