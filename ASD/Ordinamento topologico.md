Un ordinamento topologico è un ***ordinamento totale***, o ***permutazione***,dei vertici di un grafo $G=(V,E)$ della forma $v_1,v_2,\dots,v_k$ tale che:  $\forall(v,u)\in E$, $v$ precede $u$ nell'ordinamento, non necessariamente è il precedente.

>[!important] 
>Se un grafo $G$ è ciclico, allora non esiste una permutazione, cioè un ordinamento, che rispetti quella serie di archi. Quindi non esistono ordinamenti topologici per grafi ciclici.

Ogni grafo ***aciclico*** ammette almeno un ordinamento topologico, se non ci sono "diritti di precedenza", il numero massimo di ordinamenti topologici è $n!$, dove $n$ è il numero di vertici.

## Proprietà
Dato un grafo $G =(V,E)$, se $G$ è ***aciclico***, allora esiste (almeno) un ordinamento topologico.

- Se $G$ è un grafo aciclico e $G'$ è un sottografo di $G$, allora $G'$ è aciclico.
- Se $G$ è aciclico, allora esiste un vertice $v\in V$ tale che: $v$ ha grado entrante 0.
	(Da dimostrare)

## Come trovare un ordinamento topologico

Dalle proprietà precedenti sappiamo che se un grafo è aciclico, allora esiste un vertice $v_1\in V$ con grado entrante 0, che non ha diritti di precedenza da rispettare, allora $v_1$ sarà il primo vertice di $\pi$. Calcolo quindi il sottografo che si ottiene togliendo $v_1$ dal grafo: $G_{1} = (V \setminus \{ v_{1} \} \in E \setminus \{(v_{1,}u) \in E \ | \ u\in V \})$. $G_1$ a sua volta è aciclico, ed esiste $v_2$ con zero archi entranti, quindi $v_2$ è il secondo vertice di $\pi$. Si prosegue così per tutti i vertici in $V$.

Questo metodo non è efficiente perchè ad ogni eliminazione bisogna calcolare un sottografo, quindi per evitare di calcolare i sottografi, usiamo una coda $Q$.
### Algoritmo
1. Calcolo il grado entrante di ogni vertice tramite la funzione $GradoEntrante(G)$.
2. Prendo tutti i vertici con grado 0 e li inserisco in una coda $Q$.
3. Prendo un vertice dalla coda e verifico dove vanno i suoi archi uscenti (controllo la sua lista di adiacenza), se uno di questi ha grado 1 (che quindi diventerà 0), lo inserisco nella coda $Q$.

In questo modo non bisogna creare un sottografo ad ogni eliminazione.

```python
def OrdinamentoTopologico(G):
	GE = GradoEntrante(G)
	for v in V:
		if GE[v] == 0:
			Q = Enqueue(Q, v)
	while Q != NULL:
		v = Head(Q)
		print(v)
		for u in Adj[v]:
			GE[u] = GE[v] - 1
			if GE[u] == 0:
				Q = Enqueue(Q, u)
		Q = Dequeue(Q)
```

```python
def GradoEntrante(G):
	for v in V:
		GE[v] = 0
	for v in V:
		for u in Adj[v]:
			GE[u] = GE[u] + 1
```

