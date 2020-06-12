#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/util.h"


int getMeminfo(){
	FILE *fichier = fopen("/proc/meminfo","r");
	char ligne[200];
	long memTotale = 0;

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		if(strstr(ligne, "MemTotal:") != NULL){
			char *ptr = ligne;
			printf("%s", ligne); 
			memTotale = fnc_getNumberInString(ligne);
			printf("%d\n", memTotale+1);
			printf("Gig %.2f\n", fnc_kBtoGB(memTotale));
		}
	}
	fclose(fichier);

	return 0; 
} 
