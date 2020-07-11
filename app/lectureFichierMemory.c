#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../util/util.h"
#include "../structs.h"

DefMemory* getMeminfo(){
	FILE *fichier = fopen("/proc/meminfo","r");
	char ligne[200];
	long memTMP = 0;
	DefMemory* memoire = (DefMemory*)malloc(sizeof(DefMemory)); 

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		if(strstr(ligne, "MemTotal:") != NULL){
			memTMP = fnc_getNumberInString(ligne);
			memoire->memTotale = memTMP+1; 
		}else if(strstr(ligne, "MemFree:") !=NULL){
			memoire->memFree = fnc_getNumberInString(ligne);
		}else if(strstr(ligne, "MemAvailable:") != NULL){
			memoire->memAvailable = fnc_getNumberInString(ligne);
		}else if(strstr(ligne, "Cached") != NULL){
			memoire->cached = fnc_getNumberInString(ligne);
		}else if(strstr(ligne, "Buffers:") != NULL){
		       memoire->buffers = fnc_getNumberInString(ligne);
		}	       

	}
	fclose(fichier);
	printf("MemTota : %.2f\nMemFree : %.2f\nMemAvai : %.2f\nCached : %.2f\nBuffers : %.2f\n ",fnc_kBtoGB(memoire->memTotale), fnc_kBtoGB(memoire->memFree), fnc_kBtoGB(memoire->memAvailable), fnc_kBtoGB(memoire->cached),fnc_kBtoMB(memoire->buffers));
	return memoire; 
}


void printMem(){
	DefMemory* memoire = getMeminfo();

	printf("MemTota : %.2f\nMemFree : %.2f\nMemAvai : %.2f\nCached : %.2f\nBuffers : %.2f\n ",fnc_kBtoGB(memoire->memTotale), fnc_kBtoGB(memoire->memFree), fnc_kBtoGB(memoire->memAvailable), fnc_kBtoGB(memoire->cached),fnc_kBtoMB(memoire->buffers));
}
