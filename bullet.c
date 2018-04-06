#include "bullet.h"


//
Bullet* bullet_create(SDL_Surface* screen,int type)
{
    Bullet* bullet=NULL;

    bullet=(Bullet*)malloc(sizeof(Bullet));

    if(bullet==NULL)
    return NULL;

    else
    {
    bullet->sprite=NULL;
    bullet->type=type;

    if(type==BULLET_TYPE_1)
    {
        bullet->sprite=Sprite_create(screen,"./assets/images/bullet2.png");
    }
    else
    {
       bullet->sprite=Sprite_create(screen,"./assets/images/bullet3.png");
    }
    //
    Sprite_setSpeeds(bullet->sprite,0,-4);    
    //pos
    bullet_setPosition(bullet,2*WIDTH,2*HEIGHT);
	//HIT
    bullet->hit=0;
    //Sprite_setDebugRect(bullet->sprite,1); //<-DEBUG
    
    Sprite_setCollidRectInflate(bullet->sprite,1,1);

    }
    return bullet;
}
//*********************************
void bullet_dispose(Bullet* bullet)
{
    if(bullet->sprite != NULL)
    {
    Sprite_dispose(bullet->sprite);
    bullet->sprite=NULL;
    }
    //
    free(bullet);
}
//********************************
void bullet_render(Bullet* bullet)
{
    Sprite_render(bullet->sprite);
}

//********************************
void bullet_update(Bullet* bullet)
{
    Sprite_update(bullet->sprite);


    if(Sprite_getTop(bullet->sprite) <=10)
    {
    bullet->hit=1;
    }
}
//*********************************************
void bullet_setPosition(Bullet* bullet, int x, int y)
{
    if(bullet->type==BULLET_TYPE_2)
    {
    Sprite_setPosition(bullet->sprite,x,y);
    
    }
    //
    else
    {
	Sprite_setPosition(bullet->sprite,x,y);
    }

}
//******************************************
void bullet_setSpeed(Bullet* bullet, int dx,int dy)
{
    Sprite_setSpeeds(bullet->sprite,dx,dy);
}
//*******************************
void bullet_reset(Bullet* bullet)
{
    bullet_setPosition(bullet,2*WIDTH,2*HEIGHT);
    bullet->hit=0;
    Sprite_setSpeeds(bullet->sprite,0,0);
}
//**********************************
int bullet_hit(const Bullet* bullet)
{
    return bullet->hit;
}
//


