#ifndef _LECTUREFICHIERCPU_H
#define _LECTUREFICHIERCPU_H


#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 

#include "../structs.h"
#include "../util/util.h"

	DefCPU* getCPUInfo();
	float calculCPUUsage(DefCPU *cpu, DefCPU *cpu2);
	double* readUptime(double *val);
	long getTotalTime(DefCPU *cpu);
	float *fnctTestCPU(DefCPU *cpu1, DefCPU *cpu2);

#endif 
