#include <stdlib.h> 
#include <stdio.h> 
#include "app/lectureFichierMemory.h"
#include "app/lectureFichierProcess.h"
#include "app/lectureFichierCPU.h"

int main(int argc, char *argv[]){
	getMeminfo();
//	test();
	printf("sizeof int : %d\n\n", sizeof(int));
	getCPUInfo();
	return 0; 

}
