L'ereditarietà è una caratteristica fondamentale della programmazione ad oggetti; essa viene utilizzata per semplificare la creazione di nuove classi che condividono alcune caratteristiche con una classe esistente. 

L'idea alla base è quella di dire al compilatore che una nuova classe, detta ***classe derivata***, è ottenuta da una classe preesistente, detta ***classe base***, copiando il codice della classe base nella classe derivata, sostituendone qualche parte, qualora qualche metodo venisse sostituito.
Quindi la classe derivata ***eredita*** tutti gli attributi e tutti i metodi della classe base, tranne quelli definiti ***privati***; possiamo aggiungere poi metodi ed attributi e ridefinire alcuni metodi per differenziare la classe derivata.

Per dichiarare una classe derivata in C++ si utilizza la seguente sintassi:
```cpp
class ClassName : [virtual][private/ protected / public] BaseClassName{
	// Attributi e metodi della classe
};
```
---
#### Ereditarietà pubblica, privata e protetta
Di default l'ereditarietà è ***privata***, quindi tutti i membri ereditati diventano membri privati della classe derivata. E' possibile però richiedere un'ereditarietà pubblica o protetta, ma in ogni caso **non si può alterare il grado di protezione di un membro ereditato**, quindi:
- I membri privati rimangono quindi privati e non sono accessibili dalla classe derivata in ogni caso.
- Con l'ereditarietà pubblica i membri ereditati mantengono lo stesso grado di protezione, quindi quelli public rimangono public e quelli protected rimangono protected.
- Con l'ereditarietà protetta i membri public diventano protected, mentre quelli protected rimangono tali.
- Con l'ereditarietà privata tutti i membri diventano privati.

---
#### Ereditarietà multipla
Il C++ consente l'ereditarietà multipla, consentendo ad una classe di ereditare le caratteristiche di più classi basi. Però l'ereditarietà multipla può generare alcuni problemi, come ad esempio il **name clash**: se una classe eredita da due classe che hanno un metodo con lo stesso nome, si crea una situazione di ambiguità e questo genera un **errore a tempo di esecuzione**, che può essere risolto specificando il percorso del metodo al quale ci stiamo riferendo:
```cpp
class Base1{
	public:
		void f();
};

class Base2{
	public:
		void f();
		void f2;
};

class Derived : public Base1, public Base2{
};

Derived d;
d.f(); // ERRORE a tempo di esecuzione!
d.Base1::f(); // chiamata a f di Base1
d.Base2::f(); // chiamata a f di Base2
```

##### Diamond problem e ereditarietà virtuale
Un altro problema ricorrente con l'ereditarietà multipla è la definizione di classi derivate a partire da classi base che condividono un antenato in comune; questo problema è chiamato ***diamond problem*** e può essere risolto grazie alla keyword `virtual` e al concetto di ***ereditarietà virtuale***.

![[Diamond problem.jpg|400]]

Senza l'ereditarietà virtuale, se due classi B e C, ereditano da A, ed una classe D eredita da B e C, allora D conterrà due copie dei membri della classe A: una copia tramite B e una tramite C. Queste copie sono accessibili indipendentemente tramite il metodo visto prima.

Attraverso l'utilizzo della keyword `virtual`si assicura che esista un'unica copia di quella classe nella gerarchia. Inoltre, il compilatore non si limita a copiare il contenuto della classe base nella classe derivata, ma inoltre inserisce nella classe derivata **un puntatore ad una istanza della classe base**; quindi quando una classe eredita più volte da una classe base virtuale, il compilatore inserisce solo una istanza della classe virtuale e fa si che tutti i puntatori a tale classe puntino a quell'unica istanza.

###### Costruttori e distruttori nelle classi derivate
Quando si costruisce un oggetto di una classe che ha più classi base, il costruttore della classe base viene chiamato nell'ordine in cui le classi base sono elencate nella definizione della classe derivata, mentre i distruttori nell'ordine opposto alle chiamate dei costruttori.

```cpp
class A{
	A();
	~A();
};

class B: A{
	B();
	~B();
};

class C: A{
	C();
	~C();
};

class D: B, C{
	D();
	~D();
};

int main(){
	D d;
}
```

I costruttori vengono chiamati nel seguente ordine A,B,A,C,D, mentre distruttori D,C,A,B,A.

Nel caso dell'ereditarietà virtuale invece:
```cpp
class A{
	A();
	~A();
};

class B: virtual A{
	B();
	~B();
};

class C: virtual A{
	C();
	~C();
};

class D: B, C{
	D();
	~D();
};

int main(){
	D d;
}
```

In questo caso l'ordine di chiamata dei costruttori è A,B,C,D e i distruttori D,C,B,A.

>[!Important]
>Creare una gerarchia senza ***virtual*** corrisponde alla visita in postOrder di un grafo senza colorazione(con ripetizioni), che quindi costa esponenziale sulla dimensione del grafo.