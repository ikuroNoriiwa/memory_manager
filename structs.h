
#ifndef _STRUCTS_H
#define _STRUCTS_H

	typedef struct{
		long memTotale; 
		long memFree; 
		long memAvailable;
		long cached;
		long buffers; 
	}DefMemory; 
	
	typedef struct{
		char* name;	//nom du processus
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

	typedef struct{
		char* cpuName; 	// nom du CPU (cpu = full, cpu1, ..., cpu7 )
		long t_user;	// temps passé en mode USER
		long t_nice;	// temps passé en mode priorité basse (nice)
		long t_system;	// temps passé en mode système
		long t_idle;	// temps passé en mode inactivité (twiddling thumbs you know)
		long t_iowait;	// temps d'attente des I/O
		long t_irq;	// temps de service des interruption
		long t_softirq;	// temps de services deds interruptions logicielles 
		/* CALCULS POUR LES CPUs
		 *
		 * (user + nice + system + idle + iowait +irq + softirq ) = 100% CPU time
		 *
		 * (idle * 100) / (user + nice + system + idle + iowait + irq + softirq) = % de charge libre 
		 *
		 */
		long btime; 	// date de démarrage du système (en s depuis le 01/01/1970)
		long processes;	// nombre de processus exécuté depuis le démarrage
		long procs_running; // nombre de processus en cours sur les CPU
		long procs_blocked; // nombre de processus en attente d'I/O 
	}DefCPU; 
#endif
