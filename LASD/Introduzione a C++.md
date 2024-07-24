---
Data: 12/03/2024
---
## Struttura modulare di un programma

### Un programma semplice 

***main.cpp*** (C++ program)
```cpp
#include <iostream>   // libreria standard di C++ per l'input/output
using namespace std;  // dichiarazione dello spazio dei nomi
int main(){
	cout<<"Hello World!"<<endl;  // endl si usa per andare a capo
	return 0; // opzionale
} 
```
- Dichiarare lo spazio dei nomi ci consente di accedere alle funzionalità di quello specifico spazio, senza doverlo specificare ogni volta; quello più comune è ***std***, che fa parte della libreria standard di C++.
- Se non specifichiamo lo spazio dei nomi, dobbiamo scrivere `std::`, ad esempio:
	`std::cout<< "Hello World!"<< std::endl`
- Per andare a capo posso usare anche `/n` come in C.


***build.sh*** (Bash script)
```
#/bin/bash
g++[-03] -o main main.cpp
```

- `-o main` indica l'output (file eseguibile) e il suo nome(main);
- `main.cpp` è il codice sorgente;
- `[-0],[-1],[-2],[-3]` sono i parametri di ottimizzazione del codice.

---
### Un programma più strutturato

***main.cpp***
```cpp
#include <iostream>
#include "test.hpp"  // rendo visibile il prototipo di test al main
using namespace std;
int main(){
	cout<< "Chiamata a funzione:";
	test();
}
```

***test.cpp***
```cpp
#include <iostream>
#include "test.hpp"
void test(){
	std::cout<< "OK!" <<end;
}
```

***test.hpp***
```cpp
#ifndef TEST_HPP  //istruzioni del preprocessore
#define TEST_HPP
void test();    // prototipo funzione test()
#endif
```
- `.hpp` = Header file
- Serve per creare i prototipi delle funzioni, in modo da renderle visibili al main.

>[!note] 
>- In test.cpp utilizzo `#include "test.hpp"` poichè se la funzione `test()` è definita in fondo al file, ed è chiamata prima, il compilatore sa che esiste, altrimenti terminerebbe con errore!
> - In questo caso posso anche ometterlo, perchè test.cpp contiene solo il corpo della funzione `test()`.

***build.sh***
```
#!/bin/bash
g++[-03] -o main test.cpp main.cpp
```
- Il compilatore compila tutti i file sorgente, in questo caso main.cpp e test.cpp.
- Se esistono tutte le funzioni chiamate, il ***linker*** unisce i vari file oggetto, altrimenti termina con errore.

>[!warning] 
>I file.cpp non si includono da nessuna parte!

---
