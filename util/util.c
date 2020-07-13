#define _POSIX_C_SOURCE 199309L
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdio.h> 
#include "util.h"
/**
 * converti les ko(KiloOctets ou KiloByte en anglais) en Go (GigaOctet ou GigaByte en anglais)
 * @param taille : int correspondant à la taille en ko
 * @return float : la conversion en Go 
 */
float fnc_kBtoGB(long taille){
	return (taille / pow(10,6));
}

float fnc_kBtoMB(int taille){
	return (taille / pow(10,3));
}

/**
 * converti une string (char*) en int 
 * @param str : char* comprenant lettre en chiffre (ex type de RAM et taille)
 * @return int : int récupéré dans la string 
 */
long fnc_getNumberInString(char* str){
	char *ptr = str;
	long ret = 0;
	while(*ptr){
		if(isdigit(*ptr)){
			ret = strtol(ptr, &ptr, 10);
		}else{
			ptr++;
		}
	}

	return ret; 
}


void fnc_removeChar(char *str, int retirer){
	int x = 0;
	
	retirer--;
	while(str[x] != '\0'){
		if(x >= retirer){
			str[x] = str[x+1];
		}
		x++;
	}
	
}

int msleep(long tms){
	struct timespec ts; 
	int ret; 

	if(tms < 0){
		errno = EINVAL;
		return -1;
	}	

	ts.tv_sec = tms / 1000;
	ts.tv_nsec = (tms % 1000) * 1000000;

	do{
		ret = nanosleep(&ts , &ts);
	}while(ret && errno == EINTR);

	return ret; 

}


char* getCurrentTime(){
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	return asctime(timeinfo);
}


int getNumberOfCore(){
	FILE *fichier = fopen("/proc/stat", "r");
	if(fichier == NULL){
		printf("error : %s et nomb : %d\n ", strerror(errno), errno);
	}
	char ligne[200];
	int cpt = 0;
	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		if(strstr(ligne, "cpu") != NULL){
			cpt++;	
		}
	}
	cpt = cpt - 1;

	fclose(fichier);
	return cpt;
}


void viderTampon(FILE *fichier){
	int c; 
	while((c = fgetc(fichier)) != '\n'){
	}
}



char* getHostname(){
	FILE *fichier = fopen("/etc/hostname", "r");
	char ligne[200];
	char *nom;
	if(fichier == NULL){
		fprintf(stderr, "fnc util::getHostname err : %s et errno %d\n",strerror(errno), errno);
		exit(EXIT_FAILURE);
	}

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		nom = (char*)malloc(sizeof(char) * sizeof(ligne));
		strcpy(nom,ligne);
		nom[strlen(nom) - 1] = '\0';
	}
	
	fclose(fichier);
	return nom;
}

char* getCPUName(){
	FILE *fichier = fopen("/proc/cpuinfo", "r");
	char ligne[200];
	char *nomCPU;
	int i = 0;

	if(fichier == NULL){
		fprintf(stderr, "fnc util::getCPUName err : %s et errno %d\n",strerror(errno), errno);
		exit(EXIT_FAILURE);
	}

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		if(strstr(ligne, "model name") != NULL){
			for(i = 0; i < 13 ; i++){
				fnc_removeChar(ligne,1);
			}
			nomCPU = (char*)malloc(sizeof(char) * strlen(ligne));
			strcpy(nomCPU, ligne);
			nomCPU[strlen(nomCPU) -1] = '\0';
			break;
		}
		
	}

	return nomCPU;
}

