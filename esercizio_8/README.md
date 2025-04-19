# 🔀 Esercizio 8 - Comunicazione e sincronizzazione avanzata tra processi

Questa serie di esercizi si concentra su:
- Scambio di dati tra padre e figli
- Sincronizzazione tra più processi
- Comunicazione tramite segnali

---

## ✍️ Esercizio 8.1 - Somma tra padre e due figli

Scrivere un programma in C che:

- Crea **due figli**: uno per i numeri pari (`fpari`) e uno per i dispari (`fdispari`)
- Il **padre legge** numeri **positivi da tastiera**
  - Se il numero è **pari**, lo manda a `fpari`
  - Se è **dispari**, lo manda a `fdispari`
- L'inserimento si ferma quando si riceve un **numero negativo**
- I **figli effettuano somme parziali** dei valori ricevuti
- Alla fine, **rimandano i risultati al padre**
- Il **padre calcola e stampa** la **somma totale**

📌 Suggerimento: usare pipe o segnali per comunicare, e `wait()` per sincronizzazione finale.

---

## ✍️ Esercizio 8.2 - Segnali tra processi figli

Scrivere un programma in C in cui:

- Il padre crea **N processi figli** (dove **N è pari**)
- Ogni figlio ha un indice `i` (da `0` a `N-1`)
- In base a `argv[1]`:
  1. Se `argv[1] == "a"`:
     - Ogni figlio con `i` pari manda **SIGUSR1** al processo `P_{i+1}`
  2. Se `argv[1] == "b"`:
     - Ogni figlio con `i < N/2` manda **SIGUSR1** al processo `P_{i+N/2}`

📌 Suggerimento: salvare i PID in un array condiviso per inviare correttamente i segnali tra figli.

---

## ✍️ Esercizio 8.3 - Scrittura/lettura sincrona su file temporaneo

Scrivere un programma C e POSIX che:

- Usa i **segnali per sincronizzare** padre e figlio
- Il padre **scrive** numeri da `1` a `n` (preso da riga di comando)
- Il figlio **legge** un numero alla volta
- Lo scambio avviene tramite **un file temporaneo**, sempre sovrascrivendo la **prima posizione**
- I segnali sincronizzano la scrittura/lettura per evitare condizioni di race

📌 Tip: usare `kill()` con `SIGUSR1`/`SIGUSR2` per il coordinamento.
