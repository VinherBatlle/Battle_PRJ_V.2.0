#ifndef EAGLESP_H_INCLUDED
#define EAGLESP_H_INCLUDED

#include "GameEngine.h"
#include "eagle.h"
#include "Scores.h"

typedef struct Eaglesp Eaglesp;

struct Eaglesp
{
	
Eagle** tabeagle;
Eagle* eagle1;
Eagle* eagle2;
Eagle* eagle3;
int nbr_eagles;
int nbr_eagles_now;
int nbr_decr;
};

//
Eaglesp* eaglesp_create(SDL_Surface* screen);
//
void eaglesp_dispose(Eaglesp* eaglesp);
//
void eaglesp_render(Eaglesp* eaglesp);
//
void eaglesp_update(Scores* scores,Eaglesp* eaglesp,int playsound);
//
void eaglesp_newWave(Eaglesp* eaglesp,int n);
//
void eaglesp_swDir(Eaglesp* eaglesp);

#endif // EAGLESP_H_INCLUDED
