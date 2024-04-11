Un template permette di scrivere codice generico, cioè codice che funziona con diversi [[Tipi Fondamentali|tipi]] di dati (char, int, float, double,...), senza doverlo riscrivere ogni volta per ogni tipo.

Ad esempio, creiamo un template Data ed un vettore di tipo generico "Data":
###### Vector.cpp
```cpp
template <typename Data>
Vector <Data>::Vector(uint n){
	Elements = new Data[n];
	size = n;
}

template <typename Data>
Vector <Data>:: ~Vector(){
	delete[] Elements;
}
```
- Non ho new e detete nude in Vector.
###### Vector.hpp
```cpp
template <typename Data>
 class Vector{
	 private:
		 uint size = 0;
		 Data * Elements = nullptr;
	public:
		Vector() = default;
		Vector(uint n);
		~Vector();
		Data & operator[](ulong);
 };
 #include "Vector.cpp"
```

Quando andremo a dichiarare un nuovo oggetto di tipo vettore (Vector), dobbiamo specificare il tipo tra parentesi angolari <>, per sostituirlo al template "Data".
###### main.cpp
```cpp
#include "Vector.hpp"
int main(){
	Vector<int> vec(5);
	vec[0] = 3;
	cout << vec[0];
	return 0;
}
```
---
