# 🔧 Esercizio 2 - Somma di coppie di interi con `read` e `write`

Scrivere un programma in **C** che:

- Prende in input **coppie di interi** utilizzando la system call `read`
- Calcola la **somma** degli interi
- Stampa a video il risultato utilizzando la system call `write`
- Termina quando il **primo input è `-1`**

## 🧠 Assunzioni

- Gli interi inseriti sono **di una sola cifra** (es. `3`, `7`, `0`, `-1`)

---

💡 *Suggerimento*: per semplificarti la vita puoi leggere da `stdin` un numero per volta e convertire da carattere a intero con una semplice sottrazione (`'0'`).

Esempio (pseudo-input):
```
3 5
→ Output: 8

1 7
→ Output: 8

-1 0
→ Il programma termina
```

---

## 🛠️ Variante: uso dei file al posto di stdin/stdout

Modificare il programma in modo che:

- Legga l'input dal file `testfile`
- Scriva l'output nel file `outputfile`

⚠️ **Tutte le `read` devono avvenire su `STDIN_FILENO`**  
⚠️ **Tutte le `write` devono avvenire su `STDOUT_FILENO`**

Per farlo, usare le funzioni di duplicazione dei file descriptor (`dup` / `dup2`) per reindirizzare gli stream standard.

Esempio di flusso:
```c
int fd_in = open("testfile", O_RDONLY);
dup2(fd_in, STDIN_FILENO);

int fd_out = open("outputfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd_out, STDOUT_FILENO);
```
Dopo questa configurazione, il resto del programma può restare invariato.
