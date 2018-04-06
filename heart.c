#include "heart.h"
#include "Constantes.h"

//
Heart* heart_create(SDL_Surface* screen)
{
    Heart* heart=NULL;

    heart=(Heart*)malloc(sizeof(Heart));

    if(heart==NULL)
    return NULL;

    else
    {
    heart->sprite=NULL;
    heart->sound=NULL;
    
	//
    heart->sprite=Sprite_create(screen,"./assets/images/heart.png");
	//Sprite_setDebugRect(heart->sprite,1); //debug
    Sprite_setCollidRectInflate(heart->sprite,3,3);
    //
    Sprite_setSpeeds(heart->sprite,0,4);

	heart_setPosition(heart,WIDTH/2,HEIGHT+1);
   
	heart->sound=Sound_create("./assets/sounds/Heart2.ogg");
	Sound_setVolume(heart->sound,FORT);
   
    }
    return heart;
}
//*********************************
void heart_dispose(Heart* heart)
{
    if(heart->sprite != NULL)
    {
    Sprite_dispose(heart->sprite);
    heart->sprite=NULL;
    }
    //
    free(heart);
}
//********************************
void heart_render(Heart* heart)
{
    Sprite_render(heart->sprite);
}

//********************************
void heart_update(Heart* heart)
{
    Sprite_update(heart->sprite);


    if(Sprite_getBottom(heart->sprite) >=HEIGHT)
    {
	 int rand=ge_rand(0,200);;
	 if(rand==50)
	 {
	 heart_reset(heart);
	 }
    }
}
//*********************************************
void heart_setPosition(Heart* heart, int x, int y)
{
    Sprite_setPosition(heart->sprite,x,y);
}
//******************************************
void heart_setSpeed(Heart* heart, int dx,int dy)
{
    Sprite_setSpeeds(heart->sprite,dx,dy);
}
//*******************************
void heart_reset(Heart* heart)
{
    heart_setPosition(heart,ge_rand(30,WIDTH-30),0);
   
}
//**********************************
int heart_Hit(Heart* heart)
{
	heart_setPosition(heart,0,HEIGHT+30);  
}
//


