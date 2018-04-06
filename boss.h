#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "GameEngine.h"
#include "bullet.h"

typedef struct Boss Boss;

struct Boss{

Sprite* sprite;

int Wave;
int HP ;
int nbr_bullets;
int nbr_bullets_now;
int type;
int v;

Bullet** tabbullet2;


Animation* explo;
};

//
Boss* boss_create(SDL_Surface* screen);
//
void boss_dispose(Boss* boss);
//
void boss_render(Boss* boss);
//
void boss_update(Boss* boss);
//
void boss_setPosition(Boss* boss, int x, int y);
//
void boss_setSpeed(Boss* boss, int dx,int dy);
//
void boss_reset(Boss* boss);
//
int boss_hit(Boss* boss,int x, int y);
//
int boss_touchBotScreen(const Boss* boss);
#endif // BOSS_H_INCLUDED
