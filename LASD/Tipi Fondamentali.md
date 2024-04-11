---
Data: 13/03/2024
---
## Tipi base
- `bool`
- `(const) char`
- `(unsigned)(const) int, short, long, long int, long long int`
- `(unsigned)(const) float, double, long double`

Per dichiarare una variabile:
```cpp
type varname [= value];
type varname[num_elements][={val_0,..., val_n}];
const type varname = value;
```

Ad esempio:
```cpp
unsigned int x = 3;
double vector[3] = {0.1, 2, 5.7}
long matrix[3][2] = {{0,1},{2,3},{4,5}};
const double pi = 3.14;
```
---
## Puntatori

`type * varname [= default address]`

```cpp
char c = 'a';
char * p = &c;
cout<< *p <<endl;
p = nullptr;   // corrisponde alla macro NULL di C
```

### Puntatore a void

`void * varname [= ...]`

```cpp
char c = 'a';
void * p = &c;
cout<< *p <<endl; // Errore!
cout<< *((char*)p)<<endl;  // OK! Casting esplicito all C
cout<< *(static_cast<char*>(p))<<endl;  // OK! Casting esplicito all C++
```

### Puntatore costante e puntatore a costante
```cpp
const char c = 'b';
char *p = &c;   // Errore!  
const char * p = &c; // OK!  // puntatore costante a variabile costante
```
---
## Riferimenti

Un riferimento può essere visto come un puntatore non NULL, infatti deve per forza "riferirsi" a qualcosa, non ha vita propria.

`type & varname = ...`

#### Riferimento:
```cpp
uint d = 7;
uint &e = d;
e++;      //(= d++)
cout<<d;  // stampa 8
```

>[!warning] 
> ```cpp
> uint &e = 1; // ERRORE!
>```
#### Puntatore:
```cpp
uint d = 7;
uint *p = &d; 
(*p)++;    //(= d++)  
cout<<d;   // stampa 8
```
#### Variabile:
```cpp
uint d = 7;
uint e = d; 
e++;      //(= d++)
cout<<d;  // stampa 7
```

### Riferimento temporaneo

 Un riferimento temporaneo viene distrutto appena una chiamata a funzione distrugge quell'area di memoria.
`type && varname = ...`

---
## Oggetti

```cpp
ObjectType f();
ObjectType var = f();    // copia del valore
ObjectType var = std::move(f());  // spostamento del valore
ObjectType &&var = f(); // riferimento Rvalue
Object * f();  // necessaria allocazione dinamica
```

```cpp
string f()
string var = f();  // copia della stringa
string && var = f(); // riferimento temporaneo del valore di ritorno
string & var = f(); // Errato!
string var1 = std::move(f()); // spostamento del valore
string var2 = std::move(var); // spostamento del valore
```
