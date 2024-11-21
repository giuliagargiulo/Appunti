## 1. Come viene gestito un pagefault?
Un **pagefault** è un'interruzione generata dalla CPU quando un processo cerca di accedere ad una pagina che non è presente in memoria (RAM); questo può accadere quando un processo accede per la prima volta ad una pagina, oppure quando la pagina è stata spostata sul disco per fare spazio ad altre pagine. Quando si verifica un pagefault, viene gestito nel seguente modo:
1. **Interruzione e sospensione del processo**: la CPU sospende il processo che ha causato l'interruzione e invia un segnale al SO.
2. **Individuazione della pagina mancante**: il SO, tramite la tabella delle pagine del processo, individua la pagina mancante e verifica se è valida e se può essere caricata in memoria.
3. **Allocazione di un frame**: se la pagina è valida, il SO **cerca un frame libero**; se non ci sono frame liberi, si utilizzano gli algoritmi di sostituzione delle pagine (ad esempio LRU o OTP).
4. **Scrittura della pagina su disco (se ci sono state modifiche)**: se la pagina sostituita è stata modificata, il SO la scrive sul disco per non perdere le modifiche.
5. **Caricamento della pagina in memoria**: una volta trovato un frame, il SO carica la pagina mancante **nel frame libero**.
6. **Aggiornamento della tabella delle pagine**: il SO aggiorna la tabella della pagine del processo, per indicare che adesso la pagina è in memoria ed associa l'indirizzo logico del processo al nuovo frame.
7. **Ripresa dell'esecuzione del processo:** il processo riprende l'esecuzione da dove si era interrotta.
---
## Discutere cosa si intende per località di un processo e come si può rappresentare.

La località di un processo è un insieme di pagine che sono utilizzate attivamente dal processo (contemporaneamente). Un processo, durante la sua esecuzione si sposta di località in località, e spesso alcune di queste sono sovrapponibili.

Ad esempio, se si invoca una funzione, essa definisce una nuova località, contenente istruzioni, variabili locali e un sottoinsieme di quelle globali; quando la procedura termina, il processo lascia questa località, poichè le variabili locali e le istruzioni non sono più utilizzate attivamente.

Il modello di località è alla base del caching, poiché se ci accessi ai dati fossero casuali, anzichè per località, il caching sarebbe inutile.

Supponendo di allocare ad un processo il numero di frame necessari per sistemare le sue località attuali, finchè tutte le pagine non saranno presenti in memoria si verificheranno pagefault per quelle località; a questo punto, finché le località non subiranno cambiamenti, non si verificheranno pagefault.
Se si allocano meno frame rispetto alla dimensione della località attuale, invece, la paginazione degenera, provocando il **trashing**, poichè non si possono tenere in memoria tutte le pagine che il processo sta utilizzando attivamente.

***Modello Working set***
Il modello working set è basato sull'ipotesi di località. Esso utilizza un parametro, delta ($\Delta$), per definire una working set window (finestra dell'insieme di lavoro).
L'idea consiste nell'esaminare i più recenti $\Delta$ riferimenti alle pagine; l'insieme delle $\Delta$pagine piu recenti costituisce il **working set**. 

Se una pagina è in uso attivo, allora sarà nel working set, altrimenti dopo $\Delta$ unità di tempo, uscirà dal working set. Quindi, **l'insieme di lavoro è un'approssimazione della località del programma.**

![[Screenshot 2024-11-03 alle 16.29.21.png|500]]
Ad esempio, in questa immagine, se $\Delta = 10$, allora all'istante $t_1$ l'insieme di lavoro è $WS(t_1)=\{1,2,5,6,7\}$, mentre all'istante $t_2$ è $WS(t_2)=\{3,4\}$.

La caratteristica più importante del **working set** è la sua **dimensione**. Calcolando la dimensione dell'insieme di lavoro $WS_i$ , per ogni processo $p_i$ , si può determinare la richiesta totale di frame $D = \sum_i(WS_i)$. Se la richiesta totale $D$, è maggiore del numero di frame liberi $m$ ($D > m$), allora si verifica il **trashing**, poiché alcuni processi non dispongono del numero necessario di frame.

---
## Spiegare brevemente quali sono i vantaggi dell'uso del journaling per il file system.

Il journaling per il file system è una tecnica migliora la consistenza e la coerenza del sistema in caso di guasti o arresti improvvisi. 

Il verificatore della coerenza può risultare troppo lento o potrebbe non essere in grado di ripristinare le strutture del file system, con conseguente perdita di file.

La soluzione a questo problema consiste nell'applicare agli aggiornamenti dei metadati relativi al file system medoti di ripristino basati sulla registrazione delle modifiche in un file, detto **file di log**. Ogni insieme di operazioni che esegue un compito si chiama **transazione**; una volta che le modifiche sono state riportate nel file di log, esse si considerano **portate a termine con successo**, restituendo cosi il controllo al processo utente, che può continuare la sua esecuzione.
Nel frattempo, si applicano alle strutture le operazioni scritte nel log, e si aggiorna il puntatore che indica quali operazioni sono state eseguite e quali no.
Quando un'intera operazione è stata eseguita, essa viene rimossa dal file di log.

Se si verifica un crollo del sistema, nel log potrebbero esserci zero o più transazioni, che devono essere completate; esse vengono eseguite dalla posizione corrente del puntatore fino al termine, e le strutture del file system rimangono **coerenti**.
L'unico problema che si può verificare è se una transazione sia **fallita**, e quindi non dichiarata terminata con successo prima del crollo del sistema; in questo caso si devono annullare tutti i cambiamenti effettuati dalla transazione, mantenendo la coerenza del file system.

**Vantaggi:**
1. **Recupero rapido dei dat**i: in caso di arresto improvviso, il file system può usare il journal per ripristinare rapidamente le operazioni incomplete, senza dover scansionare l'intero disco.
2. **Integrità dei dati**: il journaling tiene traccia delle operazioni sui dati e sulla struttura del file system; in caso di errore, il journal fornisce uno stato coerente, riducendo il rischio di perdita dei dati o il danneggiamento del file system.
3. **Protezione della struttura del file system**: il journal registra le modifiche alla struttura del file system prima che vengano applicate, quindi in caso di interruzione possono essere ripristinate.
4. **Possibilità di annullare modifiche**: poichè le modifiche vengono resistrate prima di essere applicate, il file system può annullare operazioni non completate in modo sicuro, ripristinando il sistema allo stato precedente.

---

