#include <stdlib.h>
#include <ncurses.h>

#include "../app/lectureFichierCPU.h"
#include "../util/util.h"
#include "../structs.h"

void afficherCPU(){
	WINDOW *haut, *graph; 
	DefCPU *charge1, *charge2;
	int i = 1;
	float *tab;
	initscr(); 
	start_color();

	haut  = subwin(stdscr, 23, 7, 0, 0);
	graph = subwin(stdscr, 23, 100, 0, 7);

	box(haut, ACS_VLINE, ACS_HLINE);
	box(graph, ACS_VLINE, ACS_HLINE);

	mvwprintw(haut, 1, 1, "100%%");
	mvwprintw(haut, 2, 1, "95%%");
	mvwprintw(haut, 3, 1, "90%%");
	mvwprintw(haut, 4, 1, "85%%");
	mvwprintw(haut, 5, 1, "80%%");
	mvwprintw(haut, 6, 1, "75%%");
	mvwprintw(haut, 7, 1, "70%%");
	mvwprintw(haut, 8, 1, "65%%");
	mvwprintw(haut, 9, 1, "60%%");
	mvwprintw(haut, 10, 1, "55%%");
	mvwprintw(haut, 11, 1, "50%%");
	mvwprintw(haut, 12, 1, "45%%");
	mvwprintw(haut, 13, 1, "40%%");
	mvwprintw(haut, 14, 1, "35%%");
	mvwprintw(haut, 15, 1, "30%%");
	mvwprintw(haut, 16, 1, "25%%");
	mvwprintw(haut, 17, 1, "20%%");
	mvwprintw(haut, 18, 1, "15%%");
	mvwprintw(haut, 19, 1, "10%%");
	mvwprintw(haut, 20, 1, "05%%");
	mvwprintw(haut, 21, 1, "00%%");

	while(1/*getch() != 'q'*/){
		int hauteur = 21;
		int j = 21; 
		charge1 = getCPUInfo();
		msleep(250);
		charge2 = getCPUInfo();
		
		tab = fnctTestCPU(charge1, charge2);
		//printf("test : %.2f\n",tab[0]);
		if(tab[0] < 5){
			hauteur = 21;
		}else if(tab[0] > 5 && tab[0] < 10){
			hauteur = 20;
		}else if(tab[0] > 10 && tab[0] < 15){
			hauteur = 19;
		}else if(tab[0] > 15 && tab[0] < 20){
			hauteur = 18;
		}else if(tab[0] > 20 && tab[0] < 25){
			hauteur = 17;
		}else if(tab[0] > 25 && tab[0] < 30){
			hauteur = 16;
		}else if(tab[0] > 30 && tab[0] < 35){
			hauteur = 15;
		}else if(tab[0] > 35 && tab[0] < 40){
			hauteur = 14;
		}else if(tab[0] > 40 && tab[0] < 45){
			hauteur = 13;
		}else if(tab[0] > 45 && tab[0] < 50){
			hauteur = 12;
		}else if(tab[0] > 50 && tab[0] < 55){
			hauteur = 11;
		}else if(tab[0] > 55 && tab[0] < 60){
			hauteur = 10;
		}else if(tab[0] > 60 && tab[0] < 65){
			hauteur = 9;
		}else if(tab[0] > 65 && tab[0] < 70){
			hauteur = 8;
		}else if(tab[0] > 70 && tab[0] < 75){
			hauteur = 7; 
		}else if(tab[0] > 75 && tab[0] < 80){
			hauteur = 6;
		}else if(tab[0] > 80 && tab[0] < 85){
			hauteur = 5;
		}else if(tab[0] > 85 && tab[0] < 90){
			hauteur = 4;
		}else if(tab[0] > 90 && tab[0] < 95){
			hauteur = 3;
		}else if(tab[0] > 95 && tab[0] < 100){
			hauteur = 2;
		}
		
		init_pair(1, COLOR_RED, COLOR_BLACK);

		for(j = 21 ; j >= hauteur ; j--){
			
			wbkgd(graph, COLOR_PAIR(1));
			mvwprintw(graph, j, i, "a");
		}

		for(j = hauteur -  1 ; j >= 2 ; j--){
			mvwprintw(graph, j , i , " ");
		}
		i++;
		if(i == 99){
			i = 1;	
		}else{
			for(j = 21 ; j >= 2 ; j--){
				if(i < 98){
					mvwprintw(graph, j , i + 1, " ");
				}
			}	
		}	
		wrefresh(graph);
		wrefresh(haut);	
		free(tab);
	}
	endwin();
	free(haut);
	free(graph);
}
