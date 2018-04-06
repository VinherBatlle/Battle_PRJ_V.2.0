#ifndef INTRODUCTIONSTAGE_H_INCLUDED
#define INTRODUCTIONSTAGE_H_INCLUDED

#include "GameEngine.h"
#include "Constantes.h"
#include "ship.h"
#include "eaglesp.h"
#include "bullets.h"
#include "heart.h"

typedef struct introVar introVar;

struct introVar
{
Stage* introStage;
SDL_Event event;
Music* music;

MoveLabel* titre;
MoveLabel* auteur;
MoveLabel* start;

int moving;

Heart* heart;
Ship* ship;
Bullets* bullets;
Eaglesp* eaglesp;
ImageScrollingV* bkg;

};

//
int startIntroduction();
//
void createIntroduction(introVar* introvar);
//
void disposeIntroduction(introVar* introvar);
//
void renderIntroduction(introVar* introvar);
//
void updateIntroduction(float delta_s,introVar* introvar);
//
void eventIntroduction(introVar* introvar);

#endif // INTRODUCTIONSTAGE_H_INCLUDED
