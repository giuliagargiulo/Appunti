---
author: Giulia Gargiulo
---
Per creare uno schema di DB si usa il comando:
`CREATE SCHEMA nomeSchema [AUTHORIZATION nomeUtente]`

Uno schema include ***tabelle***, ***domini***, ***viste*** e altri costrutti e può essere definito come un ***contenitore logico***.

---
## Creazione delle tabelle

```SQL
CREATE TABLE <nomeSchema>.<nomeTabella>(
<nomeAttributo1> <tipo>,
<nomeAttributo2> <tipo>,
COSTRAINT <nomeVincolo> <vincolo>;
)
```

>[!example]
>Creazione tabella Studenti : S $\leftarrow$ Studenti(Nome, Cognome, Matricola(PK), codFisc, dataNascita)
>```SQL
>create table uni.Studenti(  
>	Nome varchar(20) NOT NULL,  
>	Cognome varchar(20),  
>	Matricola varchar(9),
>	codFisc char(16),
>	dataNascita date,
>	CONSTRAINT Matricola PRIMARY KEY(Matricola)  
);
>```

---
## Tipi di dato
#### Dati numerici
- Interi (Integer, int, smallint)
- Reali (float, real, double precision)
- Numeri formattati (DECIMAL(i ,j),)......

#### Stringhe di caratteri
- A lunghezza fissa (`CHAR(n), CHARACTER(n)`)
- A lunghezza variabile (`VARCHAR(n), CHARVARYING(n))
- Per default il numero minimo di caratteri è 1.

#### Stringhe di bit
- A lunghezza fissa: `BIT(n)`
- ...

#### Boolean
Prevede True o False, ma ha una logica a tre valori, considerata l'esistenza del valore $NULL$.

#### Date
Ha come componenti Year, Month e Day; formato YYYY-MM-DD.

#### Time
Ha almeno 8 posizioni con componenti Hour, Minute, e Second; formato HH:MM:SS.

#### Domain
Tipo di dato che permette di creare ***domini*** personalizzati di valori:
`CREATE DOMAIN <nomeDominio> AS <tipoDatoBase>`
`CHECK <vincolo>

>[!Esempio]
>
>```SQL
>CREATE DOMAIN genere AS CHAR(1)
>CHECK genere = 'M' or genere = 'F'

---
## Alter Table
Serve a modificare una tabella già creata:
- aggiungendo o rimuovendo una `CONSTRAIN`;
- attivando o disattivando una `CONSTRAIN`;
- aggiungendo, rimuovendo o modificando un attributo.

```SQL
ALTER TABLE <nomeTabella> SET CONSTRAIN <nomeCostraint> DISABLED / ENABLED
ALTER TABLE <nomeTabella> DROP CONSTRAIN <nomeCostraint>
ALTER TABLE <nomeTabella> CREATE CONSTRAIN <nomeCostrain> <defVincolo>

ALTER TABLE <nomeTabella> ADD <nomeAttributo> <tipoAttributo>
ALTER TABLE <nomeTabella> DROP <nomeAttributo> CASCADE / RESTRICT
ALTER TABLE <nomeTabella> ALTER <nomeAttributo> DROP DEFAULT
```
---
## Drop
Serve per eliminare una ***tabella*** o uno ***schema***

```SQL
DROP TABLE <nomeTabella> CASCADE / RESTRICT
DROP SCHEMA <nomeSchema> CASCADE / RESTRICT
```