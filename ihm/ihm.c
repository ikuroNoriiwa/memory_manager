#include <stdlib.h>
#include <ncurses.h>

#include "../app/lectureFichierCPU.h"
#include "../util/util.h"
#include "../structs.h"
#include "ihm.h"

#define GRAPH_HEIGHT 25

void affichMain(){
	WINDOW *menu, *pourcentage, *graphCPU;

	initscr();
	start_color();


	pourcentage = subwin(stdscr, GRAPH_HEIGHT, 7, 5, 0);
	menu = subwin(stdscr, 5, 107, 0, 0);
  graphCPU = subwin(stdscr, GRAPH_HEIGHT, 100, 5, 7);

	box(pourcentage, ACS_VLINE, ACS_HLINE);
	box(menu, ACS_VLINE, ACS_HLINE);
	box(graphCPU, ACS_VLINE, ACS_HLINE);
	
	affichMenuTopCPU(menu);
	afficherCPU(pourcentage, graphCPU);
	refresh();

	getch();
	endwin();
}

void affichMenuTopCPU(WINDOW *menu){
	char *cpuName = getCPUName();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	mvwprintw(menu, 1, 1,"hostname : ");
	wattron(menu, COLOR_PAIR(1));
	mvwprintw(menu,1,12,"%s",getHostname() );
	wattroff(menu, COLOR_PAIR(1));
	mvwprintw(menu,1,107-(strlen(cpuName)+14),"model name : ");
	wattron(menu, COLOR_PAIR(1));
	mvwprintw(menu,1,107-(strlen(cpuName)+1),"%s",cpuName);
	wattroff(menu, COLOR_PAIR(1));
	wrefresh(menu);
}

void afficherCPU(WINDOW *haut, WINDOW *graph){
	DefCPU *charge1, *charge2;
	int i = 1;
	float *tab;
 
  char *global = "Utilisation globale";
 
  mvwprintw(graph, 1,(100/2 - strlen(global)/2), "%s", global);

	mvwprintw(haut, GRAPH_HEIGHT - 22, 1, "100%%");
	mvwprintw(haut, GRAPH_HEIGHT - 21, 1, " 95%%");
	mvwprintw(haut, GRAPH_HEIGHT - 20, 1, " 90%%");
	mvwprintw(haut, GRAPH_HEIGHT - 19, 1, " 85%%");
	mvwprintw(haut, GRAPH_HEIGHT - 18, 1, " 80%%");
	mvwprintw(haut, GRAPH_HEIGHT - 17, 1, " 75%%");
	mvwprintw(haut, GRAPH_HEIGHT - 16, 1, " 70%%");
	mvwprintw(haut, GRAPH_HEIGHT - 15, 1, " 65%%");
	mvwprintw(haut, GRAPH_HEIGHT - 14, 1, " 60%%");
	mvwprintw(haut, GRAPH_HEIGHT - 13, 1, " 55%%");
	mvwprintw(haut, GRAPH_HEIGHT - 12, 1, " 50%%");
	mvwprintw(haut, GRAPH_HEIGHT - 11, 1, " 45%%");
	mvwprintw(haut, GRAPH_HEIGHT - 10, 1, " 40%%");
	mvwprintw(haut, GRAPH_HEIGHT - 9, 1, " 35%%");
	mvwprintw(haut, GRAPH_HEIGHT - 8, 1, " 30%%");
	mvwprintw(haut, GRAPH_HEIGHT - 7, 1, " 25%%");
	mvwprintw(haut, GRAPH_HEIGHT - 6, 1, " 20%%");
	mvwprintw(haut, GRAPH_HEIGHT - 5, 1, " 15%%");
	mvwprintw(haut, GRAPH_HEIGHT - 4, 1, " 10%%");
	mvwprintw(haut, GRAPH_HEIGHT - 3, 1, "  5%%");
	mvwprintw(haut, GRAPH_HEIGHT - 2, 1, "  0%%");

	while(1/*getch() != 'q'*/){
		int hauteur = 21;
		int j = 21; 
		charge1 = getCPUInfo();
		msleep(250);
		charge2 = getCPUInfo();
		
		tab = fnctTestCPU(charge1, charge2);
		//printf("test : %.2f\n",tab[0]);
		if(tab[0] < 5){
			hauteur = GRAPH_HEIGHT - 2;
		}else if(tab[0] > 5 && tab[0] < 10){
			hauteur = GRAPH_HEIGHT - 3;
		}else if(tab[0] > 10 && tab[0] < 15){
			hauteur = GRAPH_HEIGHT - 4;
		}else if(tab[0] > 15 && tab[0] < 20){
			hauteur = GRAPH_HEIGHT - 5;
		}else if(tab[0] > 20 && tab[0] < 25){
			hauteur = GRAPH_HEIGHT - 6;
		}else if(tab[0] > 25 && tab[0] < 30){
			hauteur = GRAPH_HEIGHT - 7;
		}else if(tab[0] > 30 && tab[0] < 35){
			hauteur = GRAPH_HEIGHT - 8;
		}else if(tab[0] > 35 && tab[0] < 40){
			hauteur = GRAPH_HEIGHT - 9;
		}else if(tab[0] > 40 && tab[0] < 45){
			hauteur = GRAPH_HEIGHT - 10;
		}else if(tab[0] > 45 && tab[0] < 50){
			hauteur = GRAPH_HEIGHT - 11;
		}else if(tab[0] > 50 && tab[0] < 55){
			hauteur = GRAPH_HEIGHT - 12;
		}else if(tab[0] > 55 && tab[0] < 60){
			hauteur = GRAPH_HEIGHT - 13;
		}else if(tab[0] > 60 && tab[0] < 65){
			hauteur = GRAPH_HEIGHT - 14;
		}else if(tab[0] > 65 && tab[0] < 70){
			hauteur = GRAPH_HEIGHT - 15;
		}else if(tab[0] > 70 && tab[0] < 75){
			hauteur = GRAPH_HEIGHT - 16; 
		}else if(tab[0] > 75 && tab[0] < 80){
			hauteur = GRAPH_HEIGHT - 17;
		}else if(tab[0] > 80 && tab[0] < 85){
			hauteur = GRAPH_HEIGHT - 18;
		}else if(tab[0] > 85 && tab[0] < 90){
			hauteur = GRAPH_HEIGHT - 19;
		}else if(tab[0] > 90 && tab[0] < 95){
			hauteur = GRAPH_HEIGHT - 20;
		}else if(tab[0] > 95 && tab[0] < 100){
			hauteur = GRAPH_HEIGHT - 21;
		}
		
		for(j = GRAPH_HEIGHT-2 ; j >= hauteur ; j--){
			mvwprintw(graph, j, i, "a");
		}

		for(j = hauteur -1 ; j >= 2 ; j--){
			mvwprintw(graph, j , i , " ");
		}
		i++;
		if(i == 99){
			i = 1;	
		}else{
			for(j = GRAPH_HEIGHT -2  ; j >= 2 ; j--){
				if(i < 98){
					mvwprintw(graph, j , i + 1, " ");
				}
			}	
		}	
		wrefresh(graph);
		wrefresh(haut);	
		free(tab);
	}
}
