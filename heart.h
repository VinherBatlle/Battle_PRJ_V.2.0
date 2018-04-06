#ifndef HEART_H_INCLUDED
#define HEART_H_INCLUDED

#include "GameEngine.h"

typedef struct Heart Heart;

struct Heart{

Sprite* sprite;
Sound* sound;
int hit;
};

//
Heart* heart_create(SDL_Surface* screen);
//
void heart_dispose(Heart* heart);
//
void heart_render(Heart* heart);
//
void heart_update(Heart* heart);
//
void heart_setPosition(Heart* heart, int x, int y);
//
void heart_setSpeed(Heart* heart, int dx,int dy);
//
void heart_reset(Heart* heart);
//
int heart_Hit(Heart* heart);
#endif // HEART_H_INCLUDED
