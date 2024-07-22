---
Data: 14/03/2024
---
In C e C++ la gestione della memoria è compito del programmatore.
Per allocare e deallocare dinamicamente la memoria in `C++` si utilizzano rispettivamente gli operatori:
- `new`, che corrisponde alla funzione`malloc()`del linguaggio `C`;
- `delete`, che corrisponde alla funzione `free()` del linguaggio `C`.

Quando l'allocazione non ha avuto successo, l'operatore `new` solleva un'eccezione, cioè `bad-alloc`, non sostituisce `nullptr` quando fallisce (come in C) .

>[!attention] 
>1. L'uso degli operatori `new` e `delete` non va combinato con chiamate a funzione malloc, realloc e free.
>2. Non ci devono mai essere `new`e `delete` "nude", cioè sparse nel codice, l'allocazione e deallocazione della memoria dovrebbe essere sempre fatta nei ***costruttori*** o ***distruttori***.

#### Allocazione dinamica di un vettore
```cpp
uint num = espressione;
type * var = new type [num]; // num = dimensione array
...
delete[]var;
```

```cpp
const uint arraysize = 3;
uint * uiptr = new uint[arraysize]; // array non inizializzato
uint * uiptr1 = new uint[arraysize]{}; // array inizializzato a 0
uint * uiptr2 = new uint[arraysize]{5,6,7}; // array inizializzato con 5,6,7
delete[] uiptr;
delete[] uiptr1;
delete[] uiptr2;
```

#### Allocazione dinamica di un oggetto
```cpp
Objectype * var = new Objectype(); // nelle () eventuale valore di default
...
delete var;
```
---
