#include <stdlib.h> 
#include <stdio.h> 
#include "app/lectureFichierMemory.h"
#include "app/lectureFichierProcess.h"
#include "app/lectureFichierCPU.h"
#include "util/util.h"
#include "ihm/ihm.h"
void lancementAppli();

int main(int argc, char *argv[]){
//	lancementAppli();
	affichMain();
	return 0; 

}


void lancementAppli(){
	DefCPU *charge1; 
	DefCPU *charge2;
	DefMemory *memory;
	float *tab;	
	printf("###INIT APP###\n");
	printf("  #INIT MEM#   \n");
	memory = getMeminfo();
	printf("test ram : %ld\n", memory->memFree);
	//printMem();
	printf("  #END MEM#   \n");

	printf("  #INIT CPU#   \n");
        printf("Nombre de coeur : %d\n",getNumberOfCore());
	printf("Temps total : %ld \n", getTotalTime(getCPUInfo()));
	while(1){
		charge1 = getCPUInfo();
		msleep(250);
		charge2 = getCPUInfo(); 
		tab = fnctTestCPU(charge1, charge2);
		printf("charge : %.2f\n",tab[0]);
		free(charge1);
		free(charge2);
	}
	printf("  #END CPU#   \n");

	printf("###END APP###\n");
}
