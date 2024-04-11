---
author: Giulia Gargiulo
tags:
  - SQL
  - definizione
  - comandi
---

L'operazione di ***proiezione*** altera lo schema di relazione selezionando solo alcuni attributi, mentre il numero di **tuple**(righe) rimane inalterato.

Sia $S(A_{1}, \dots,A_{n})$ lo schema di relazione e sia $r$ la relazione; in ***algebra relazionale*** l'operazione di proiezione si rappresenta come:
$$\LARGE \pi^{(r)}_{(B_{1},\dots,B_{m}), \ dove \ {\{B_{1},\dots,B_{m} \} \subseteq \{ A_{1},\dots, A_{n} \} }} $$

## Proiezione in SQL
```SQL
SELECT Nome,Cognome
	FROM Studente
```
- Stesso numero di righe, cambia il numero di attributi.
