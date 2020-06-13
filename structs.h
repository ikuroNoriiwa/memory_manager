
#ifndef _STRUCTS_H
#define _STRUCTS_H

	typedef struct{
		int memTotale; 
		int memFree; 
		int memAvailable;
		int cached;
		int buffers; 
	}DefMemory; 
	
	typedef struct{
		char* user; 	//Nom d'utilisateur propriétaire du processus
		int pid; 	//PID 
		int ppid;	//PID du parent
		float cpu;	// CPU consommé -À TROUVER-
		float mem;	// mémoire consommé -À TROUVER-
		char* status;	// état du processus (RSDZTW) 
		char* command;	// commande lancée
		int start;	// heure de lancement
		int time; 	// temps de fonctionnement 
	}DefProcessus;
#endif
