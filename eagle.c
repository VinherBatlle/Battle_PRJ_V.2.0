#include "eagle.h"
#include "Constantes.h"
int bullet_timer=ge_rand(20,90);

//
Eagle* eagle_create(SDL_Surface* screen,int type)
{
    Eagle* eagle=NULL;
    

    eagle=(Eagle*)malloc(sizeof(Eagle));

    if(eagle==NULL)
    return NULL;

    else
    {
    eagle->sprite=NULL;

    eagle->type=type;

    if(type==EAGLE_TYPE_1)
    {
        eagle->sprite=Sprite_create(screen,"./assets/images/Eagle1.png");
    }
    else
    {
       eagle->sprite=Sprite_create(screen,"./assets/images/Eagle2.png");
    }
    //
    Sprite_setSpeeds(eagle->sprite,0,0);
    eagle->touchBot=0;
    eagle->canupdate=1;
    //Sprite_setDebugRect(eagle->sprite,1); //DEBUGRECT
    Sprite_setCollidRectInflate(eagle->sprite,2,2);
    }
    //Animation
    eagle->explo=Animation_create(screen,"./assets/images/explosion.png",5,5);
	Animation_loadSound(eagle->explo,"./assets/sounds/Ship Explod Ennemy.ogg");
	Sound_setVolume(eagle->explo->sound,MOYEN);
  //bullet
    eagle->bullet=bullet_create(screen,1);
    bullet_setPosition(eagle->bullet,2*WIDTH,2*HEIGHT); 
    
    return eagle;
}
//*********************************
void eagle_dispose(Eagle* eagle)
{
	if(eagle->bullet != NULL)
	bullet_dispose(eagle->bullet);
	Animation_dispose(eagle->explo);
    if(eagle->sprite != NULL)
    {
    Sprite_dispose(eagle->sprite);
    eagle->sprite=NULL;
    }
    //
    free(eagle);
}
//********************************
void eagle_render(Eagle* eagle)
{
	
    Sprite_render(eagle->sprite);
    Animation_render(eagle->explo);
   if(eagle->bullet != NULL)
    bullet_render(eagle->bullet);
}

//********************************
void eagle_update(Eagle* eagle)
{
	if(eagle->canupdate==0){
		Sprite_setPosition(eagle->sprite,2*WIDTH,0);
		Sprite_setSpeeds(eagle->sprite,0,0);
		}

	bullet_timer++;
	
	Animation_update(eagle->explo);
	
	
    Sprite_update(eagle->sprite);	
    if(Sprite_getBottom(eagle->sprite) >=HEIGHT+30)
    {
    eagle->touchBot=1;
    }
    if(eagle->bullet!= NULL)
    bullet_update(eagle->bullet); 
	if(bullet_timer > 70 ){
	bullet_setSpeed(eagle->bullet,0,8);	
	bullet_setPosition(eagle->bullet,Sprite_getCenterX(eagle->sprite),Sprite_getCenterY(eagle->sprite)-10); 
	bullet_timer=0;
	}  


}
//*********************************************
void eagle_setPosition(Eagle* eagle, int x, int y)
{	

    if(eagle->type==EAGLE_TYPE_2)
    {
    Sprite_setBottom(eagle->sprite,y);
    Sprite_setLeft(eagle->sprite,x);
    }
    //
    else
    {
    Sprite_setTop(eagle->sprite,y);
    Sprite_setLeft(eagle->sprite,x);
    }

}
//*******************************************
void eagle_standby(Eagle* eagle)
{		
		eagle->canupdate=0;
		Sprite_setPosition(eagle->sprite,2*WIDTH,0);
		Sprite_setSpeeds(eagle->sprite,0,0);
}
//******************************************
void eagle_setSpeed(Eagle* eagle, int dx,int dy)
{
    Sprite_setSpeeds(eagle->sprite,dx,dy);
}
//*******************************
void eagle_reset(Eagle* eagle)
{
	
    eagle->touchBot=0;
    Sprite_setSpeeds(eagle->sprite,0,0);
	
}
//**********************************
int eagle_touchBotScreen(const Eagle* eagle)
{
    return eagle->touchBot;
}

void eagle_hit(Eagle* eagle)
{
	Animation_setPosition(eagle->explo,Sprite_getLeft(eagle->sprite)-30,Sprite_getTop(eagle->sprite)-30);
	Animation_play(eagle->explo);
	Animation_playSound(eagle->explo);
}

//


