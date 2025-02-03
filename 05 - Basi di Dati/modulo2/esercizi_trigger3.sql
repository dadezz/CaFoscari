-- Dipendenti(Id, Nome, AnnoNascita, Stipendio)
-- Manager(Id*, Area)
--      Id FK(Dipendenti)
-- Staff(Id*, Cod*)
--      Id FK(Dipendenti) Cod FK(Progetti)
-- Progetti(Cod, Nome, Budget, Responsabile*)
--      Responsabile FK(Manager)

-- Ogni progetto con un budget superiore a 10.000 deve avere un responsabile.
CREATE TRIGGER Responsabile BEFORE INSERT OR UPDATE ON Progetti
FOR EACH ROW
EXECUTE FUNCTION responsabile();

CREATE FUNCTION responsabile() RETURNS TRIGGER AS $$
BEGIN
    IF NEW.budget > 10000 AND NEW.Responsabile IS NULL
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- Ogni dipendente deve avere uno stipendio maggiore di 1.500 se ha meno di 35 anni, e di 2.000 se ne ha di più
CREATE TRIGGER StipendioMinimo BEFORE UPDATE OR INSERT ON Dipendenti
FOR EACH ROW
EXECUTE FUNCTION stipendiominimo();

CREATE FUNCTION stipendiominimo() RETURNS TRIGGER AS $$
BEGIN
    IF (NEW.Stipendio < 1500 AND 2025-NEW.AnnoNascita < 35)
        OR (NEW.Stipendio < 2000 AND 2025-NEW.AnnoNascita >= 35) 
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Un dipendente pu`o essere assegnato al massimo a 3 progetti.
CREATE TRIGGER Progetti3 BEFORE UPDATE OR INSERT ON Staff
FOR EACH ROW
EXECUTE FUNCTION progetti3();

CREATE FUNCTION progetti3() RETURNS TRIGGER AS $$
BEGIN
    if 3 < ANY (
        SELECT COUNT(s.Cod)
        FROM Staff s
        GROUP BY s.Id
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- Il manager responsabile di un progetto deve appartenere anche al suo staff.
CREATE TRIGGER ResPro BEFORE UPDATE OR INSERT ON Progetti
FOR EACH ROW
EXECUTE FUNCTION respro();

CREATE TRIGGER ResPro1 BEFORE DELETE ON Staff
FOR EACH ROW
EXECUTE FUNCTION respro1();

CREATE FUNCTION respro1() RETURNS TRIGGER AS $$
BEGIN
    IF NEW.id = (
        SELECT responsabile
        FROM progetti
        WHERE Cod = New.Cod
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

CREATE FUNCTION respro() RETURNS TRIGGER AS $$
BEGIN
    IF NEW.Responsabile NOT IN (
        SELECT Id
        FROM Staff
        WHERE Cod = New.Cod
    )
    THEN RETURN NULL;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql

-- Tutti i manager devono guadagnare almeno il 20% in più rispetto al salario medio dei dipendenti non manager.
CREATE TRIGGER Stipendiomaggiore AFTER UPDATE OR INSERT ON Dipendenti
FOR EACH STATEMENT
EXECUTE FUNCTION stipendiomedio();

CREATE FUNCTION stipendiomedio() RETURNS TRIGGER AS $$
DECLARE 
    media INT 
BEGIN 
    SELECT AVG(*) INTO media
    FROM Dipendenti d
    WHERE d.id NOT IN (
        SELECT m.Id 
        FROM Manager
    )

    IF (media * 1.2) > ANY (
        SELECT Stipendio
        FROM Dipendenti JOIN Manager USING (Id)
    )
    THEN RETURN OLD;
    END IF;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;