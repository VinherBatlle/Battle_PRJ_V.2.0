#ifndef GAMESTAGE_H_INCLUDED
#define GAMESTAGE_H_INCLUDED

#include "GameEngine.h"
#include "Constantes.h"
#include "ship.h"
#include "eaglesp.h"
#include "Scores.h"
#include "bullets.h"
#include "heart.h"
#include "boss.h"

typedef struct gameVar gameVar;

struct gameVar
{
Stage* gameStage;
SDL_Event gameevent;
Music* music;

int pause;
int canpause;
int eagleskilled;
int heartpickedup;

Scores* scores;
Heart* heart;
Ship* ship;
Bullets* bullets;
Eaglesp* eaglesp;
Boss* boss;
ImageScrollingV* bkg;

//Pause
SDL_Surface* pause2;
Label* pauselabel;
SDL_Rect pause2_rect;


};

//
int startGame();
//
void createGame(gameVar* gamevar);
//
void disposeGame(gameVar* gamevar);
//
void renderGame(gameVar* gamevar);
//
void updateGame(float delta_s,gameVar* gamevar);
//
void checkCollide(gameVar* gamevar);
//
void eventGame(gameVar* gamevar);

#endif // GAMESTAGE_H_INCLUDED
