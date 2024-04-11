La programmazione orientata agli oggetti consente di aggregare in un'unica entità i dati e le tecniche per la loro manipolazione. Ciò è reso possibile dalla definizione di **classi** che espandono l'insieme di [[Tipi Fondamentali|tipi predefiniti]] previsti dallo standard C++.

 Per ogni oggetto avremo anche un insieme di funzioni specializzate, e diversi livelli di accesso per ogni sua proprietà. Una classe, quindi, definisce un'_interfaccia_ verso il mondo esterno, che consente di manipolarne di dati e, allo stesso tempo, maschera le dinamiche del suo funzionamento interno.

#### Definizione di una classe
```cpp
class ClassName{
	private:
		... // attributi e funzioni membro() privati, cioè accessibili 
			// solo dall'interno della classe;
	protected:
		... // attributi e metodi visibili solo ad altre classi 
			// nella gerarchia;
	public:
		... // attributi e metodi visibili a tutti.
};
```
##### Costruttori e distruttore
```cpp
// Costruttori
ClassName(); // default constructor
ClassName(parameters); // specific constructor
ClassName( const ClassName &) // copy constructor
ClassName(ClassName &&) noexcept; // move constructor

// Distrutture
~ClassName(); 
```
##### Operatori
```cpp
bool operator == (const ClassName &) cout noexcept; // confronto
ClassName & operator = (const ClassName &);  // copy assignment
ClassName & operator = (ClassName &&) noexcept; // move assignment
```

#### Definizione di classi e metodi(da rivedere)
L'applicazione della parola chiave `virtual` ai metodi di una classe consente di condizionare l'esecuzione del codice secondo il tipo dell'istanza dell'oggetto a cui si fa riferimento.

```cpp
class ClassName : [virtual][private/ protected / public] BaseClassName{
};

// Metodi
[virtual] type NameFun(parameters)[const][noexcept][override][=assignment]
// Pseudo assignment :=0 / = default / = delete
```

Definizione concreta di un metodo:
```cpp
type ClassName::FunName(parameters)[specifers]{codice}
```