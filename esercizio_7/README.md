# 🧵 Esercizio 7 - Pipe e creazione di processi multipli

In questi esercizi lavoriamo con la **comunicazione tramite pipe** tra processi, simulando comandi tipici della shell come `ls`, `grep`, e `sort`.

---

## ✍️ Esercizio 7.1 - `ls -R | grep <pattern>`

Scrivere un programma in C che:

- Esegue il comando `ls -R | grep <pattern>`
- Dove `<pattern>` è inserito **dall'utente**
- Utilizza **due processi** distinti:
  - Uno per eseguire `ls -R`
  - Uno per eseguire `grep <pattern>`
- I processi devono comunicare attraverso una **pipe**

📌 Suggerimento:

- Usare `pipe()`, `fork()`, `dup2()`, `execlp()`/`execvp()`
- Il processo padre crea la pipe, poi genera i due figli

---

## ✍️ Esercizio 7.2 - `ls | sort | grep <pattern>`

Scrivere un programma in C che:

- Esegue il comando `ls | sort | grep <pattern>`
- Usa **tre processi distinti**, ognuno per uno dei comandi
- Comunica usando **due pipe**
- Il pattern è inserito **dall'utente**

📌 Suggerimento:

- La **prima pipe** collega `ls` a `sort`
- La **seconda pipe** collega `sort` a `grep`
- Ogni processo deve **ridirezionare input/output** correttamente con `dup2`

🧠 Questo esercizio simula una vera **pipeline a tre stadi**, tipica nei sistemi Unix-like.
