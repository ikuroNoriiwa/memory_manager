#ifndef _UTIL_H
#define _UTIL_H

	float fnc_kBtoGB(int taille);
        float fnc_kBtoMB(int taille);	
	long fnc_getNumberInString(char* str); 
	void fnc_removeChar(char *str, int retirer);
	int msleep(long ms);
	char* getCurrentTime();
	int getNumberOfCore();
	void viderTampon(FILE *fichier);

#endif 
