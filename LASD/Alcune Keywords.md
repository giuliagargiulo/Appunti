---
author: Giulia Gargiulo
---

1. `inline` si usa quando il corpo di una funzione contiene soltanto una chiamata ad un'altra funzione; il compilatore, quindi, evita di compliare la funzione principale, e compila direttamente il suo corpo, ossia la chiamata a funzione; però non viene svolto sempre, è il compilatore a decidere.
2. `friend` si utilizza quando si vuole dare l'accesso ad una classe o ad una funzione ai membri privati e protetti di una classe. Una funzione amica può essere una funzione globale o una funzione membro di un'altra classe.
3. `override` si utilizza quando vogliamo utilizzare un metodo virtuale derivato da una classe base; l'uso di questo specificatore previene banali errori di digitazione, perchè evidenzia eventuali mancate corrispondenze tra il prototipo del metodo virtuale dichiarato nella classe base e quello ridefinito della classe derivata. Se il compilatore non trova il metodo nella classe base, emette un errore ed interrompe la compilazione.
4. `virtual` permette di definire una funzione virtuale, cioè una funzione dichiarata in una classe base, e ridefinita (overridden) in una classe derivata. Dichiarando una funzione virtual, posso sovrascriverla in un'altra classe.
5. `this`,identifica un puntatore speciale che contiene l'indirizzo dell'istanza della classe che ha invocato il metodo; l'uso è esclusivamente confinato all'ambito della definizione dei metodi di una classe.
6. `void virtual Clear() = 0;` l'uguale 0 rende la funzione virtuale pura, cioè che non può essere implementata nella classe base, ma che verrà implementata nelle sottoclassi. 

>[!important]
>Quando si dichiara una funzione virtuale pura, ogni classe che eredita dalla classe in cui è contenuta la funzione, dovrà implementare quella funzione.
