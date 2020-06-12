#include <math.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * converti les ko(KiloOctets ou KiloByte en anglais) en Go (GigaOctet ou GigaByte en anglais)
 * @param taille : int correspondant à la taille en ko
 * @return float : la conversion en Go 
 */
float fnc_kBtoGB(int taille){
	return (taille / pow(10,6));
}

float fnc_kBtoMB(int taille){
	return (taille / pow(10,3));
}

/**
 * converti une string (char*) en int 
 * supprime les lettres et ne récupère que les chiffre
 * @param str : char* comprenant lettre en chiffre (ex type de RAM et taille)
 * @return int : int récupéré dans la string 
 */
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
