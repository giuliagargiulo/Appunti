---
author: Giulia Gargiulo
---
### Tipi di vincoli
#### 1. Vincoli di Dominio
Esprimono delle restrizioni sui valori del dominio di un ***singolo attributo***; sono realizzati tramite:
- una condizione da controllare nella dichiarazione dell'attributo, ad esempio `CHECK(voto>= 18 and voto<=30`
- definendo un tipo tramite da dichiarazione di un ***dominio*** `CREATE DOMAIN`. In questo caso disaccoppio la definizione del vincolo da quella della tabella.
#### 2. Vincoli di N-upla
Sono vincoli che coinvolgono più attributi di una ***stessa*** riga **(n-upla)**; si definiscono tramite `CHECK CONSTRAINT` alla fine della tabella.

>[!Note]
>I vincoli di dominio e di n-upla sono facili da controllare, il controllo viene effettuato all'inserimento o modifica nella tabella.
>
#### 3. Vincoli Intra-relazionali
Sono vincoli che coinvolgono l'intera tabella; si definiscono tramite:
- `PRIMARY KEY` e `UNIQUE`
- `CONSTRAINT <nome_vincolo> CHECK <espressione>`
#### 4. Vincoli Inter-relazionali
Sono vincoli che coinvolgono più tabelle; si definiscono tramite:
- `FOREIGN KEY`
- `ASSERTION` e `TRIGGER`

---
### Vincoli su attributi
- Vincolo di totalità: `[NULLABLE / NOT NULL]`.
- `[DEFAULT <valore>]`
- Vincolo di dominio:`[CHECK (espressione booleana)]`.
- Vincolo intra-relazionale: `[PRIMARY KEY][UNIQUE]`.
### Vincoli su tabella
```SQL
CREATE TABLE tabella
(
<nomeAttributo1> <tipo>,
<nomeAttributo2> <tipo>,
CONSTRAINT <nomeVincolo> <vincolo>
);
```

`<vincolo>:`
- `CHECK (<espressione booleana>)`
- `UNIQUE (<listaAttributi>)`
- `PRIMARY KEY (<listaAttributi>)`
- `FOREIGN KEY (<listaAttributiFK>) REFERENCES <nomeTabella> <listaAttributiPK>`

### Vincolo di Foreign Key
`FOREIGN KEY(listaAttributiFK) REFERENCES <nomeTabella> <listaAttributiPK>
E' un vincolo inter-relazionale perché coinvolge due tabelle diverse e va verificato in fase di inserimento.

Dove:
- listaAttributiFK è la lista dei attributi che sono FK nella tabella che sto creando;
- listaAttributiPK è la lista di attributi che compongono la chiave primaria nella tabella referenziata.

>[!important]
>Gli attributi referenziati devono essere PK nella tabella <nomeTabella> a cui si fa riferimento ed inoltre devono essere in corrispondenza, cioè stesso numero di attributi, stesso tipo e stessa posizione; il nome non conta.


>[!example] 
>***Schema***: 
>$\textbf{Studente}(\underline{Matricola}, codFisc, Nome, Cognome, dataNascita)$
>$\textbf{Corso}(\underline{Nome}, \underline{Anno}, Descrizione)$
> $\textbf{Esame}(\underline{NomeCorso(FK)}, \underline{Anno(FK)}, \underline{Matricola(FK)}, Data, Voto, Lode)$
> ```SQL
> CREATE TABLE uni.Esame(
> 	NomeCorso char(4) NOT NULL
> 	Anno smallint NOT NULL
> 	MatricolaSt char(8) NOT NULL
> 	Data date NOT NULL
> 	Voto smallint NOT NULL CHECK(Voto >= 18 and Voto <= 30)
> 	Lode boolean
> )
> CONSTRAINT FK_Studente FOREIGN KEY(MatricolaSt) REFERENCES Studente(Matricola)
> CONSTRAINT FK_Corso FOREIGN KEY(NomeCorso, Anno) REFERENCES Corso(Nome,Anno)
> CONSTRAINT Voto_lode CHECK((Voto = 30 and Lode = TRUE) or (NOT Lode = TRUE))
> CONSTRAINT Unique_esame UNIQUE(MatricolaSt, NomeCorso, Anno)
> ```

#### Azioni sul vincolo di FK

Le azioni si specificano sulla FOREIGN KEY per definire cosa accade se la PK referenziata viene cancellata o modificata ed il vincolo di integrità rischia di essere compromesso. Esse sono parte della definizione di FK.

`ON DELETE <azione>`
`ON UPDATE <azione>`

`<azione> = NO ACTION / CASCADE / SET DEFAULT / SET NULL`
`CASCADE`: a cascata, cancella o modifica tutte le tuple collegate alla PK.

```SQL
FOREIGN KEY(listaAttributiFK) REFERENCES <nomeTabella> <listaAttributiPK>
[ON DELETE <azione>]
[ON UPDATE <azione>]
```
---
