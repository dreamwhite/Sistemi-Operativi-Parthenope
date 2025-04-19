# 🧟 Esercizio 4 - Zombie process & gestione dei processi

In questo esercizio si analizzano alcuni comportamenti legati alla **creazione dei processi** in Linux e al fenomeno degli **zombie process**.

---

## 🔹 Parte 1 - Esempio di base

Il codice seguente è stato fornito a lezione per mostrare la creazione di processi multipli con `fork()` e la modifica di una variabile globale:

```c
int glob = 20;
int pid = 0;

int main() {
    int i = 0;
    for (i = 2; i < 4; i++) {
        pid = fork();
        if (pid == 0) {
            glob = glob * 2;
            sleep(i + 1);
        }
    }
    glob = glob - 1;
    printf("Valore di glob = %d\n", glob);
}
```

---

## 🔹 Parte 2 - Creazione e attesa di processi

Un secondo esempio, usato per spiegare come attendere i processi figli con `wait()`:

```c
int main(int argc, char *argv[]) {
    pid_t childpid;
    int i, n;
    pid_t waitreturn;

    if (argc != 2) {
        fprintf(stderr, "Uso: %s processi\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    for (i = 1; i < n; i++) {
        if ((childpid = fork()))
            break;
    }

    while ((childpid != (waitreturn = wait(NULL)))) {
        if (waitreturn == -1)
            break;
    }

    fprintf(stderr, "processo %d, padre %d\n", getpid(), getppid());
    return 0;
}
```

---

## 🧟 Parte 3 - Zombie process

### ✍️ Traccia

> Scrivere un programma che crea uno **zombie** e poi esegue il comando `ps` per verificare che il processo è uno zombie.

### 💡 Suggerimento

- Un processo diventa zombie quando **termina** ma il padre **non lo ha ancora atteso**.
- Usa `fork()` per creare il figlio e fallo terminare subito con `exit(0)`.
- Il padre attende alcuni secondi (es. `sleep(10)`) e nel frattempo esegue `ps` per mostrare che il figlio è in stato `Z`.

Esempio base:

```c
int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Processo figlio
        exit(0);
    } else {
        // Processo padre
        sleep(10);
        system("ps -o pid,ppid,state,cmd");
    }

    return 0;
}
```

🔍 Output atteso: il figlio sarà in stato `Z` (zombie) finché il padre non lo "raccoglie" con `wait()`.
