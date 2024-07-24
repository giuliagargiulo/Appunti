Un iteratore in C++ è un oggetto che ci permette di scorrere gli elementi di una struttura dati in modo sequenziale. Essi ci permettono di accedere agli elementi della struttura, senza però mostrare i dettagli interni della struttura sulla quale vengono applicati.

Le principali operazioni che un operatore può svolgere sono:
- ***Deferenziazione***, tramite `operator*()`, permette di accedere al valore dell'elemento corrente.
- ***Incremento***, tramite `operator++`, passa all'elemento successivo nella struttura.
- **Confronto**, permette di confrontare due iteratori per vedere se puntano allo stesso elemento.

### Iteratori sugli alberi binari

Per implementare degli iteratori sugli alberi binari in preorder, postorder e inorder abbiamo bisogno di tre elementi: **root** (radice dell'albero) , **current**(nodo corrente) e uno **stack**.
Gli iteratori simulano la ricorsione tramite l'utilizzo di uno **stack**, inserendo nello stack gli elementi da visitare successivamente. Se lo stack è vuoto e non ci sono altri figli, allora current viene impostato a **nullptr**, e di conseguenza l'iteratore termina.

```cpp
const typename BinaryTree<Data>::Node * root = nullptr;
const typename BinaryTree<Data>::Node * current = nullptr;
StackVec<const typename BinaryTree<Data>::Node *> stack;
```

1. L'iteratore in **PreOrder** deve visitare per prima la radice dell'albero, poi il sottoalbero sinistro e poi il sottoalbero destro (la visita avviene scendendo nell'albero). All'inizio della visita current è uguale alla radice dell'albero, quindi `current = root`. 

2. L'iteratore **InOrder** deve visitare prima tutto il sottoalbero sinistro, poi la radice e poi il sottoalbero destro (la visita parte dopo aver raggiunto il nodo minimo). All'inizio della visita current è uguale al minimo del sottoalbero sinistro, quindi utilizziamo la seguente funzione per arrivare al nodo più a sinistra, inserendo nello stack tutti i figli sinistri che incontriamo. Questa funzione verrà richiamata sul sottoalbero destro del nodo corrente per inserire nello stack il suo sottoalbero sinistro.

```cpp
template <typename Data>
const typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::FindDeepestLeftInOrder(const typename BinaryTree<Data>::Node * node){
	while(node != nullptr && node->HasLeftChild()){
	stack.Push(node);
	node = &node->LeftChild();
	}
return node;
}
```

3. L'iteratore in **PostOrder** deve visitare prima tutto il sottoalbero sinistro, poi tutto quello destro e poi la radice (la visita avviene risalendo nell'albero). All'inizio della visita, current parte dal nodo minimo del sottoalbero sinistro, utilizzando la seguente funzione per arrivare al nodo più a sinistra, inserendo nello stack tutti i figli sinistri che troviamo, ed infine il sottoalbero destro del nodo minimo, se è presente. Questa funzione verrà richiamata ogni volta che il nodo corrente ha sottoalbero destro, per inserire nello stack il suo sottoalbero sinistro.

```cpp
template <typename Data>
const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::FindDeepestLeft(const typename BinaryTree<Data>::Node * node){

	if(node != nullptr){
		while(node->HasLeftChild()){
		stack.Push(node);
		node = &node->LeftChild();
		}
	
		if(node->HasRightChild()){
		stack.Push(node);
		node = &node->RightChild();
		node = FindDeepestLeft(node);
		}
	}
return node;
}
```


Per implementare un iteratore su alberi binari che effettua una vista in ampiezza abbiamo invece bisogno di tre elementi: **root** (radice dell'albero) , **current**(nodo corrente) e una **coda**.
La coda ci servirà per salvare i figli sinistro e destro del nodo che stiamo visitando, per visitarli successivamente, mantenendo l'ordine dei livelli.

```cpp
const typename BinaryTree<Data>::Node * root = nullptr;
const typename BinaryTree<Data>::Node * current = nullptr;
QueueVec<const typename BinaryTree<Data>::Node *> queue;
```

L'teratore parte dalla radice, quindi `current = root`, e procede per livelli, inserendo in coda i figli del nodo corrente; ogni volta che un nodo viene visitato, viene rimosso dalla coda. 
Quando la coda è vuota (cioè non ci sono più sottoalberi da visitare), allora l'iteratore termina.

```cpp
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator ++ (){
	if(Terminated())
		throw std::out_of_range("operator++: Iterator is terminated");
	if(current->HasLeftChild())
		queue.Enqueue(&current->LeftChild());
	if(current->HasRightChild())
		queue.Enqueue(&current->RightChild());
	if(queue.Empty())
		current = nullptr;
	else
		current = queue.HeadNDequeue();
	return *this;
}
```

---
### Iteratori online e offline

Gli **iteratori online** possono essere utilizzati immediatamente, e non richiedono che l'intera collezione di dati sia già presente in memoria; essi lavorano con dati generati o ottenuti al momento. Complessità computazionale più alta.

Gli **iteratori offline**, invece, operano su collezioni di dati che sono già interamente disponibili in memoria, e richiedono quindi che tutti i dati siano accessibili prima che l'iterazione inizi. Maggiore spazio in memoria occupato.

