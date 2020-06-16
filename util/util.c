#define _POSIX_C_SOURCE 199309L
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

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
