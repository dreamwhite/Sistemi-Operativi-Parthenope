# 🔗 Esercizio 3 - Link simbolici e accesso a directory

In questo esercizio dovrai lavorare con i **link simbolici** e la lettura del contenuto di una directory.

## 📌 Obiettivo

1. Creare un **link simbolico** con il comando:

   ```bash
   ln -s file_originale link_symbolic
   ```

2. Scrivere un programma in **C** che:
   - Accede alla **directory** contenente il link
   - Seleziona il **link simbolico**
   - Stampa a video il **nome del file** linkato

---

💡 *Suggerimento*: puoi usare le funzioni della famiglia `dirent.h` (`opendir`, `readdir`, ecc.) per navigare nella directory.

Per verificare se un file è un link simbolico puoi usare `lstat()` e controllare che `st_mode` abbia il flag `S_IFLNK`.

Esempio di base:

```c
struct stat sb;
if (lstat("link_symbolic", &sb) == 0 && S_ISLNK(sb.st_mode)) {
    // è un link simbolico
}
```

---

## 🧠 Variante: trovare il link simbolico che punta al file più grande

Scrivere un programma in **C e POSIX sotto Linux** che:

- Scansiona la **directory corrente**
- Trova tutti i **link simbolici**
- Verifica a quale **file regolare** puntano
- Stampa a video il **nome del link simbolico** che punta al **file di taglia maggiore**

📌 *Assunzione*: i link simbolici **non puntano ad altri link simbolici**

---

🔎 *Tip:* puoi usare `readlink()` per leggere a cosa punta un symlink, e `stat()` sul path ottenuto per verificarne la dimensione.
