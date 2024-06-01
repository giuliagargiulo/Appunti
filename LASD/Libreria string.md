La libreria `<string>` può essere inclusa in un file tramite:
```cpp
#include <string>
```

Essa ci permette di utilizzare la classe `string`, al posto degli array di caratteri che si usano in C.
```cpp
#include <string>
string Nome = "Alan";
string Nome = ("Alan");
string Nome = {"Alan"};
```
---
#### Confronto tra stringhe
- Gli oggetti `string` sono confrontabili dal punto di vista ***lessicografico*** (posizione dei caratteri nella tabella ASCII) tramite gli operatori `"==", "!=", "<", ">", "<=", ">="`.
- Se una stringa è il prefisso di un'altra stringa, allora viene prima nell'ordinamento; ad esempio "mare" è minore di  "marea".
```cpp
string Stringa1 = "Alan Turing";
string Stringa2 = "Kurt Godel";

cout << "(String1 < String2):" << (Stringa1 < Stringa2) << endl; // restituisce 1

cout << "(String1 <= String2):" << (Stringa1 <= Stringa2) << endl; // restituisce 1

cout << "(String1 == String2):" << (Stringa1 == Stringa2) << endl; // restituisce 0

cout << "(String1 != String2): " << (Stringa1 != Stringa2) << endl; // restituisce 1

cout << "(String1 >= String2):" << (Stringa1 >= Stringa2) << endl; // restituisce 0

cout << "(String1 > String2):" << (Stringa1 > Stringa2) << endl; // restituisce 0
```
---
DA FARE
- Gli operatori di input e output usati per le stringhe sono `<<, >>`.
- Alcune funzioni utili della libreria string sono: size(), empty(), front(), back(), getline(cin, stringa), `[i]`??.
- friend?
---
#### Concatenazione di stringhe
La ***concatenazione*** di stringhe si ottiene tramite l'operatore `+`.
```cpp
string var = var1 + var2;
string var += var1;
```
---
#### Sottostringhe
Per le sottostringhe si utilizza la funzione substr($i$,$n$), che restituisce una sottostringa da posizione $i$ a posizione $i + n - 1$ .
```cpp
string var = "Alan";
cout << var.substr(1,2); // OUTPUT = "la"
```

>[!attention] 
>La funzione substr() può generare l'eccezione `out_of_range`.

---
 