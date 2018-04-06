#include "bullets.h"
#include "Constantes.h"

int shoottimer=0; //var glob pour le cooldown

//
Bullets* bullets_create(SDL_Surface* screen)
{
	
    Bullets* bullets=NULL;

    bullets=(Bullets*) malloc(sizeof(Bullets));

    if(bullets==NULL)
        return NULL;

    else
    {	
		bullets->nbr_mun=50;
		bullets->nbr_mun_now=10;
		bullets->tab_n = NULL;
		bullets->tab_n = (int*) malloc(bullets->nbr_mun * sizeof(int));
		bullets->tabbullet = NULL;
		bullets->tabbullet = (Bullet**) malloc(bullets->nbr_mun * sizeof(Bullet*));
		if(bullets->tabbullet == NULL | bullets->tab_n == NULL){
			exit(0);
		}
		for(int i = 0; i < bullets->nbr_mun; i++){
        bullets->tabbullet[i]=bullet_create(screen,2);
        bullet_setPosition(bullets->tabbullet[i],2*WIDTH,2*HEIGHT);     
		}
		/*for(int i= 0; i < bullets->nbr_mun/2 ; i++){
        bullets->tabbullet[i]=bullet_create(screen,1);
        bullet_setPosition(bullets->tabbullet[i],2*WIDTH,2*HEIGHT);     
		}*/


        
        bullets->canshoot=1;
        
       for(int i=0 ; i < bullets->nbr_mun_now ; i++)
       {
		   bullets->tab_n[i]=1;
	   }  
	}

    return bullets;
}
//**********************************************************************
void bullets_dispose(Bullets* bullets)
{
	for(int i = 0; i < bullets->nbr_mun; i++){
		if(bullets->tabbullet[1] != NULL)
        bullet_dispose(bullets->tabbullet[i]);
	}
    //
    free(bullets);
}
//**********************************************************************
void bullets_render(Bullets* bullets)
{
    for(int i = 0; i < bullets->nbr_mun_now; i++){
		if(bullets->tabbullet[1] != NULL)
        bullet_render(bullets->tabbullet[i]);
	}
        
 

}
//**********************************************************************
void bullets_update(Scores* scores,Bullets* bullets,int playsound)
{
	//Cooldown shoot
	if(bullets->canshoot==0)
	{ 
		shoottimer++;
	}
	if(shoottimer>10)
	{
		bullets->canshoot=1;
		shoottimer=0;
		
	}
	
	//Reset ammo
	for(int i = 0; i < bullets->nbr_mun_now; i++){
		if(bullet_hit(bullets->tabbullet[i]) | bullet_hit(bullets->tabbullet[i])){
        bullet_reset(bullets->tabbullet[i]);
        bullets->tab_n[i]=1;
		}
	}
   
    //

    //Update
    //
    for(int i = 0; i < bullets->nbr_mun_now; i++){
    bullet_update(bullets->tabbullet[i]);
	}
    //
  
}

void bullets_setPosSpeed(Bullets* bullets,int x, int y)
{
	
	if(bullets->shoot_i >= bullets->nbr_mun_now ){
		bullets->shoot_i=0;
	}
	if(bullets->tab_n[bullets->shoot_i]==1)	
	{
		bullet_setPosition(bullets->tabbullet[bullets->shoot_i],x,y);
		bullet_setSpeed(bullets->tabbullet[bullets->shoot_i],0,-BULLET1_SPEED);	
		bullets->tab_n[bullets->shoot_i]=0; 
	}
	
}










