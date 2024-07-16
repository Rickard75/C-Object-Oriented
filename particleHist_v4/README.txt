Per compilare qui bisogna usare le librerie dei design pattern contenute in "util/include".
A tal fine per compilare correttamente nel mio PC va eseguita l'istruzione:
WSL> g++ -Wall -I. -I "/mnt/c/Users/Asus/Desktop/UNI/CORSI/CORSI EXTRA/C++ e PROGRAMMAZIONE a OGGETTI - prof. Paolo Ronchese/ESEMPI ed ESERCIZI" 
     `root-config --cflags` -o main *.cc `root-config --libs`

Per runnare l'eseguibile, siccome ora le operazioni sono codificate dai nomi "dump", "plot" eccetera:
WSL> ./main sim 10 dump bg
oppure
WSL> ./main input ../bragg_events.dat plot hh.root bg

Poi per aprire il file root creato senza intestazione:
WSL> root -l hh.root
root[0]> Attaching file hh.root as _file0...
	(TFile *) 0x56363ded8330