I puntatori a funzione possono essere utilizzati per:
1. Passare una funzione come parametro di altre funzioni
2. Funzioni di callback

Un puntatore a funzione permette la chiamata di funzioni diverse con lo stesso prototipo conoscendone l'indirizzo.

```cpp
typedef type (*FunName)(parameters); // definizione alla C

#include <functional>
typedef std::function <type(parameters)> FunName; // definizione alla C++
```

#### Esempi

```cpp
bool (* Compare)(int x, int y);

void Sort(int * A, int n, Compare cmp){
	if (cmp(x, y)){ 
		...
	}
	else{
		...
	}
}
```

```cpp
bool LessThen(int x, int y){return (x < y)}
bool GreaterThen(int x, int y){return(x > y)}
bool Compare(int x, int y){...}
Compare fun = &LessThen;
Sort(A, 10, &LessThen);  // Sort(A, 10, fun);
Sort(A, 10, &GreaterThen);
```
---
