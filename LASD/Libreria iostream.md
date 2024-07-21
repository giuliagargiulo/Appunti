Un grafo è una struttura dati rappresentato da una coppia ordinata $G = (V, E)$, dove $V$ è l'insieme dei ***vertici*** ed $E$ è l'insieme degli archi del grafo $G$.
La libreria `<iostream>` può essere inclusa in un file tramite:
```cpp
#include <iostream>
```

Nella libreria `<iostream>` troviamo i principali operatori per le funzioni di **input** e **output**:

- Operatore ***put-to*** `<<`, da applicare a oggetti di tipo "ostream", ad esempio `cout`.
- Operatore ***get-from*** `>>`, da applicare a oggetti di tipo "istream", ad esempio `cin`.
##### Output stream (ostream)
1. cout
2. clog
3. cerr
##### Input stream (istream)
1. cin

```cpp
cout << "Hello:" << 8 << 'c';

string Nome;
uint i;
char c;
cin >> nome >> i >> c;
```

Per i [[tipi definiti dall'utente]] bisogna ridefinire gli operatori `>>` e `<<`, specificando al compilatore cosa fare:
```cpp
struct Studente{
	string Nome;
	string Cognome;
	string Matricola;
	uint id;
};
Studente var;

cout << var; // ERRORE! Bisogna ridefinire <<
cin >> var;  // ERRORE! Bisogna ridefinire >>

ostream & operator << (ostream os, const Studente & st){
return os << st.Nome << "-" << st.Cognome << "-" << st.Matricola << endl;
}

istream & operator >> (istream & is, Studente & st){
return is >> st.Nome >> st.Cognome >> st.Matricola >> st.id;
}
```

#### Classe istream

- good(), eof(), fail(), bad(), sono funzioni membro per l'analisi dello stato;
- get($c$) dove $c$ è di tipo `char`, getline($p$, $n$) dove $p$ è di tipo `char *`  ed $n$ è il numero di caratteri da leggere.

#### Classe ostream
- put($c$) dove $c$ è di tipo `char`, write($p$, $n$), dove $p$ è di tipo `const char *` ed $n$ è il numero di caratteri da scrivere.
---
