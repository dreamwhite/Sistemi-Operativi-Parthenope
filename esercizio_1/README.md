# 🧪 Esercizio 1 - Compilare la libreria `libapue` (Stevens)

In questo esercizio vediamo come scaricare e compilare i sorgenti del libro di Stevens, fondamentali per testare gli esempi del corso.

## 📦 Passaggi

1. Scarica il file `src.3e.tar.gz` dal sito ufficiale:  
   👉 [http://apuebook.com/code3e.html](http://apuebook.com/code3e.html)

2. Decomprimi l’archivio nella tua cartella di lavoro. Ad esempio:

   ```bash
   tar xvf src.3e.tar.gz
   ```

3. Questo creerà una cartella chiamata `apue.3e` con tutto il codice sorgente.

4. *(Facoltativo)* Sposta la cartella dove preferisci. Ad esempio:

   ```bash
   mv apue.3e /home/tuo_utente/programmi/apue.3e
   ```

5. Entra nella cartella ed esegui la compilazione:

   ```bash
   cd /home/tuo_utente/programmi/apue.3e
   make
   ```

✅ Se tutto è andato bene, hai ora i file oggetto e le librerie pronte all’uso per compilare gli esercizi del libro all'interno della directory `lib`

---

📌 **Nota**: su alcune distro potresti dover installare `gcc` o i build tools (`build-essential` su Debian/Ubuntu) prima di compilare.
