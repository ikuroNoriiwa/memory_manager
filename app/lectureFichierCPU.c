#include "lectureFichierCPU.h"

DefCPU* getCPUInfo(){
	FILE *fichier = fopen("/proc/stat","r");
	char ligne[200];
	int cptCPU = 0; 
	char* tmp; 
	DefCPU* cpus = (DefCPU*)malloc(sizeof(DefCPU)*8);
	while(fgets(ligne,sizeof ligne, fichier) != NULL){
		//printf("%s", ligne);

		if(strstr(ligne,"cpu") != NULL){
			int i = 0; 
			tmp = strtok(ligne, " "); 
			while(tmp != NULL){
				printf("%s ", tmp);
				if(i == 0){
				
				}
				tmp = strtok(NULL, " ");
			}
			//printf("%s %s\n", strtok(ligne, " "), strtok(ligne, " ")++);
			//printf("%s \n", tmp[1]);
			cptCPU++; // compte le nombre de CPU (0 = all, 1 = cpu , ..., 8 = cpu 7) 
		}
	}

}
