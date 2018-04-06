#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "GameEngine.h"
#include "Constantes.h"


typedef struct Bullet Bullet;

struct Bullet{

Sprite* sprite;
int type;
int hit;

};

//
Bullet* bullet_create(SDL_Surface* screen,int type);
//
void bullet_dispose(Bullet* bullet);
//
void bullet_render(Bullet* bullet);
//
void bullet_update(Bullet* bullet);
//
void bullet_setPosition(Bullet* bullet, int x, int y);
//
void bullet_setSpeed(Bullet* bullet, int dx,int dy);
//
void bullet_reset(Bullet* bullet);
//
int bullet_hit(const Bullet* bullet);
#endif // BULLET_H_INCLUDED
