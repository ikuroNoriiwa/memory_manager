#include <stdlib.h> 
#include <stdio.h> 
#include "app/lectureFichierMemory.h"
#include "app/lectureFichierProcess.h"
#include "app/lectureFichierCPU.h"

int main(int argc, char *argv[]){
	getMeminfo();
//	test();
//	printf("sizeof int : %d\n\n", sizeof(int));
	DefCPU* tmp = getCPUInfo();
	int i = 0; 

	for(i = 0 ; i < 8 ; i++){
		if(i == 0 ){
			printf("%s %ld %ld %ld %ld %ld %ld %ld \n\n", tmp[i].cpuName,tmp[i].t_user, tmp[i].t_nice, tmp[i].t_system, tmp[i].t_idle, tmp[i].t_iowait, tmp[i].t_irq, tmp[i].t_softirq);
			printf("btime : %ld\nprocesses : %ld\nprocs_running : %ld\nprocs_blocked : %ld\n", tmp[i].btime, tmp[i].processes, tmp[i].procs_running, tmp[i].procs_blocked);
		}else{
			printf("%s %ld %ld %ld %ld %ld %ld %ld \n", tmp[i].cpuName,tmp[i].t_user, tmp[i].t_nice, tmp[i].t_system, tmp[i].t_idle, tmp[i].t_iowait, tmp[i].t_irq, tmp[i].t_softirq);

		}

	}
	return 0; 

}
