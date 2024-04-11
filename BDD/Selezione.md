---
author: Giulia Gargiulo
tags:
  - SQL
  - definizione
  - comandi
---
L'operazione di ***selezione*** lascia lo schema relazionale inalterato, ma modifica il numero di **tuple**(righe), selezionando solo le tuple che rispettano una determinata **condizione**.

Sia $S(A_{1}, \dots,A_{n})$ lo schema di relazione e sia $r$ la relazione; in ***algebra relazionale*** l'operazione di ***selezione*** si rappresenta come:
$$\LARGE{\sigma^{(r)}_{<condizione>}} $$ dove $condizione$= `<attributo> <operatore> <valore>` e operatore: <, >, =, <>.

## Selezione in SQL
```SQL
SELECT*
	FROM Studente
	WHERE (Voto > 27 and Cognome ='Rossi')
```
- Se la condizione è TRUE la riga viene selezionata;
- Cambia il numero di righe, stesso numero di attributi.

Condizioni di selezione:
- `<attributo> <op_confronto> <valore>`
- `<attributo> <op_relazione> <attributo>`
- `<attributo> IS [NOT] NULL`

`<op_confronto> = <, <=, >, >=, < >`
`<op_relazione> = and, not, or`

---
## Proiezione e Selezione
```SQL
SELECT [DISTINCT] <listaAttributi>
	FROM <nomeTabella> [AS alias]
	WHERE <espressioneBooleana>
```
$1)$ Viene eseguita prima l'operazione di ***selezione*** delle righe, tramite la ***WHERE***.
$2)$ Dopo viene eseguita l'operazione di ***proiezione***, cioè la selezione delle colonne, tramite la ***SELECT***.

>[!Note]
>Per eliminare i duplicati in SQL devo specificare DISTINCT.
