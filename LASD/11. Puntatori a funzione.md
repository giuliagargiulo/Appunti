I puntatori a funzione possono essere utilizzati per:
1. Passare una funzione come parametro di altre funzioni (funzioni di callback) e richiamarla all'interno del corpo della funzione.
2. Chiamare funzioni diverse con lo stesso prototipo (cioè con nome diverso e stesso tipo e stessi parametri), conoscendone l'indirizzo.

```cpp
typedef type (*FunPtrName)(parameters); // definizione alla C

#include <functional>
typedef std::function <type(parameters)> FunPtrName; // definizione alla C++
```
---
#### Esempi
##### Caso 1: 
Passare una funzione come parametro di altre funzioni, in questo caso della funzione di Sort; questo ci permette di definire diversi tipi di sorting, senza dover ridefinire la funzione Sort, ma semplicemente passando come parametro un'altra funzione.
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

##### Caso 2:
Chiamare funzioni diverse con lo stesso prototipo.

```c++
#include <functional>

void functionA(int a){ return a+2; }
void functionB(int b){ return a+5; }
typedef std::function<void(int)> funPtr;
funPtr = functionA;
funPtr(5);

funPtr = functionB;
funPtr(10);


void process(int value, std::function<void(int)> callback){
	value +=2;
	callback(value);
}

int main(){
	process(5,functionA);
	process(5,functionB);
	return 0;
}


```


---
