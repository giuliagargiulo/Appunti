Un ***[[Sistema operativo|sistema operativo]]*** è un **programma** che gestisce le risorse di un calcolatore, e fa da intermediario tra l'utente e l'hardware di un calcolatore.
Un [[Sistema operativo|SO]] deve:
1. gestire l'esecuzione dei programmi utente
2. semplificare l'interazione tra utente e calcolatore
3. rendere efficace ed efficiente l'utilizzo del calcolatore
4. utilizzare l'hardware in modo efficiente

Un ***sistema di calcolo*** è formato da 4 componenti: 
- **Hardware**, composto da CPU, memoria e dispositivi di I/O
-  **[[Sistema operativo|SO]]**, che rappresenta il primo strato software e controlla e coordina l'uso dei dispositivi da parte dei programmi applicativi per gli utenti
- **Programmi applicativi**, definiscono il modo in cui utilizzare le risorse per la risoluzione di problemi
- **Utenti**, che possono essere persone, altri processi o altri calcolatori.

>[!Important]
>In generale, un sistema operativo offre gli strumenti per impiegare in modo corretto le risorse messe a disposizione dal sistema di calcolo;  definisce un ambiente in cui altri programmi possono lavorare.

Poiché utilizzare un calcolatore non è facile, sono stati sviluppati i programmi applicativi; 
questi programmi sono diversi tra loro, ma richiedono alcune funzioni comuni, che sono state racchiuse in un unico insieme di programmi, cioè il **[[Sistema operativo|sistema operativo]]**. 
Infatti un [[Sistema operativo|SO]] si occupa di:
- **Allocare e gestire le risorse di un calcolatore**, risolvendo in modo efficiente i conflitti.
- **Controllare l'esecuzione dei programmi** evitando errori ed usi impropri del calcolatore.
- **Fornire un ambiente di esecuzione** coerente ed uniforme per l'esecuzione dei programmi.
---
## Definizione di sistema operativo

 Il [[Sistema operativo|sistema operativo]] è quindi un programma continuamente in esecuzione che gestisce le risorse (hardware) del calcolatore e gestisce l'esecuzione dei programmi; esso include il **kernel** (nucleo), ma anche altri componenti come **librerie di sistema**, **l'interfaccia utente**, i **driver** per i dispositivi ecc...
 
>[!Nota] 
>Tutto ciò che non fa parte del SO, eccetto i **programmi di sistema** (unità fornite insieme al SO), è un **programma applicativo**.

## Kernel

Il **kernel** è il cuore del sistema operativo, è un componente di basso livello che opera tra l'hardware e il software applicativo e gestisce:
1.  le risorse hardware del calcolatore, come CPU, memoria, periferiche e dispositivi di I/O
2.  la memoria, i processi e i file 
3. la comunicazione tra hardware e software

Tutto il resto, anche l'interazione con l'utente, è ottenuto tramite programmi eseguiti dal kernel, che accedono alle risorse hardware tramite richieste al kernel. 
Nei moderni SO, il **kernel** è l'unico programma ad avere **accesso completo** all'hardware, tramite la **kernel mode**, mentre gli altri programmi vengono eseguiti dal kernel tramite la **user mode**.

![[Pasted image 20240901173229.png |400]]
---
## Organizzazione del calcolatore

Il sistema operativo è strettamente legato all'architettura del calcolatore. I moderni calcolatori sono formati da una o più CPU ed da controllori di dispositivo, detti **driver**; essi sono connessi tramite un canale, detto **bus**, che permette l'accesso alla memoria condivisa, permettendo a queste componenti di eseguire operazioni in parallelo competendo per l'accesso alla memoria.
In realtà vengono utilizzati più bus, ma il principale è il **PCIe**.

![[Pasted image 20240901174442.png |500]]
### CPU
La CPU, acronimo di Central Processing Unit, esegue le istruzioni dalla memoria;
ogni CPU ha un **set di istruzioni** che può eseguire ciclicamente, attraverso le fasi di **fetch**, **decode** ed **execute**, e dei **registri** (program counter, stack pointer, instruction register, status register, memory address register, memory data register).

- CPU: componente hardware che esegue istruzioni.
- Processore: chip fisico che contiene una o più CPU.
- Unità di calcolo (core): unità di elaborazione di base della CPU.
- Multicore: include più core sulla stessa CPU.
- Multiprocessore: include più processori.
---
## Sistemi con interrupt

Grazie alla **multiprogrammazione** è possibile eseguire più processi contemporaneamente. Ad esempio, durante l'esecuzione di un processo, se si ha bisogno di un input, la CPU non può aspettare che la periferica fornisca il dato, restando in questo modo ferma, quindi passa il controllo ad un altro processo.
Quando la periferica ha finito, emette un segnale, cioè un'**interruzione**, per far capire alla CPU che ha terminato e che il controllo può tornare alla CPU.

Le interruzioni, quindi, consentono di gestire le operazioni concorrenti, sovrapponendo CPU e operazioni di I/O ed evitando il **busy waiting**.

1. I dispositivi di I/O e la CPU sono in **esecuzione concorrente**
2. Ogni controllore di dispositivo è responsabile di un dispositivo ed ha un **buffer** locale
3. La CPU porta i dati dalla/alla **memoria** ai/dai buffer locali
4.  Potrebbero essere necessari I/O dal dispositivo ai buffer locali del controller
5. La periferica informa la CPU che ha finito le sue operazioni attraverso il meccanismo delle **interrupt**.

>[!Nota]
>I sistemi operativi moderni sono guidati dalle **interruzioni**:
>- Le interrupt trasferiscono il controllo ad una procedura di servizio dell'interruzione
>- Una volta eseguita la procedura di servizio, il controllo torna all'operazione interrotta.
>
>Un altro metodo è quello del **polling**, che tiene traccia delle comunicazioni dei dispositivi di I/O interrogandoli ad intervalli regolari.


### Interrupt timeline

![[Screenshot 2024-09-02 alle 17.35.10.png | 500]]
1. Per avviare le operazioni di I/O la CPU carica opportuni registri del controllore I/O ed intanto continua l'esecuzione di un altro processo.
2. Intanto il controllore I/O avvia le operazioni sul proprio buffer e quando ha terminato invia l'**interrupt**.
3. La CPU controlla periodicamente la presenza di un'interruzione (oltre alle fasi di fetch, decode ed execute, ad ogni ciclo la CPU esegue anche una **checkForInterrupt**)
4. Quando si accorge che è presente un'interruzione, la CPU salva il contesto del processo in esecuzione, determina il tipo dell'interrupt e chiama il gestore di interruzione, che invoca la **routine di servizio** (un programma che serve quell'interruzione).
5. Quando la CPU riceve un'interrupt, essa riceve anche un **indice**, che confronta con il **vettore delle interruzioni** per ottenere l'indirizzo della routine di servizio.
6. Gestita l'interruzione, la CPU riprende l'elaborazione interrotta (del primo processo).

Negli SO moderni c'è un controllore hardware delle interruzioni, per ottimizzare al massimo i tempi di gestione.

![[Screenshot 2024-09-02 alle 17.48.15.png | 500]]
### Tipi di interrupt

Esistono due tipi di interruzione:
- **Non mascherabile**: si tratta di errori irreversibili (errori hardware, divisione per 0, segmentation fault), che quindi devono essere serviti immediatamente.
- **Mascherabile**: l'interrupt può essere gestita in un secondo momento, quindi viene mascherata, e servita successivamente.

### Cicli di I/O

Dopo l'avvio di un'operazione di I/O, ci sono due modalità di gestione:
- Il controllo torna al programma utente dopo il completamento dell'operazione di I/O, quindi viene attivata un'istruzione di **wait** per la CPU fino al prossimo interrupt. In questo caso si conosce il dispositivo che ha richiesto l'interruzione.
- Il controllo torna al programma utente senza aspettare il completamento dell'operazione di I/O, e il SO usa la tavola dei dispositivi I/O per capire quale ha richiesto l'interruzione, verifica lo stato del dispositivo e modifica la entry per indicare che ha servito l'interruzione.

>[!Nota]
>Non sempre è necessario conoscere il dispositivo che ha inviato l'interrupt, ad esempio nel caso di una divisione per 0 non ci interessa.

---
## Caratteristiche del sistema operativo

### Multiprogrammazione
La **multiprogrammazione** è la capacità di gestire contemporaneamente l'esecuzione di più programmi. Un singolo utente non riesce a sfruttare al meglio la CPU e i dispositivi di I/O, quindi per ottimizzarne l'utilizzo, la multiprogrammazione organizza i jobs per mantenere sempre attiva la CPU.
- In memoria è conservato un insieme dei job totali del sistema
- Un job viene selezionato ed eseguito dal job scheduler
- Nel caso di attesa, il SO cambia job.
### Timesharing
La CPU cambia job molto frequentemente, permettendo agli utenti di interagire; questo comporta:
- **Tempo di risposta breve**
- Ogni utente ha programmi in esecuzione (processi)
- Se più job sono pronti per essere eseguiti si ha lo **sheduling della CPU**.

### Orientati alle interrupt
I sistemi operativi sono **interrupt driven** (orientati alle interrupt) dal punto di vista hardware e software:
- **Interrupt hardware**: sollevate da un dispositivo (disco, periferica,...)
- **Interrupt software**: dette anche **exception** o **trap**, si tratta di **richieste** del sistema operativo **per un servizio** (**system call**).

---
## Attività del sistema operativo
1. Il sistema operativo deve avviarsi (**bootstrap** program)
2. Il kernel inizia a lavorare, offrendo servizi al sistema e agli utenti, e gestendo tutte le risorse del calcolatore.
3. Il kernel dovrà gestire le interruzioni ed eccezioni ed eseguire le chiamate di sistema.
4. Multiprogrammazione.

>[!Important]
>Per essere eseguiti, i processi devono trovarsi in memoria principale.

---
## Meccanismi di protezione di un SO
I sistemi multiprogrammati e multiutente richiedono meccanismi di **protezione** di diverso tipo.
### Modalità operativa duale
le operazioni in **dual-mode** permettono al SO di proteggere se stesso ed altri componenti; per questo il sistema operativo mette a disposizione due modalità,**user mode** e **kernel mode**, che si distinguono grazie ad una componente hardware, **un bit di modalità**, ovviamente anch'esso protetto (settabile solo in modalità kernel).

- In questo modo è possibile distinguere facilmente quando si sta eseguendo codice utente o kernel.
- Alcune istruzioni sono **privilegiate** e quindi eseguibili solo in modalità kernel.

>[!Important]
>Con **interrupt** o **trap** si va alla modalità **kernel**, mentre quando viene servita l'interruzione il sistema ripristina la modalità **user**.

### Protezione temporale
Esistono anche delle **protezioni temporali**, poiché i programmi utenti non devono mantenere il controllo per un tempo illimitato; quindi viene utilizzato un **timer** per dare al sistema operativo il controllo periodico della CPU. Il timer funziona anch'esso con delle interruzioni, inviate ad intervalli periodici di tempo; il contatore del timer viene decrementato dal clock fisico, e quando arriva a zero, viene inviata un'**interrupt**, permettendo al sistema operativo di riprendere il controllo.

### Protezione della memoria
Inoltre bisogna anche proteggere la modalità di esecuzione privilegiata e la **memoria** collegata ad essa, poiché sovrascrivendo il vettore delle interruzioni e le operazioni di servizio, si potrebbe trasferire la modalità privilegiata all'utente. Quindi
occorrono anche **meccanismi di protezione hardware della memoria**.

Ad esempio, nel caso in cui su una macchina stanno operando contemporaneamente più processi e/o più utenti, occorre una protezione sulle aree di memoria su cui stanno lavorando i vari processi; quindi si stabiliscono degli spazi di indirizzamento, cioè spazi in memoria all'interno dei quali può lavorare un determinato processo, tramite un **registro base** e un **registro limite**, anche se vedremo poi che la CPU lavora su indirizzi logici, non fisici.












 

