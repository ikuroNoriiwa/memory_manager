#include <stdlib.h>
#include <ncurses.h>

#include "../app/lectureFichierCPU.h"
#include "../app/lectureFichierMemory.h"
#include "../util/util.h"
#include "../structs.h"
#include "ihm.h"

#define GRAPH_HEIGHT 25
#define RAM_HEIGHT 10
#define RAM_WIDTH 107

void initAllColor(){
	init_pair(1, COLOR_BLUE, COLOR_BLACK); //fond noir, lettre bleu
	init_pair(2, COLOR_WHITE, COLOR_WHITE); //fond blanc, lettre blanche
	init_pair(3, COLOR_GREEN, COLOR_GREEN); // all green
	init_pair(4, COLOR_YELLOW, COLOR_YELLOW); // all yellow
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA); // all magenta
	init_pair(6, COLOR_RED, COLOR_RED); // all red
}

void affichMain(){
	WINDOW *menu, *pourcentage, *graphCPU, *ram;

	initscr();
	start_color();
	initAllColor();

	pourcentage = subwin(stdscr, GRAPH_HEIGHT, 7, 5, 0);
	menu = subwin(stdscr, 5, 107, 0, 0);
	graphCPU = subwin(stdscr, GRAPH_HEIGHT, 100, 5, 7);
	ram = subwin(stdscr, RAM_HEIGHT, RAM_WIDTH, 30, 0);

	box(pourcentage, ACS_VLINE, ACS_HLINE);
	box(menu, ACS_VLINE, ACS_HLINE);
	box(graphCPU, ACS_VLINE, ACS_HLINE);
	box(ram, ACS_VLINE, ACS_HLINE);

	refresh();
	affichMenuRam(ram);	
	affichMenuTopCPU(menu);
	afficherCPU(pourcentage, graphCPU, ram);
	refresh();

	getch();
	endwin();
}

void affichMenuTopCPU(WINDOW *menu){
	char *cpuName = getCPUName();
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

void afficherCPU(WINDOW *haut, WINDOW *graph, WINDOW *ram){
	DefCPU *charge1, *charge2;
	DefMemory *memory;
	int i = 1;
	float *tab;
 	int posRam = 0;
  	char *global = "Utilisation globale";
	int color = 0;
 
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
		msleep(100);
		charge2 = getCPUInfo();
		//affichRam(ram, memory, );
		posRam++;

		tab = fnctTestCPU(charge1, charge2);
		affichRam(ram, memory, tab[0]);
		//printf("test : %.2f\n",tab[0]);
		if(tab[0] < 5){
			hauteur = GRAPH_HEIGHT - 2;
			wattron(graph, COLOR_PAIR(2));
			color = 2;
		}else if(tab[0] >= 5.0 && tab[0] <= 10.0){
			hauteur = GRAPH_HEIGHT - 3;
			wattron(graph, COLOR_PAIR(2));
			color = 2;
		}else if(tab[0] > 10.0 && tab[0] <= 15.0){
			hauteur = GRAPH_HEIGHT - 4;
			wattron(graph, COLOR_PAIR(3));
			color = 3;
		}else if(tab[0] > 15.0 && tab[0] <= 20.0){
			hauteur = GRAPH_HEIGHT - 5;
			wattron(graph, COLOR_PAIR(3));
			color = 3;
		}else if(tab[0] > 20.0 && tab[0] <= 25.0){
			hauteur = GRAPH_HEIGHT - 6;
			wattron(graph, COLOR_PAIR(3));
			color = 3;
		}else if(tab[0] > 25.0 && tab[0] <= 30.0){
			hauteur = GRAPH_HEIGHT - 7;
			wattron(graph, COLOR_PAIR(3));
			color = 3;
		}else if(tab[0] > 30.0 && tab[0] <= 35.0){
			hauteur = GRAPH_HEIGHT - 8;
			wattron(graph, COLOR_PAIR(3));
			color = 3;
		}else if(tab[0] > 35.0 && tab[0] <= 40.0){
			hauteur = GRAPH_HEIGHT - 9;
			wattron(graph, COLOR_PAIR(4));
			color = 4;
		}else if(tab[0] > 40.0 && tab[0] <= 45.0){
			hauteur = GRAPH_HEIGHT - 10;
			wattron(graph, COLOR_PAIR(4));
			color = 4;
		}else if(tab[0] > 45.0 && tab[0] <= 50.0){
			hauteur = GRAPH_HEIGHT - 11;
			wattron(graph, COLOR_PAIR(4));
			color = 4;
		}else if(tab[0] > 50.0 && tab[0] <= 55.0){
			hauteur = GRAPH_HEIGHT - 12;
			wattron(graph, COLOR_PAIR(5));
			color = 5;
		}else if(tab[0] > 55.0 && tab[0] <= 60.0){
			hauteur = GRAPH_HEIGHT - 13;
			wattron(graph, COLOR_PAIR(5));
			color = 5;
		}else if(tab[0] > 60.0 && tab[0] <= 65.0){
			hauteur = GRAPH_HEIGHT - 14;
			wattron(graph, COLOR_PAIR(5));
			color = 5;
		}else if(tab[0] > 65.0 && tab[0] <= 70.0){
			hauteur = GRAPH_HEIGHT - 15;
			wattron(graph, COLOR_PAIR(5));
			color = 5;
		}else if(tab[0] > 70.0 && tab[0] <= 75.0){
			hauteur = GRAPH_HEIGHT - 16; 
			wattron(graph, COLOR_PAIR(6));
			color = 6;
		}else if(tab[0] > 75.0 && tab[0] <= 80.0){
			hauteur = GRAPH_HEIGHT - 17;
			wattron(graph, COLOR_PAIR(6));
			color = 6;
		}else if(tab[0] > 80.0 && tab[0] <= 85.0){
			hauteur = GRAPH_HEIGHT - 18;
			wattron(graph, COLOR_PAIR(6));
			color = 6;
		}else if(tab[0] > 85.0 && tab[0] <= 90.0){
			hauteur = GRAPH_HEIGHT - 19;
			wattron(graph, COLOR_PAIR(6));
			color = 6;
		}else if(tab[0] > 90.0 && tab[0] <= 95.0){
			hauteur = GRAPH_HEIGHT - 20;
			wattron(graph, COLOR_PAIR(6));
			color = 6;
		}else if(tab[0] > 95.0 && tab[0] <= 100.0){
			hauteur = GRAPH_HEIGHT - 21;
			wattron(graph, COLOR_PAIR(6));
			color = 6;
		}
	
		for(j = GRAPH_HEIGHT-2 ; j >= hauteur ; j--){
			mvwprintw(graph, j, i, "f");
			//affichage de la charge 
		}
		
		wattroff(graph, COLOR_PAIR(color));
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
		wrefresh(ram);
		free(tab);
	}
}

void affichRam(WINDOW *ram, DefMemory *memory, float fl){

	mvwprintw(ram, 2, 1 , "%.2f", fl);
}


void affichMenuRam(WINDOW *ram){
	mvwprintw(ram, 1, 4,"test");
	addch(ACS_VLINE);
	wrefresh(ram);
}
