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
	//afficherCPU();
//	getCPUName();
	//affichMain();
//	printf("%s\n", __TIME__);
	getMeminfo();/*
//	test();
//	printf("sizeof int : %d\n\n", sizeof(int));
	double val1[2];
	double val2[2];
	DefCPU* tmp = getCPUInfo();
	int i = 0; 
	double totalCPU1 = 0 ; 
	double totalCPU2 = 0; 
	float charge1;
	float charge2;
	printf("TEST : %s\n",tmp[i].cpuName);
	for(i = 0 ; i <= getNumberOfCore() ; i++){
		if(i == 0 ){
			printf("%s %ld %ld %ld %ld %ld %ld %ld \n\n", tmp[i].cpuName,tmp[i].t_user, tmp[i].t_nice, tmp[i].t_system, tmp[i].t_idle, tmp[i].t_iowait, tmp[i].t_irq, tmp[i].t_softirq);
			printf("btime : %ld\nprocesses : %ld\nprocs_running : %ld\nprocs_blocked : %ld\n", tmp[i].btime, tmp[i].processes, tmp[i].procs_running, tmp[i].procs_blocked);
		//	totalCPU1 = (tmp[i].t_user + tmp[i].t_nice + tmp[i].t_system + tmp[i].t_idle + tmp[i].t_iowait + tmp[i].t_irq + tmp[i].t_softirq);
		//	printf("utilisation CPU sur long terme : %lf\n",((totalCPU1 - tmp[i].t_idle)*100)/totalCPU1);
		}else{
			printf("%s %ld %ld %ld %ld %ld %ld %ld \n", tmp[i].cpuName,tmp[i].t_user, tmp[i].t_nice, tmp[i].t_system, tmp[i].t_idle, tmp[i].t_iowait, tmp[i].t_irq, tmp[i].t_softirq);

		}

	}

	for( i = 0; i <= getNumberOfCore() ; i++){	
		calculCPUUsage(&tmp[i],&tmp[i]);
	}
	
	printf("%s\n", getCurrentTime());
	printf("%s\n",getCurrentTime());

	totalCPU1 = (tmp[0].t_user + tmp[0].t_nice + tmp[0].t_system + tmp[0].t_idle + tmp[0].t_iowait + tmp[0].t_irq + tmp[0].t_softirq);
	charge1 = ((totalCPU1 - tmp[0].t_idle)*100) / totalCPU1; 
	
	readUptime(val1);
	msleep(1000);

	DefCPU* tmp2 = getCPUInfo();
	totalCPU2 = (tmp2[0].t_user + tmp2[0].t_nice + tmp2[0].t_system + tmp2[0].t_idle + tmp2[0].t_iowait + tmp2[0].t_irq + tmp2[0].t_softirq);
	//charge2 = ((totalCPU1 - tmp2[0].t_idle)*100) / totalCPU1; 
	//printf("Charge 2 derniere secondes : %f\n",(charge1-charge2) );
	fnctTestCPU(tmp, tmp2);
	readUptime(val2);
//	printf("valeurs charge CPU 1 : %lf et %lf charge 2 : %lf et %lf\n",val1[0],val1[1],val2[0],val2[1]); 
//	printf("charge CPU %lf\n", (100-100*(val2[1]-val1[1])/(val2[0]-val1[0])));
	printf("%s\n", getCurrentTime());*/
	return 0; 

}


void lancementAppli(){
	DefCPU *charge1; 
	DefCPU *charge2;
	float *tab;	
	printf("###INIT APP###\n");
	printf("  #INIT MEM#   \n");
	printMem();
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
