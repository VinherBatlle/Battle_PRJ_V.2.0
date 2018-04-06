#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

#include "GameEngine.h"
#include "bullet.h"
#include "Scores.h"

typedef struct Bullets Bullets;

struct Bullets
{
Bullet** tabbullet;
Bullet* bullet1;
Bullet* bullet2;
Bullet* bullet3;
//Bullet* bullet4;
//Bullet* bullet5;
int nbr_mun;
int nbr_mun_now;
int* tab_n;
int canshoot;
int shoot_i;
};

//
Bullets* bullets_create(SDL_Surface* screen);
//
void bullets_dispose(Bullets* bullets);
//
void bullets_render(Bullets* bullets);
//
void bullets_update(Scores* scores,Bullets* bullets,int playsound);
//
void bullets_newWave(Bullets* bullets,int n);
//
void bullets_setPosSpeed(Bullets* bullets,int x, int y);
//void bullets_swDir(Bullets* bullets); // pour plus tard

#endif // BULLETS_H_INCLUDED
