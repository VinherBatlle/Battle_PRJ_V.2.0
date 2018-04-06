#ifndef EAGLE_H_INCLUDED
#define EAGLE_H_INCLUDED

#include "GameEngine.h"
#include "bullet.h"

typedef struct Eagle Eagle;

struct Eagle{

Sprite* sprite;
int type;
int touchBot;
Bullet* bullet;
int canupdate;

Animation* explo;
};

//
Eagle* eagle_create(SDL_Surface* screen,int type);
//
void eagle_dispose(Eagle* eagle);
//
void eagle_render(Eagle* eagle);
//
void eagle_update(Eagle* eagle);
//
void eagle_setPosition(Eagle* eagle, int x, int y);
//
void eagle_setSpeed(Eagle* eagle, int dx,int dy);
//
void eagle_reset(Eagle* eagle);
//
void eagle_standby(Eagle* eagle);
//
void eagle_hit(Eagle* eagle);
//
int eagle_touchBotScreen(const Eagle* eagle);
#endif // EAGLE_H_INCLUDED
