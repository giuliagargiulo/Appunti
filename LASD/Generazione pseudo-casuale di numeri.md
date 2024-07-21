Per la generazione di numeri pseudo-casuali in C++ si utilizzano alcune funzioni della libreria `<random>`:

```cpp
#include <random>
default_random_engine gen(random_device{}());
uniform_int_distribution <type> dist(i,j);
for(uint i=0; i<15; i++){
	cout << dist(gen);
}
```
 - `<type>`= int, uint, long,...
 - `dist`: distribuzione uniforme
 - $(i,j)$: range di valori.
