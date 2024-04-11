---
author: Giulia Gargiulo
Esame: 19-01-2023
---
## Creazione Database

```SQL
DROP SCHEMA IF EXISTS p CASCADE;  
CREATE SCHEMA p;  
  
CREATE TABLE p.Libro  
(  
    ISBN        integer,  
    Titolo      varchar(20),  
    Editore     varchar(20),  
    Anno        date,  
    Descrizione varchar(128),  
    CONSTRAINT PK_Libro PRIMARY KEY (ISBN)  
);  
  
CREATE TABLE p.Esemplare  
(  
    CodiceBarre   integer,  
    ISBN          integer,  
    Collocazione  varchar(20),  
    Prestito      boolean,  
    Consultazione boolean,  
    CONSTRAINT PK_Esemplare PRIMARY KEY (CodiceBarre),  
    CONSTRAINT FK_Esemplare FOREIGN KEY (ISBN) REFERENCES p.Libro (ISBN)  
);  
  
CREATE TABLE p.Profilo  
(  
    CodProfilo  integer,  
    MaxDurata   integer,  
    MaxPrestito integer,  
    CONSTRAINT PK_Profilo PRIMARY KEY (CodProfilo)  
);  
  
CREATE TABLE p.Utente  
(  
    CF         varchar(16),  
    CodProfilo integer,  
    Nome       varchar(20),  
    Cognome    varchar(20),  
    DataN      date,  
    CONSTRAINT PK_Utente PRIMARY KEY (CF),  
    CONSTRAINT FK_Utente FOREIGN KEY (CodProfilo) REFERENCES p.Profilo (CodProfilo)  
);  
  
CREATE TABLE p.Prenotazione  
(  
    CodPrenotazione integer,  
    ISBN            integer,  
    Utente          varchar(16),  
    Data            date,  
    CONSTRAINT PK_Prenotazione PRIMARY KEY (CodPrenotazione),  
    CONSTRAINT FK_Utente FOREIGN KEY (Utente) REFERENCES p.Utente (CF)  
);  
  
CREATE TABLE p.Prestito  
(  
    CodPrestito integer,  
    CodiceBarre integer,  
    Utente      varchar(16),  
    DataE       date,  
    DataS       date,  
    DataR       date,  
    DataSol     date,  
    CONSTRAINT PK_Prestito PRIMARY KEY (CodPrestito),  
    CONSTRAINT FK_Esemplare FOREIGN KEY (CodiceBarre) REFERENCES p.Esemplare (CodiceBarre),  
    CONSTRAINT FK_Utente FOREIGN KEY (Utente) REFERENCES p.Utente (CF)  
);
```
---
## Popolamento del database

```SQL
INSERT INTO p.Utente(CF)  
VALUES ('a'),  
       ('b'),  
       ('c'),  
       ('d');  
  
  
INSERT INTO p.Libro(ISBN, Titolo)  
VALUES (100, 'Mario'),  
       (200, 'Simone'),  
       (300, 'Mammanuele'),  
       (400, 'Giulia');  
  
INSERT INTO p.Esemplare(CodiceBarre, ISBN)  
VALUES (1111, 100),  
       (2222, 200),  
       (3333, 400),  
       (4444, 400),  
       (5555, 300);  
  
INSERT INTO p.Prenotazione(CodPrenotazione, ISBN, Utente, Data)  
VALUES (1, 100, 'a', '2022-02-02'),  
       (2, 200, 'b', '2021-01-01'),  
       (3, 300, 'c', '2021-02-02');  
  
  
INSERT INTO p.Prestito(CodPrestito, CodiceBarre, DataE, Utente, DataSol)  
VALUES (1, 1111, '2022-01-01', 'a',NULL),  
       (2, 1111, '2023-02-23', 'b',NULL),  
       (3, 2222, '2022-01-01', 'a', NULL),  
       (4, 3333, '2022-02-03', 'b', NULL),  
       (6, 4444, '2022-03-03', 'd', NULL),  
       (7, 4444, '2023-02-02', 'd', NULL),  
       (8, 1111, '2022-02-02', 'd', NULL),  
       (9, 1111, '2023-01-01', 'd', NULL),  
       (10, 2222, '2022-01-01', 'd', NULL),  
       (11, 3333, '2022-01-01', 'd', NULL),  
       (12, 1111, '2021-01-01', 'c', NULL),  
       (13, 4444, '2021-01-01', 'c', NULL),  
       (14, 4444, '2021-01-01', 'c', NULL),  
       (15, 1111, '2022-01-01', 'c', NULL);
```
## Update

```SQL
UPDATE p.Prestito SET DataSol ='2022-02-02' WHERE CodPrestito = 1;  
UPDATE p.Prestito SET DataSol ='2023-02-25' WHERE CodPrestito = 2;
```
---
## Query

***Traccia***: Si scriva un interrogazione in SQL che, se valutata, fornisce il titolo del libro che ha avuto nell'anno 2022 il maggior numero di prestiti (si intende per numero di prestiti di un libro il numero di prestiti di tutti i suoi esemplari).

```SQL
SELECT L.Titolo,  
       COUNT(ISBN) AS Conteggio  
FROM (p.Libro AS L  
    NATURAL JOIN p.Esemplare AS E)  
         JOIN p.Prestito AS PR ON PR.CodiceBarre = E.CodiceBarre  
WHERE EXTRACT(YEAR FROM PR.DataE) = 2022  
GROUP BY L.Titolo  
ORDER BY Conteggio DESC  
LIMIT 1;
```

---
## Trigger

***Implementare i seguenti trigger***:
1. Il primo trigger viene attivato quando viene inserita la **data di sollecito** per un prestito; l'effetto del trigger è che tutte le prenotazioni di quell'utente vengono automaticamente cancellate.  
```SQL
CREATE OR REPLACE FUNCTION crea_trigger1()  
    RETURNS TRIGGER AS  
$$  
BEGIN  
    DELETE FROM p.Prenotazione AS PRE  
    WHERE NEW.Utente = PRE.Utente;  
    RETURN NEW;  
END;  
$$  
    LANGUAGE plpgsql;  
  
CREATE TRIGGER annulla_prenotazioni  
    AFTER UPDATE ON p.Prestito  
    FOR EACH ROW  
    WHEN (NEW.DataSol IS NOT NULL)  
EXECUTE FUNCTION crea_trigger1();
```

2. Il secondo trigger viene attivato ad ogni richiesta di prestito. L'effetto è che bisogna controllare se l'utente ha una prenotazione per quel libro; in tal caso la prenotazione corrispondente va rimossa.

```SQL
```
