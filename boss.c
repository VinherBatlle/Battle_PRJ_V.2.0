#include "boss.h"
#include "Constantes.h"
int bullets_timer=ge_rand(20,90);
int bullets_timer2=0;
int swd_dir_boss=0;
//
Boss* boss_create(SDL_Surface* screen)
{
    Boss* boss=NULL;
    

    boss=(Boss*)malloc(sizeof(Boss));

    if(boss==NULL)
    return NULL;

    else
    {
    boss->sprite=NULL;
	boss->type=1;
    if(boss->type==BOSS_TYPE_1)
    {
        boss->sprite=Sprite_create(screen,"./assets/images/Boss1.png");
    }
    if(boss->type==BOSS_TYPE_2)
    {
       boss->sprite=Sprite_create(screen,"./assets/images/boss2.png");
    } 
    if(boss->type==BOSS_TYPE_3)
    {
       boss->sprite=Sprite_create(screen,"./assets/images/boss3.png");
    }
    //
    
    boss->Wave=0;
    
    //STATS
    boss->HP=15;
    boss->nbr_bullets=7;
    boss->nbr_bullets_now=3;
    boss->v=2;
    
    //Apparition
    Sprite_setPosition(boss->sprite,2*WIDTH,2*HEIGHT);
    Sprite_setSpeeds(boss->sprite,boss->v,0);
    

    //Sprite_setDebugRect(boss->sprite,1); //DEBUGRECT    
	 Sprite_setCollidRectInflate(boss->sprite,10,20);
    
   
	//bullets
		boss->tabbullet2 = NULL;
		boss->tabbullet2 = (Bullet**) malloc(boss->nbr_bullets * sizeof(Bullet*));
		if(boss->tabbullet2 == NULL){
			exit(0);
		}
		for(int i = 0; i < boss->nbr_bullets; i++){
        boss->tabbullet2[i]=bullet_create(screen,1);
        bullet_setPosition(boss->tabbullet2[i],2*WIDTH,2*HEIGHT);     
		}
    
    //Animation
    boss->explo=Animation_create(screen,"./assets/images/explosion.png",5,5);
	Animation_loadSound(boss->explo,"./assets/sounds/Ship Explod Ennemy.ogg");
	Sound_setVolume(boss->explo->sound,MOYEN);
	}
	return boss;
}
//*********************************
void boss_dispose(Boss* boss)
{	
	for(int i=0 ; i < boss->nbr_bullets_now; i++){
	if(boss->tabbullet2[i] != NULL){
	bullet_dispose(boss->tabbullet2[i]);
	}
	}
	
	Animation_dispose(boss->explo);
	
    if(boss->sprite != NULL)
    {
    Sprite_dispose(boss->sprite);
    boss->sprite=NULL;
    }
    //
    free(boss);
}
//********************************
void boss_render(Boss* boss)
{
	
    Sprite_render(boss->sprite);
    Animation_render(boss->explo);
    
   
  for(int i=0 ; i < boss->nbr_bullets_now; i++){
	if(boss->tabbullet2[i] != NULL)
	bullet_render(boss->tabbullet2[i]);
	}
}

//********************************
void boss_update(Boss* boss)
{	
	bullets_timer++;
	swd_dir_boss++;
	
	Animation_update(boss->explo);
    Sprite_update(boss->sprite);	
   
 for(int i=0 ; i < boss->nbr_bullets_now; i++){
	if(boss->tabbullet2[i] != NULL)
	bullet_update(boss->tabbullet2[i]);
	}
	
	//
	int c_x = Sprite_getCenterX(boss->sprite);
	int c_y = Sprite_getCenterY(boss->sprite);
	int coef= 30; 
	int a=0;
	////////////////////////////////////////////////////////////////////
	if(bullets_timer > 50){
	bullets_timer=0;
		
			for(int i=0; i < boss->nbr_bullets_now; i++){
				if(i <= (boss->nbr_bullets_now/2 ))
				a= i;
				else
				a = - (i - (boss->nbr_bullets_now/2) );
			
				bullet_setPosition(boss->tabbullet2[i], c_x+coef*a, c_y);
				bullet_setSpeed(boss->tabbullet2[i],a*1.5,10);
			}
		}
	
	if(swd_dir_boss > 100){
	swd_dir_boss = 0;
	boss->v = -boss->v;
	Sprite_setSpeeds(boss->sprite,boss->v,0);
	}

}
//*********************************************
void boss_setPosition(Boss* boss, int x, int y)
{

    Sprite_setBottom(boss->sprite,y);
    Sprite_setLeft(boss->sprite,x);

}
//******************************************
void boss_setSpeed(Boss* boss, int dx,int dy)
{
    Sprite_setSpeeds(boss->sprite,dx,dy);
}
//*******************************
void boss_reset(Boss* boss)
{	
	boss->HP = 30;
	boss->nbr_bullets_now=boss->nbr_bullets;
	Sprite_setPosition(boss->sprite,2*WIDTH,2*HEIGHT);
    Sprite_setSpeeds(boss->sprite,boss->v,0);
}
//**********************************
int boss_touchBotScreen(const Boss* boss)
{
    //return boss->touchBot;
}

int boss_hit(Boss* boss,int x, int y)
{
	if(boss->HP > 0){
	boss->HP--;
	//Animation_setPosition(boss->explo,Sprite_getLeft(boss->sprite)-30,Sprite_getTop(boss->sprite)-30);
	Animation_setPosition(boss->explo,x,y);
	Animation_play(boss->explo);
	Animation_playSound(boss->explo);
	return 0;
	}
	if(boss->HP == 0){
	boss->HP--;
	Sprite_setPosition(boss->sprite,2*WIDTH,2*HEIGHT);
	Animation_setPosition(boss->explo,Sprite_getLeft(boss->sprite)-30,Sprite_getTop(boss->sprite)-30);
	boss_reset(boss);
	return 1;
	}
	
}


//


