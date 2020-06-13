#include "lectureFichierProcess.h"


DefProcessus* getProcessName(char* pidProcess){
	char path[25] = "/proc/"; 
	int i = 0;
	
	DefProcessus* processus = (DefProcessus*)malloc(sizeof(DefProcessus));
	strcat(path,pidProcess);
	strcat(path,"/status");
	
	FILE *fichier = fopen(path,"r");
	char ligne[200];

	while(fgets(ligne, sizeof ligne, fichier) != NULL){
		//Get name from ps>
		//printf("debug : %s",ligne);
		if(strstr(ligne, "Name:	") != NULL){
			for(i = 0; i < 6; i++){
				fnc_removeChar(ligne, 1);
			}
			processus->name = (char*)malloc(sizeof(char)*sizeof ligne);
			strcpy(processus->name,ligne);
			processus->name[strlen(processus->name)-1] = '\0';
			//printf("PRocNAme - NAME : %s",processus->name);
			//printf(" + len %d et %c", strlen(ligne), ligne[6]);
		}else if(strstr(ligne, "Uid:") != NULL){
			//printf(" et %s \n",getUser(fnc_getNumberInString(ligne)));
			processus->user = getUser(fnc_getNumberInString(ligne));
		}else if((strstr(ligne, "Pid:") != NULL) && (strstr(ligne,"Tracer") == NULL)){
			if(strstr(ligne, "PPid:")!= NULL){
				processus->ppid = fnc_getNumberInString(ligne);
				printf("et ppid:%d\n", processus->ppid);
			}else{
				processus->pid = fnc_getNumberInString(ligne);
				printf(" ET pid:%d \n", processus->pid);
			}
		}
	//	printf("\n");
	}
	
	fclose(fichier);	
	
}

void test(){

	DIR* rep = NULL; 
	struct dirent* fichierLu = NULL;	
	rep = opendir("/proc");
	
	if(rep == NULL){
		exit(1);
	}else{
		puts("Dossier ouvert");
		while(fichierLu = readdir(rep)){
			//printf("\nNom fichier : %s", fichierLu->d_name);
			if(isdigit(fichierLu->d_name[0])){
				//printf(" * ");
				getProcessName(fichierLu->d_name);
			}
		}
		closedir(rep);
	}
}

char* getUser(uid_t uid){
	struct passwd *pws; 
	pws = getpwuid(uid);

	return pws->pw_name;
}
