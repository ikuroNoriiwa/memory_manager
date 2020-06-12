#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int fnc_getNumberInString(char* str);
float fnc_kiloBYTEInGigaBYTE(int taille);

int main(){

	FILE *fichier = fopen("/proc/meminfo", "r");
	char ligne[200];
	long memTotale = 0; 

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		if(strstr(ligne, "MemTotal:") != NULL){
			char *ptr = ligne;
			printf("%s", ligne);
			memTotale = fnc_getNumberInString(ligne);
			printf("%d\n", memTotale+1);
			printf("Gig %.2f\n", fnc_kiloBYTEInGigaBYTE(memTotale));
		}
	}
	fclose(fichier);

	return 0;
}


## Lib Ctype.h
int fnc_getNumberInString(char* str){
	char *ptr = str;
	int ret = 0;
	while(*ptr){
		if(isdigit(*ptr)){
			ret = strtol(ptr, &ptr, 10);
		}else{
			ptr++;
		}
	}

	return ret; 
}


## Lib math.h
float fnc_kiloBYTEInGigaBYTE(int taille){
	float ret = 0; 

	ret = taille / pow(10,6);
	return ret; 

}
