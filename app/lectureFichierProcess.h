
#ifndef _LECTUREFICHIERPROCESS_H
#define _LECTUREFICHIERPROCESS_H

#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> 
#include <string.h>
#include <dirent.h>

#include "../structs.h"
#include "../util/util.h"

	DefProcessus* getProcessName(char* pidProcess);
	void test();
	char* getUser(uid_t uid);
#endif 
