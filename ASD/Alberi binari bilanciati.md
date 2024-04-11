Per tutte le **classi di alberi bilanciati** vale la seguente proprietà:
Sia $n$ il numero di nodi di un albero $T$, allora $h(T) = c \ \log_{2}n + k$, quindi possiamo dire che: $$h(T) = O(\log_{2}n)$$
### Alberi perfettamente bilanciati

Un [[albero binario]] si dice **perfettamente bilanciato** (***APB***) se o è vuoto, oppure:
1. La cardinalità di $T_{dx}$ e $T_{sx}$ differisce al massimo di 1: $||T_{sx}|-|T_{dx}|| \leq 1$;
2. A loro volta i sottoalberi $T_{dx}$ e $T_{sx}$ sono ***APB***.

***Caso base:*** $T=\emptyset$
***Caso induttivo:*** $T\not=\emptyset$, in cui  $T_{dx}$ e $T_{sx}$  sono APB.

#### Ricerca (da rivedere)
La ricerca in un APB richiede $\Large \frac{n}{2^i}$ confronti, quindi possiamo calcolare anche l'altezza considerando la cardinalità di una foglia (1): ${\Large \frac{n}{2^{i}}} = 1$  quindi  $h = \log_{2}n$.

---
## Alberi AVL
Un albero binario è detto ***AVL*** se o è vuoto, oppure:
1. Le altezze dei sottoalberi $T_{dx}$ e $T_{sx}$ differiscono al massimo di 1: $|h(T_{sx}) - h(T_{dx})|\leq 1$
2. A loro volta i sottoalberi $T_{dx}$ e $T_{sx}$ sono ***AVL***.

***Caso base:*** $T=\emptyset$
***Caso induttivo:*** $T\not=\emptyset$, in cui  $T_{dx}$ e $T_{sx}$  sono AVL.

>[!tip] 
>Un [[Albero binario| albero pieno]] è sia AVL che APB;
>Un albero vuoto ha altezza -1 per convenzione.

### AVL minimi
Gli AVL minimi sono i più alti tra gli AVL con lo stesso numero di nodi. Fissata l'altezza $h$, l'AVL minimo di altezza $h$ è l'AVL con il minor numero di nodi possibile.


In generale, un AVL minimo di altezza $h$, con $h>1$ è uguale ad un albero che ha come sottoalberi: 
- un AVL minimo di altezza $h_{1}= h-1$ 
- un AVL minimo di altezza $h_{2}= h-2$