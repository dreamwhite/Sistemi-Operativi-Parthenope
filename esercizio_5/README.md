# 🧬 Esercizio 5 - Esperimenti con `fork()`, processi e variabili globali

Questo esercizio è diviso in **più sezioni**: domande teoriche, codice da analizzare e due tracce vere e proprie.

---

## 🔹 Parte 1 - Cosa succede se modifichiamo il test?

Modifica proposta:  
Sostituire:

```c
if ((childpid = fork()) <= 0)
```

con:

```c
if ((childpid = fork()) == -1)
```

### 🔍 Risposta:

- Tutti i processi restano nel ciclo a meno che la `fork()` fallisca.
- Ogni iterazione del ciclo raddoppia il numero di processi, formando un **albero**.
- In figura con `n = 4`, si crea una **struttura ad albero** dove ogni processo crea figli a ogni iterazione.
- Il programma **non distingue** tra padre e figlio, quindi **entrambi continuano nel ciclo**.

---

## 🔹 Parte 2 - Analisi dei codici forniti

### 📄 Codice 1

```c
int glob = 5;
int pid = 0;
pid = fork();
glob--;
pid = fork();
glob--;
if (pid != 0) {
    pid = fork();
    glob--;
}
printf("Valore di glob = %d\n", glob);
```

🧠 Cosa succede?

- Ogni `fork()` crea un nuovo processo che ha una **copia indipendente** della variabile `glob`.
- Le modifiche a `glob` non si riflettono tra processi.
- Si generano **più processi** (fino a 8 in alcuni casi).
- Ogni processo stampa un valore diverso di `glob`, in base al percorso che ha seguito.

---

### 📄 Codice 2

```c
int glob = 5;
int pid = 0;

int main() {
    int i = 0;
    for (i = 1; i < 3; i++) {
        pid = fork();
        if (pid == 0) {
            glob = glob * 2;
            sleep(i + 1);
        }
        glob = glob + 1;
    }
    printf("Valore di glob = %d\n", glob);
}
```

🧠 Cosa succede?

- Ogni processo raddoppia `glob` se è un figlio e incrementa dopo ogni ciclo.
- I valori di `glob` cambiano **in modo indipendente** in ogni processo.
- I processi figli possono avere valori diversi a seconda del momento in cui avviene la `fork()`.

---

## 🧪 Parte 3 - Traccia 1

### ✍️ Scrivere un programma C che:

- Crea un processo figlio
- Stampa il messaggio **"In attesa"** e attende la terminazione del figlio
- Il figlio esegue il comando `ls -l`
- Quando il figlio termina:
  - Il padre stampa **"Nuovo figlio"**
  - Crea un secondo processo figlio
  - Il secondo figlio aspetta 5 secondi, stampa un messaggio e termina
  - Il padre stampa il PID del processo terminato

---

## 🧮 Parte 4 - Traccia 2

### ✍️ Scrivere un programma C che:

- Un processo padre crea un **processo figlio**
- Il figlio calcola la **sequenza di Fibonacci di ordine `n`**, con `n <= 12`
- Il figlio termina **restituendo il valore calcolato** come codice di uscita
- Il padre:
  - Attende il figlio
  - Esamina lo stato di terminazione
  - Se il figlio è terminato con successo **e il codice è < 50**:
    - Crea un **secondo figlio**
    - Il secondo figlio esegue `ls -al a.out`
    - Il padre lo attende e stampa un messaggio
  - Altrimenti, stampa un messaggio e termina

---

📌 Suggerimento: per leggere il valore di uscita da `wait()`, usare le macro `WIFEXITED(status)` e `WEXITSTATUS(status)` da `sys/wait.h`.
