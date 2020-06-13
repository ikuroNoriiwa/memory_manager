#include <stdlib.h>
#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <dirent.h>

#include "../util/util.h"


char* getProcessName(char* pidProcess){
	char path[25] = "/proc/"; 
	int i = 0;

	strcat(path,pidProcess);
	strcat(path,"/status");
	
	FILE *fichier = fopen(path,"r");
	char ligne[200];

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		if(strstr(ligne, "Name:	") != NULL){
			for(i = 0; i < 6; i++){
				fnc_removeChar(ligne, 1);
			}
			printf("PRocNAme - NAME : %s",ligne);
			//printf(" + len %d et %c\n", strlen(ligne), ligne[6]);

		}
	}
	
	fclose(fichier);	
	
	
	return NULL;
}

void test(){

	DIR* rep = NULL; 
	struct dirent* fichierLu = NULL;	
	rep = opendir("/proc");
	
	if(rep == NULL){
		exit(1);
	}else{
		puts("Dossier ouvert");
		while(fichierLu = readdir(rep)){
			//printf("\nNom fichier : %s", fichierLu->d_name);
			if(isdigit(fichierLu->d_name[0])){
				//printf(" * ");
				getProcessName(fichierLu->d_name);
			}
		}
		closedir(rep);
	}
}

