# 🌐 Esercizio 9 - Socket TCP & connessioni multiple

In questo esercizio si lavora con **socket TCP (connection-oriented)** per la realizzazione di un client e un server. L'obiettivo è completare ed estendere il comportamento di un programma chiamato `upperserver.c`.

---

## ✍️ Parte 1 - Completare il client

Scrivere il codice del **client** che si connette al server esistente (`upperserver.c`) e:

1. Si **connette al server**
2. **Invia una stringa**
3. **Riceve la risposta** (in maiuscolo)
4. **Chiude la connessione**

📌 Il client utilizza socket TCP (AF_INET, SOCK_STREAM).  
Struttura iniziale:

```c
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("chiamata alla system call socket fallita");
        exit(1);
    }

    /* connessione al server */
    /* invio e ricezione della stringa */
    /* chiusura della connessione */
}
```

---

## ✍️ Parte 2 - Estendere il server con `fork()`

Modificare il programma **upperserver.c** in modo che:

- Possa **accettare più connessioni contemporaneamente**
- Utilizzi `fork()` per gestire **ogni nuova connessione** in un processo figlio separato

💡 Ogni volta che il server accetta una nuova connessione:
1. Crea un processo figlio con `fork()`
2. Il figlio gestisce la comunicazione con quel client
3. Il padre torna in ascolto per nuove connessioni

---

✅ Questo esercizio è una base per server concorrenti TCP su modello Unix.
