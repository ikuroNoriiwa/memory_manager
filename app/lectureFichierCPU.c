#include "lectureFichierCPU.h"

/**
 * permet de récupérer les informations des différents CPU
 * fonction basée sur le fichier /proc/stat en mode read 
 * 
 * @param 
 * @return DefCPU* : tableau dynamiquement alloué de DefCPU contenant les informations de chaque CPU *
 */
DefCPU* getCPUInfo(){
	FILE *fichier = fopen("/proc/stat","r");
	char ligne[200];
	int cptCPU = 0; 
	char* tmp; 
	DefCPU* cpus = (DefCPU*)malloc(sizeof(DefCPU)*(getNumberOfCore()+1));
	while(fgets(ligne,sizeof ligne, fichier) != NULL){
		// lit ligne par ligne le fichier /proc/stat
		if(strstr(ligne,"cpu") != NULL){
			//si la ligne comprend la chiane "cpu", récupère les informations 
			//CPU 0 = processeur total
			//CPU1-8 = coeur
			int i = 0; 
			tmp = strtok(ligne, " "); 
			while(tmp != NULL){
				//printf("%s ", tmp);
				if(i == 0){
					cpus[cptCPU].cpuName = (char*)malloc(sizeof(char)*sizeof tmp);
					strcpy(cpus[cptCPU].cpuName, tmp);
					//printf("\n i : %d et nom : %s \n",cptCPU ,cpus[cptCPU].cpuName);
				}else if(i == 1){
				//	printf("\ni : %d ligne : %s et ligne long : %ld :::", i,tmp , fnc_getNumberInString(tmp));
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

				//printf("\n Nom : %s \n ", cpus[0].cpuName);
				i++;
			}
			//printf("%s %s\n", strtok(ligne, " "), strtok(ligne, " ")++);
			//printf("%s \n", tmp[1]);
			cptCPU++; // compte le nombre de CPU (0 = all, 1 = cpu , ..., 8 = cpu 7)
		        //printf("\n\n Test acces : %s \n, et test : %ld\n", cpus[cptCPU-1].cpuName,cpus[cptCPU-1].t_user);	
			
			//pour les ligne btime, processes, procs_running et proc_blocked stock dans cpus[0]
			//correspond au processeur total car informations globales
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
		//printf("\n Nom : %s \n ", cpus[0].cpuName);
	}
	fclose(fichier);
	return cpus;
}

/**
 * @deprecated
 * permet de calculer l'utilisation du processeur en prenant deux DefCPU en paramètre 
 * il faut dans l'idéal avoir 15 secondes entre chaque CPU pour avoir une utilisation correcte 
 * @param *cpu : premier CPU pour calcul
 * @param *cpu2 : second CPU avec un interval (min 1 seconde) pour calculer la charge
 * @return float : résultat de la charge processeur 
 */
float calculCPUUsage(DefCPU *cpu, DefCPU *cpu2){
//	printf("Nom %s\n",cpu->cpuName);
	double total = (cpu->t_user + cpu->t_nice + cpu->t_system + cpu->t_idle + cpu->t_iowait + cpu->t_irq + cpu->t_softirq);
	double calc = (cpu->t_idle * 100) / total;	

	//readUptime();

	double total2 = (cpu2->t_user + cpu2->t_nice + cpu2->t_system + cpu2->t_idle + cpu2->t_iowait + cpu2->t_irq + cpu2->t_softirq);
	double calc2 = (cpu2->t_idle * 100) / total;	
//	printf("Total = %f et \charge libre : %.1f et idle : %ld \n",total,calc,cpu->t_idle);
	
	return calc;
}


double* readUptime(double *val){
	FILE *fichier = fopen("/proc/uptime","r"); 
	char ligne [200]; 
	char* ptr;
	//double val[2];
	
	fgets(ligne,sizeof ligne, fichier);
	//printf("ligne complete : %s\n", ligne);
	val[0] = strtod(ligne, &ptr); 
	val[1] = strtod(ptr, NULL);
	//printf("test : %lf et %lf\n",val[0],val[1]);
	
	fclose(fichier);
	return val;
}
/**
 * renvoie le temps total du CPU (adition de tous les champs)
 * @param cpu : DefCPU 
 * @return long : addition de tous les paramètre de temps d'un processeur / cpu 
 */
long getTotalTime(DefCPU *cpu){
	return cpu->t_user + cpu->t_nice + cpu->t_system + cpu->t_irq + cpu->t_softirq + cpu->t_iowait + cpu->t_idle; 
}


float *fnctTestCPU(DefCPU *cpu1, DefCPU *cpu2){
	int i = 0;
	int numberOfCore = getNumberOfCore();
        float *chargeCPU = (float*)malloc(sizeof(float) * numberOfCore); 	
	for(i = 0 ; i <= numberOfCore ; i++){
	//	printf("\nCPU name : %s \n",cpu1[i].cpuName);
		double prevIdle = cpu1[i].t_idle + cpu1[i].t_iowait;
		double idle = cpu2[i].t_idle + cpu2[i].t_iowait; 

		double prevNonIdle = cpu1[i].t_user + cpu1[i].t_nice + cpu1[i].t_system + cpu1[i].t_irq + cpu1[i].t_softirq;
		double nonIdle = cpu2[i].t_user + cpu2[i].t_nice + cpu2[i].t_system + cpu2[i].t_irq + cpu2[i].t_softirq;

		double prevTotal = prevIdle + prevNonIdle;
		double total = idle + nonIdle;

		double totald = total - prevTotal;
		double idled = idle - prevIdle;
		float charge = ((totald - idled) / totald);
		chargeCPU[i] = charge * 100;
	//	printf("Charge : %.2f\n", charge*100);
	}
	return chargeCPU;
}

