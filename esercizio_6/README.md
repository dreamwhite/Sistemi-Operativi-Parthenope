# 🚦 Esercizio 6 - Gestione dei segnali

In questo esercizio si lavora con la gestione dei **segnali** in C, sfruttando `signal()` o `sigaction()` per intercettare comportamenti del sistema.

---

## ✍️ Esercizio 6.1 - Intercettare SIGINT (CTRL-C)

Scrivere un programma C che:

- Intercetta il segnale generato da `CTRL-C` (SIGINT)
- Invece di terminare, **scrive su stdout** la frase:

```
non voglio terminare
```

🔧 *Suggerimento:* usa un handler personalizzato per SIGINT che esegue una `printf()`.

---

## ✍️ Esercizio 6.2 - Somma/Differenza con segnali

Scrivere un programma C che:

- Riceve **in input da tastiera** due numeri interi `a` e `b`
- Si comporta nel modo seguente in base ai **segnali ricevuti**:

### 🔹 SIGUSR2
- Stampa: `a + b = risultato`

### 🔹 SIGUSR1
- Stampa: `a - b = risultato`

### 🔹 SIGINT
- Termina il programma

---

💡 *Nota:* i segnali possono essere inviati da un altro terminale con `kill -SIGUSR1 <PID>`  
Puoi recuperare il PID del processo con `getpid()` e stamparlo a video.

📌 *Suggerimento tecnico:* è utile mantenere i valori `a` e `b` in **variabili globali**, così da poterli usare negli handler dei segnali.


---

## ✍️ Esercizio 6.3 - Due figli, segnali e controllo PARI/DISPARI - Controllo su numero pari/dispari e segnali

Scrivere un programma in C e POSIX sotto Linux che, preso un **intero positivo** da riga di comando:

- Crea due figli: **A** e **B**
- Se il numero è **pari**:
  - Invia **SIGUSR1** al figlio A, che calcola il **cubo** del numero
  - Il figlio B stampa un messaggio di saluto e termina
- Se il numero è **dispari**:
  - Invia **SIGUSR2** al figlio B, che calcola il **reciproco** del numero
  - Attende un numero di secondi pari al **doppio del numero**
  - Invia **SIGUSR1** al figlio A per fargli stampare un messaggio e terminare

---

## ✍️ Esercizio 6.4 - Sincronizzazione padre-figlio con segnali - Sincronizzazione padre-figlio

Scrivere un programma in C e POSIX che:

- Usa i **segnali** per sincronizzare un processo padre e un processo figlio
- Il padre **scrive** da 1 a `n` (preso da riga di comando)
- Il figlio **legge** un numero per volta
- Lo scambio avviene tramite **un file temporaneo**, sempre nella **prima posizione**
- Sincronizzazione tramite segnali (es. `SIGUSR1` e `SIGUSR2`)

---

## ✍️ Esercizio 6.5 - Albero ternario di processi - Albero ternario di processi

Scrivere un programma in C e POSIX che crea una **struttura ad albero ternario**:

- Ogni processo crea **fino a 3 figli**
- Ogni processo si **mette in attesa** finché i suoi figli non terminano
- Ogni figlio attende per `N` secondi, dove `N` è il **livello** dell'albero
- Al termine stampa `"Concluso!"` e notifica al genitore

---

## ❓ Esercizio 6.6 - Analisi di codice con variabile globale: Analisi di codice con `glob`

```c
int glob = 6;
int pid = 0;

fork();

for (i = 1; i < 2; i++) {
    if (!fork()) {
        glob = glob * 2;
        pid = 1;
    }

    if (pid) {
        fork();
        glob = glob - 1;
    }
}

printf("Valore di glob = %d\n", glob);
```

👉 **Domanda:** *Qual è il valore della variabile `glob` per ogni processo?*

🧠 *Suggerimento*: analizza **quanti processi** si creano e **quali rami** eseguono le modifiche a `glob`. Ricorda che ogni processo ha una **copia indipendente** di `glob` dopo la `fork()`.
