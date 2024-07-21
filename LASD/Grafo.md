Un grafo è una struttura dati rappresentato da una coppia ordinata $G = (V, E)$, dove $V$ è l'insieme dei ***vertici*** ed $E$ è l'insieme degli archi del grafo $G$.
L'insieme degli archi $E$ è formato da ***coppie*** dell'insieme dei vertici: $E \subseteq V\times V$.

- Grafo ***non orientato***: $V =\{A,B,C,D,E,F\}, \ \ (A,D)\in E = (D,A)\in E$
- Grafo ***orientato***: l'insieme $E$ è formato da ***coppie ordinate*** di vertici, quindi $(A,D)\not = (D,A)$.

>[!note] 
>Ogni grafo non orientato può essere rappresentato da un grafo orientato:
> La classe dei grafi non orientati è contenuta nella classe dei grafi orientati.

1. Il grado di un vertice dipende dal tipo di grafo che stiamo analizzando:
	- Grafo ***non orientato***: il grado di un vertice è uguale al numero di archi che partono da quel vertice.
	- Grafo ***orientato***: il grado si divide in ***grado entrante*** (numero di archi entranti) e ***grado uscente***(numero di archi che partono dal vertice).

2. Un grafo si dice ***ciclico*** se al suo interno contiene un ciclo, cioè un percorso infinito.
	Al contrario, un grafo ***orientato*** si dice ***aciclico*** se non presenta cicli al suo interno.

3. E' difficile dare una definizione induttiva di grafo, perchè:
	- Se aggiungo un nuovo vertice al grafo, avrò soltanto archi che vanno dal nuovo vertice al grafo, ma non viceversa.
	-  Se rimuovo un vertice dal grafo, perdo anche gli archi da e verso quel vertice.

4. Un grafo $G' =(V', E')$ è un ***sottografo*** di $G \iff V'\subseteq V \ \land \ E'\cap(V'\times V)$.

---
### Percorso

Per ogni $u,v\in V$, un percorso $\large\pi$  che va da $u$ a $v$ in $G$ è una sequenza di vertici della forma $\large \pi = v_0v_1v_{2\dots}v_{k-1}v_k$ tale che: $v_{0}= u$ e $v_{k}= v$ e $\forall 0\leq i\leq k-1, (v_i,v_{i+1})\in E$, cioè deve esistere un arco da $v_{0}$ a $v_1$, da $v_1$ a $v_2$, $\dots$ fino all'arco da $v_{k-1}$ a $v_k$.

>[!important] 
>Quindi un vertice $v$ è raggiungibile da $u$ in $G$ $\iff$ esiste un percorso $\large \pi$ da $u$ a $v$ in $G$.

Consideriamo la seguente ***relazione*** che rappresenta la raggiungibilità in $G$: $Reach\subseteq V\times V$, $Reach$ è una relazione ***riflessiva*** e ***transitiva***:
- $(v,v)\in Reach$,  $\pi = v \implies$ percorso vuoto.
- $(u,z)\in Reach\  \land \  (z,v)\in Reach \implies (u,v)\in Reach$
---
### Rappresentazione di un grafo

Un grafo può essere rappresentato all'interno di un algoritmo in due modi:
- Tramite una ***matrice di adiacenza***, in cui se esiste un arco tra $u$ e $v$, nella matrice troveremo in posizione $M[u][v] = 1$, altrimenti 0.
- Tramite una ***lista di adiacenza***, in cui $\forall v \in V$ esiste una lista contenente tutti i vertici che hanno un arco entrante proveniente da $v$.

---
### Visita in ampiezza

Per visitare un grafo in ampiezza bisogna prima stabilire alcuni concetti:
1. Definire un concetto simile al "livello" degli alberi, sfruttando quindi la distanza tra i nodi.
2. Definire un ***vertice sorgente*** da cui far iniziare la visita.

Bisogna quindi definire un algoritmo che proceda per distanze e che permetta di ricostruire i percorsi minimi per i nodi attraversati;

Inoltre ogni vertice deve essere visitato una sola volta, per questo durante la visita abbiamo bisogno di una ***coda*** $Q$ e i vertici devono essere colorati:
- Bianco: vertici ancora non visitati.
- Grigio: vertici "scoperti" ma non ancora visitati, cioè i vertici aggiunti alla coda.
- Nero: vertici già visitati.
Il colore di ogni vertice viene salvato in un array $color[\ ]$.

```python
def BFS(G, s):
	Init(G);		   # inizializzo i colori e tempo di scoperta
	d[s] = 0
	Q = Enqueue(Q,s);  # metto in coda la sorgente
	color[s] = g        
	while Q != ø:      # finchè la coda non è vuota continuo la visita
		x = Testa(Q)   # salvo la testa della coda in x
		for v in Adj[x]:
			if color[v] == b:
				pred[v] = x      # aggiorno il predecessore
				Q = Enqueue(Q,v) # metto in coda i vertici raggiungibili da x
				color[v] = g
				d[v] = d[x] + 1   # aggiorno il tempo di scoperta   
		Q = Dequeue(Q) 		# tolgo x dalla coda
		color[x] = n	
```

```python
def Init(G):
	for v in V do:
		color[v] = b
		d[v] = ∞
		pred[v] = NULL
```

Al termine dell'esecuzione di $BFS(G)$ valgono le seguenti proprietà:
1. $\forall \ v \in v$,  $v$ sarà visitato, e quindi sarà colorato di nero $\iff$ $v$ è raggiungibile da $s$.
2. $\forall \ v \in v$, $d[v] =\delta(s,v)$ dove $\delta(s,v)$ è la ***lunghezza del percorso minimo*** da $s$ a $v$. 
3. $\forall \ v \in v$, è possibile ottenere un percorso minimo da $s$ a $v$ concatenando un percorso minimo da $s$ a $pred[v]$ con $v$.

>[!warning] 
>La BFS non è in grado di individuare cicli all'interno del grafo!
#### Proprietà A, B e lemma
Da fare.

---
### Visita in profondità
Per visitare un grafo in profondità abbiamo bisogno di:
- un array per i colori, $color[\ ]$;
- un array per il tempo di scoperta del vertice, $d[\ ]$;
- una array per il tempo di fine visita del vertice, $f[\ ]$;
- un array per il predecessore del vertice, $pred[ \ ]$.

```python
def DFS(G):
	Init(G)
	for v in V:
		if color[v] == b:
		DFS_Visit(G, v)
```
- Al termine della $DFS(G)$ tutti i nodi di G saranno colorati di nero.

```python
def DFS_Visit(G, s):
	color[s] = g
	d[s] = tempo++    # salvo il momento il cui visito s
	for v in Adj[s]:  # visito tutti i nodi bianchi nella Adj[s]
		if color[v] == b:
		pred[v] = s
		DFS_Visit(G, v)
	f[s] = tempo++    # salvo il momento il cui finisco la visita di s
	col[s] = n        # e dei suoi adiacenti
```
- Al termine della  $DFS\_Visit(G,s)$ tutti i nodi raggiungibili da $s$ saranno colorati di nero.

```python
def Init(G):
	for v in V:
		color[v] = b
		pred[v] = NULL
		tempo = 1   
```
- tempo: variabile globale inizializzata a 1, viene incrementata di 1 ogni volta che un vertice viene visitato.

>[!warning] 
>A differenza della BFS, la ***DFS***  è in grado di individuare cicli all'interno del grafo!

>[!important] 
>Sia la BFS che la DFS hanno complessità lineare sulla dimensione dei grafo $(|V| + |E|)$, quindi possiamo dire che $T_{DFS}(G) = O(|V| + |E|)$.

---
### Ricerca di cicli
Sia $G =(V,E)$ un grafo ciclico, allora dal teorema del percorso bianco sappiamo che esiste un percorso bianco da $v_{1}$ a $v_i$, con $i =1,2,3,\dots,k$.

Per verificare se un grafo è ciclico possiamo utilizzare un algoritmo molto simile alla DFS, che restituisce $True$ se il grafo è aciclico, o $False$ se è ciclico.

```python
def Aliclico(G):
	for v in V:
		ret = Aciclico_Visit(G, v)
		if ret = False:
			return False
	return True
```

```python
def Aciclico_Visit(G, s):
	color[s] = g
	for v in Adj[s]:
	 if color[v] == b:
		 ret = Aciclic_Visit(G, v)
		 if ret = False
			return False
	else if color[v] == g  # se il nodo adiacente è grigio ho un arco di ritorno
		return False 
	return TRUE
```

---
