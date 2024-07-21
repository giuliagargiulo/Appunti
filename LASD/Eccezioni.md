Per gestire le eccezioni in C++ si utilizza la seguente struttura:
```cpp
try{
	...
	throw someException();
	...
}
catch (someException exe)
{
	// gestione dell'eccezione
}
catch(...) // prende tutto quello non definito prima
{
	...
	throw; // risolleva l'eccezione (non è riuscito a risolverla)
}
```

- Nel costruttore delle eccezioni (in questo caso someException) è buona norma inserire un messaggio d'errore.

>[!important] 
>Per definire una funzione che non solleva alcuna eccezione si utilizza `noexcept`:
>```cpp
>type nameFunction(parameters) noexcept;
>```
>Funzioni contetenti allocazioni di memoria, istruzioni di copia o che modificano la struttura dati potrebbero sollevare eccezioni, quindi non vanno dichiarate noexcept.

---
#### Eccezioni della standard library
Alcune eccezioni utili della libreria standard sono (dalla più generale alla più specifica):
- exception
	- logic_error
		- lenght_error
		- out_of_range
	- runtime_error
		- overflow_error
		- underflow_error
	- bad_alloc
	
 
 E' meglio controllare prima quelle più specifiche e poi quelle più generali:
```cpp
try {
	throw logic_error("Some logic error.");
	throw length_error("A length error occurred!");
	throw out_of_range("An out-of-range access to some structure occurred!");
	throw runtime_error("Some runtime error.");
	throw overflow_error("An overflow occurred!");
	throw underflow_error("An underflow occurred!");
	throw bad_alloc();
	throw 25;
}
catch (length_error & exc) {
	cout << "Length error: " << exc.what() << endl;
	throw;
}

catch (logic_error & exc) {
	cout << "Logic error: " << exc.what() << endl;
}
catch (overflow_error & exc) {
	cout << "Overflow error: " << exc.what() << endl;
}
catch (runtime_error & exc) {
	cout << "Runtime error: " << exc.what() << endl;
}
catch (bad_alloc & exc) {
	cout << "Bad allocation: " << exc.what() << endl;
}
catch (exception & exc) {
	cout << "All unmanaged standard exceptions reach this point!" <<
		 exc.what() << endl;

}
catch (...) {
	cout << "All unmanaged non-standard exceptions reach this point!" << endl;
	throw;
}
```

---
