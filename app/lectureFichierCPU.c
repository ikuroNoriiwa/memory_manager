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
				//printf("%s ", tmp);
				if(i == 0){
					cpus[cptCPU].cpuName = (char*)malloc(sizeof(char)*sizeof tmp);
					strcpy(cpus[cptCPU].cpuName, tmp);
				}else if(i == 1){
					//printf("\ni : %d ligne : %s et ligne long : %ld :::", i,tmp , fnc_getNumberInString(tmp));
					cpus[cptCPU].t_user = fnc_getNumberInString(tmp);
				}else if(i == 2){
					cpus[cptCPU].t_nice = fnc_getNumberInString(tmp);
				}else if(i == 3){
					cpus[cptCPU].t_system = fnc_getNumberInString(tmp);
				}else if(i == 4){
					cpus[cptCPU].t_idle = fnc_getNumberInString(tmp);
				}else if(i == 5){
					cpus[cptCPU].t_iowait = fnc_getNumberInString(tmp);
				}else if(i == 6){
					cpus[cptCPU].t_irq = fnc_getNumberInString(tmp);
				}else if(i == 7){
					cpus[cptCPU].t_softirq = fnc_getNumberInString(tmp);
				}
				tmp = strtok(NULL, " ");
				i++;
			}
			//printf("%s %s\n", strtok(ligne, " "), strtok(ligne, " ")++);
			//printf("%s \n", tmp[1]);
			cptCPU++; // compte le nombre de CPU (0 = all, 1 = cpu , ..., 8 = cpu 7)
		        //printf("\n\n Test acces : %s \n, et test : %ld\n", cpus[cptCPU-1].cpuName,cpus[cptCPU-1].t_user);	
		}else if(strstr(ligne,"btime") != NULL){
			cpus[0].btime = fnc_getNumberInString(ligne);
		}else if(strstr(ligne,"processes") != NULL){
			cpus[0].processes = fnc_getNumberInString(ligne);
		}else if(strstr(ligne,"procs_running") != NULL){
			cpus[0].procs_running= fnc_getNumberInString(ligne);
		}else if(strstr(ligne,"proc_blocked") !=NULL){
			cpus[0].procs_blocked = fnc_getNumberInString(ligne);
		}
		
		//cptCPU++; // compte le nombre de CPU (0 = all, 1 = cpu , ..., 8 = cpu 7)
	     	//printf("\n\n Test acces : %s \n, et test : %ld\n", cpus[cptCPU-1].cpuName,cpus[cptCPU-1].t_user);	
	}
	return cpus;
}
